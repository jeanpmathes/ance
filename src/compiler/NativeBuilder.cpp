#include "NativeBuilder.h"

#include "compiler/CompileContext.h"
#include "compiler/NativeBuild.h"
#include "compiler/RoughlyCastedValue.h"
#include "lang/type/ArrayType.h"
#include "lang/type/VectorType.h"
#include "lang/utility/Erased.h"

NativeBuilder::NativeBuilder(NativeBuild& native_build) : native_build_(native_build)
{
    native_build_.setActiveVisitor(this);
}

void NativeBuilder::preVisit(lang::Visitable<ANCE_CONSTRUCTS> const& visitable)
{
    auto const* located = dynamic_cast<lang::Located const*>(&visitable);
    if (located != nullptr) { native_build_.cc().setDebugLocation(located->location(), located->scope()); }
}

void NativeBuilder::postVisit(lang::Visitable<ANCE_CONSTRUCTS> const& visitable)
{
    auto const* located = dynamic_cast<lang::Located const*>(&visitable);
    if (located != nullptr) { native_build_.cc().resetDebugLocation(); }
}

std::any NativeBuilder::visit(lang::GlobalScope const& global_scope)
{
    if (native_build_.cc().unit().isUsingRuntime()) native_build_.cc().runtime().init(native_build_.cc());

    g_phase_ = G_Phase::DECLARE;

    for (auto& used_type : global_scope.getUsedBuiltInTypes()) { used_type.get().buildDeclaration(native_build_.cc()); }

    for (auto& description : global_scope.getDescriptionsInDeclarationOrder()) { visitTree(description); }

    native_build_.cc().ctx().buildDeclarations(native_build_.cc());

    g_phase_ = G_Phase::DEFINE;

    for (auto& used_type : global_scope.getUsedBuiltInTypes()) { used_type.get().buildDefinition(native_build_.cc()); }

    for (auto& description : global_scope.getDescriptionsInDefinitionOrder()) { visitTree(description); }

    native_build_.cc().ctx().buildDefinitions(native_build_.cc());

    g_phase_ = G_Phase::INVALID;

    return {};
}

std::any NativeBuilder::visit(lang::FunctionDescription const& function_description)
{
    return visitTree(*function_description.function());
}

std::any NativeBuilder::visit(lang::VariableDescription const& variable_description)
{
    switch (g_phase_)
    {
        case G_Phase::DECLARE:
        {
            variable_description.variable()->buildDeclaration(native_build_.cc());
        }
        break;
        case G_Phase::DEFINE:
        {
        }
        break;
        default:
            throw std::logic_error("Invalid global scope phase");
    }

    if (variable_description.initializerFunction() != nullptr)
    {
        visitTree(variable_description.initializerFunction()->function());
    }

    return {};
}

std::any NativeBuilder::visit(lang::StructDescription const& struct_description)
{
    switch (g_phase_)
    {
        case G_Phase::DECLARE:
        {
            struct_description.type().buildDeclaration(native_build_.cc());
        }
        break;
        case G_Phase::DEFINE:
        {
            struct_description.type().buildDefinition(native_build_.cc());
        }
        break;
        default:
            throw std::logic_error("Invalid global scope phase");
    }

    return {};
}

std::any NativeBuilder::visit(lang::AliasDescription const& alias_description)
{
    switch (g_phase_)
    {
        case G_Phase::DECLARE:
        {
            alias_description.type().buildDeclaration(native_build_.cc());
        }
        break;
        case G_Phase::DEFINE:
        {
            alias_description.type().buildDefinition(native_build_.cc());
        }
        break;
        default:
            throw std::logic_error("Invalid global scope phase");
    }

    return {};
}

std::any NativeBuilder::visit(lang::Member const&)
{
    throw std::logic_error("Members are built trough their parent struct");
}

std::any NativeBuilder::visit(lang::Function const& function)
{
    switch (g_phase_)
    {
        case G_Phase::DECLARE:
        {
            function.buildDeclaration(native_build_.cc());
        }
        break;
        case G_Phase::DEFINE:
        {
            if (function.getEntryBlock() == nullptr) return {};

            native_build_.setCurrentFunction(&function);
            assert(native_build_.getCurrentFunction()->getSubprogram() != nullptr);

            llvm::BasicBlock* decl =
                llvm::BasicBlock::Create(native_build_.llvmContext(), "decl", native_build_.getCurrentFunction());

            native_build_.ir().SetInsertPoint(decl);
            function.buildEntityDeclarations(native_build_.cc());

            llvm::BasicBlock* defs =
                llvm::BasicBlock::Create(native_build_.llvmContext(), "defs", native_build_.getCurrentFunction());

            native_build_.ir().CreateBr(defs);
            native_build_.ir().SetInsertPoint(defs);
            for (auto& parameter : function.parameters())
            {
                parameter->argument().buildInitialization(native_build_.cc());
            }

            bb_phase_ = BB_Phase::PREPARE;
            bb_visited_.clear();

            visitTree(*function.getEntryBlock());

            bb_phase_ = BB_Phase::BUILD;
            bb_visited_.clear();

            visitTree(*function.getEntryBlock());

            bb_phase_ = BB_Phase::INVALID;
            bb_map_.clear();
            bb_visited_.clear();

            native_build_.ir().SetCurrentDebugLocation(llvm::DebugLoc());
            native_build_.di().finalizeSubprogram(native_build_.getCurrentFunction()->getSubprogram());

            native_build_.setCurrentFunction(nullptr);
        }
        break;
        default:
            throw std::logic_error("Invalid global scope phase");
    }

    return {};
}

std::any NativeBuilder::visit(lang::BasicBlock const& basic_block)
{
    if (bb_visited_.contains(&basic_block)) return {};
    bb_visited_.insert(&basic_block);

    visitTree(basic_block.definition());

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Empty const& empty_bb)
{
    lang::BasicBlock::Definition::Base const* this_ptr = &empty_bb;

    switch (bb_phase_)
    {
        case BB_Phase::PREPARE:
        {
            std::string const name = "b" + std::to_string(empty_bb.index());
            bb_map_[this_ptr] =
                llvm::BasicBlock::Create(native_build_.llvmContext(), name, native_build_.getCurrentFunction());

            if (empty_bb.next()) visitTree(*empty_bb.next());
        }
        break;
        case BB_Phase::BUILD:
        {
            native_build_.ir().CreateBr(bb_map_[this_ptr]);// Branch from prelude in function to this block
            native_build_.ir().SetInsertPoint(bb_map_[this_ptr]);

            if (empty_bb.next() != nullptr)
            {
                lang::BasicBlock::Definition::Base const* next_ptr = &empty_bb.next()->definition();

                native_build_.ir().CreateBr(bb_map_[next_ptr]);
                visitTree(*empty_bb.next());
            }
            else { native_build_.ir().CreateRetVoid(); }
        }
        break;
        default:
            throw std::logic_error("Unknown basic block phase");
    }

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Finalizing const& finalizing_bb)
{
    lang::BasicBlock::Definition::Base const* this_ptr = &finalizing_bb;

    switch (bb_phase_)
    {
        case BB_Phase::PREPARE:
        {
            std::string const name = "b" + std::to_string(finalizing_bb.index());
            bb_map_[this_ptr] =
                llvm::BasicBlock::Create(native_build_.llvmContext(), name, native_build_.getCurrentFunction());

            if (finalizing_bb.next()) visitTree(*finalizing_bb.next());
        }
        break;
        case BB_Phase::BUILD:
        {
            native_build_.ir().SetInsertPoint(bb_map_[this_ptr]);

            finalizing_bb.scope().buildEntityFinalizations(native_build_.cc());

            if (finalizing_bb.next() != nullptr)
            {
                lang::BasicBlock::Definition::Base const* next_ptr = &finalizing_bb.next()->definition();

                native_build_.ir().CreateBr(bb_map_[next_ptr]);
                visitTree(*finalizing_bb.next());
            }
            else { native_build_.ir().CreateRetVoid(); }
        }
        break;
        default:
            throw std::logic_error("Unknown basic block phase");
    }

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Simple const& simple_bb)
{
    lang::BasicBlock::Definition::Base const* this_ptr = &simple_bb;

    switch (bb_phase_)
    {
        case BB_Phase::PREPARE:
        {
            std::string const name = "b" + std::to_string(simple_bb.index());
            bb_map_[this_ptr] =
                llvm::BasicBlock::Create(native_build_.llvmContext(), name, native_build_.getCurrentFunction());

            if (simple_bb.next()) visitTree(*simple_bb.next());
        }
        break;
        case BB_Phase::BUILD:
        {
            native_build_.ir().SetInsertPoint(bb_map_[this_ptr]);

            for (Statement const* statement : simple_bb.statements()) visitTree(*statement);

            if (simple_bb.next() != nullptr)
            {
                lang::BasicBlock::Definition::Base const* next_ptr = &simple_bb.next()->definition();

                native_build_.ir().CreateBr(bb_map_[next_ptr]);
                visitTree(*simple_bb.next());
            }
            else { native_build_.ir().CreateRetVoid(); }
        }
        break;
        default:
            throw std::logic_error("Unknown basic block phase");
    }

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Returning const& returning_bb)
{
    lang::BasicBlock::Definition::Base const* this_ptr = &returning_bb;

    switch (bb_phase_)
    {
        case BB_Phase::PREPARE:
        {
            std::string const name = "b" + std::to_string(returning_bb.index());
            bb_map_[this_ptr] =
                llvm::BasicBlock::Create(native_build_.llvmContext(), name, native_build_.getCurrentFunction());
        }
        break;
        case BB_Phase::BUILD:
        {
            native_build_.ir().SetInsertPoint(bb_map_[this_ptr]);

            for (Statement const* statement : returning_bb.statements()) visitTree(*statement);

            lang::Scope const* current = &returning_bb.scope();
            while (current->isPartOfFunction())
            {
                current->buildEntityFinalizations(native_build_.cc());
                current = &current->scope();
            }

            lang::Type const& return_type = returning_bb.self()->getContainingFunction()->returnType();

            if (return_type.isUnitType()) { native_build_.performReturn(std::nullopt); }
            else
            {
                Shared<lang::Value> return_value = getV(returning_bb.ret());

                return_value = lang::Type::makeMatching(return_type, return_value, native_build_.cc());

                native_build_.performReturn(return_value);
            }
        }
        break;
        default:
            throw std::logic_error("Unknown basic block phase");
    }

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Branching const& branching_bb)
{
    lang::BasicBlock::Definition::Base const* this_ptr = &branching_bb;

    switch (bb_phase_)
    {
        case BB_Phase::PREPARE:
        {
            std::string const name = "b" + std::to_string(branching_bb.index());
            bb_map_[this_ptr] =
                llvm::BasicBlock::Create(native_build_.llvmContext(), name, native_build_.getCurrentFunction());

            visitTree(*branching_bb.trueNext());
            visitTree(*branching_bb.falseNext());
        }
        break;
        case BB_Phase::BUILD:
        {
            native_build_.ir().SetInsertPoint(bb_map_[this_ptr]);

            for (Statement const* statement : branching_bb.statements()) visitTree(*statement);

            Shared<lang::Value> truth = getV(branching_bb.condition());
            Shared<lang::Value> boolean_truth =
                lang::Type::makeMatching(native_build_.cc().ctx().getBooleanType(), truth, native_build_.cc());

            native_build_.ir().CreateCondBr(native_build_.llvmContentValue(boolean_truth),
                                            bb_map_[&branching_bb.trueNext()->definition()],
                                            bb_map_[&branching_bb.falseNext()->definition()]);

            visitTree(*branching_bb.trueNext());
            visitTree(*branching_bb.falseNext());
        }
        break;
        default:
            throw std::logic_error("Unknown basic block phase");
    }

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Matching const& matching_bb)
{
    lang::BasicBlock::Definition::Base const* this_ptr = &matching_bb;

    switch (bb_phase_)
    {
        case BB_Phase::PREPARE:
        {
            std::string const name = "b" + std::to_string(matching_bb.index());
            bb_map_[this_ptr] =
                llvm::BasicBlock::Create(native_build_.llvmContext(), name, native_build_.getCurrentFunction());

            for (lang::BasicBlock const* branch : matching_bb.branches()) visitTree(*branch);
        }
        break;
        case BB_Phase::BUILD:
        {
            auto const& cases    = matching_bb.cases();
            auto const& branches = matching_bb.branches();

            native_build_.ir().SetInsertPoint(bb_map_[this_ptr]);

            for (Statement const* statement : matching_bb.statements()) visitTree(*statement);

            llvm::BasicBlock* default_block = nullptr;

            for (auto const [case_values, branch_block] : llvm::zip(cases, branches))
            {
                if (case_values.empty())
                {
                    default_block = bb_map_[&branch_block->definition()];
                    break;
                }
            }

            if (!default_block) { default_block = bb_map_[&branches.front()->definition()]; }

            Shared<lang::Value> value = getV(matching_bb.matched());

            auto switch_instance = native_build_.ir().CreateSwitch(native_build_.llvmContentValue(value),
                                                                   default_block,
                                                                   static_cast<unsigned>(cases.size()));

            for (auto const [case_values, branch_block] : llvm::zip(cases, branches))
            {
                llvm::BasicBlock* branch_native_block = bb_map_[&branch_block->definition()];

                if (case_values.empty() || branch_native_block == default_block) continue;

                for (auto& case_value : case_values)
                {
                    Shared<lang::Constant> constant = getC(*case_value);

                    auto native_integer_constant = llvm::cast<llvm::ConstantInt>(native_build_.llvmConstant(constant));
                    switch_instance->addCase(native_integer_constant, branch_native_block);
                }
            }

            for (lang::BasicBlock const* branch : branches) visitTree(*branch);
        }
        break;
        default:
            throw std::logic_error("Unknown basic block phase");
    }

    return {};
}

std::any NativeBuilder::visit(Addressof const& addressof)
{
    Shared<lang::Value> value   = getV(addressof.argument());
    Shared<lang::Value> address = native_build_.computeAddressOf(value);

    return erase(address);
}

std::any NativeBuilder::visit(Allocation const& allocation)
{
    Optional<Shared<lang::Value>> count = {};

    if (allocation.count() != nullptr)
    {
        count = getV(*allocation.count());
        count = lang::Type::makeMatching(native_build_.cc().ctx().getSizeType(), count.value(), native_build_.cc());
    }

    auto const& allocated_type = lang::Type::makeMatching<lang::Type>(allocation.allocatedType());

    Shared<lang::Value> allocated =
        native_build_.cc().runtime().allocate(allocation.allocator(), allocated_type, count, native_build_.cc());

    return erase(allocated);
}

std::any NativeBuilder::visit(And const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(ArrayDefinition const& array_definition)
{
    lang::Type const& array_element_type = array_definition.type().getElementType();

    std::vector<std::reference_wrapper<Expression const>> const elements = array_definition.values();

    std::vector<Shared<lang::Value>> values;
    values.reserve(elements.size());

    for (auto& element : elements)
    {
        Shared<lang::Value> value = getV(element.get());

        value = lang::Type::makeMatching(array_element_type, value, native_build_.cc());
        values.emplace_back(std::move(value));
    }

    lang::ArrayType const* array_type = array_definition.type().isArrayType();
    assert(array_type);

    auto value = array_type->createValue(std::move(values), native_build_.cc());

    return erase(value);
}

std::any NativeBuilder::visit(BinaryOperation const& binary_operation)
{
    Shared<lang::Value> left  = getV(binary_operation.left());
    Shared<lang::Value> right = getV(binary_operation.right());

    if (!lang::Type::areSame(right->type(), binary_operation.getRightType()))
    {
        right = right->type().buildImplicitConversion(binary_operation.getRightType(), right, native_build_.cc());
    }

    Shared<lang::Value> result = left->type().buildOperator(binary_operation.op(), left, right, native_build_.cc());

    return erase(result);
}

std::any NativeBuilder::visit(BindRef const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(BindRefTo const& bind_ref_to)
{
    Shared<lang::Value> value     = getV(bind_ref_to.address());
    Shared<lang::Value> reference = native_build_.computeReferenceFromPointer(value);

    return erase(reference);
}

std::any NativeBuilder::visit(Cast const& cast)
{
    auto const& target_type = lang::Type::makeMatching<lang::Type>(cast.target());

    Shared<lang::Value> value = getV(cast.value());

    if (lang::Type::areSame(value->type(), target_type)) { return erase(value); }
    else
    {
        Shared<lang::Value> casted_value = value->type().buildCast(target_type, value, native_build_.cc());
        return erase(casted_value);
    }
}

std::any NativeBuilder::visit(LiteralExpression const& constant_literal)
{
    Shared<lang::Constant> constant = constant_literal.constant().embed(native_build_.cc());
    Shared<lang::Value>    value    = constant;

    return erase(value);
}

std::any NativeBuilder::visit(FunctionCall const& function_call)
{
    std::vector<std::reference_wrapper<Expression const>> const arguments = function_call.arguments();

    std::vector<Shared<lang::Value>> arg_values;
    arg_values.reserve(arguments.size());

    for (auto& arg : arguments)
    {
        Shared<lang::Value> value = getV(arg.get());
        arg_values.emplace_back(std::move(value));
    }

    Shared<lang::Value> return_value = function_call.function().buildCall(arg_values, native_build_.cc());

    return erase(return_value);
}

std::any NativeBuilder::visit(IfSelect const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(Indirection const& indirection)
{
    Shared<lang::Value> value     = getV(indirection.value());
    Shared<lang::Value> reference = value->type().buildIndirection(value, native_build_.cc());

    return erase(reference);
}

std::any NativeBuilder::visit(MatchSelect const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(MemberAccess const& member_access)
{
    Shared<lang::Value>     struct_value = getV(member_access.value());
    lang::Identifier const& member       = member_access.member();

    Shared<lang::Value> value = struct_value->type().buildMemberAccess(struct_value, member, native_build_.cc());

    return erase(value);
}

std::any NativeBuilder::visit(Or const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(Parenthesis const& parenthesis)
{
    Shared<lang::Value> value = getV(parenthesis.contained());

    return erase(value);
}

std::any NativeBuilder::visit(SizeofExpression const& sizeof_expression)
{
    lang::Type const& expression_type = sizeof_expression.expression().type();

    Shared<lang::Value> size = native_build_.getSizeOf(expression_type);

    return erase(size);
}

std::any NativeBuilder::visit(SizeofType const& sizeof_type)
{
    lang::Entity const& target      = sizeof_type.target();
    auto const&         target_type = lang::Type::makeMatching<lang::Type>(target);

    Shared<lang::Value> size = native_build_.getSizeOf(target_type);

    return erase(size);
}

std::any NativeBuilder::visit(Subscript const& subscript)
{
    Shared<lang::Value> indexed = getV(subscript.indexed());
    Shared<lang::Value> index   = getV(subscript.index());

    Shared<lang::Value> value = indexed->type().buildSubscript(indexed, index, native_build_.cc());

    return erase(value);
}

std::any NativeBuilder::visit(UnaryOperation const& unary_operation)
{
    Shared<lang::Value> operand = getV(unary_operation.operand());
    Shared<lang::Value> result  = operand->type().buildOperator(unary_operation.op(), operand, native_build_.cc());

    return erase(result);
}

std::any NativeBuilder::visit(VariableAccess const& variable_access)
{
    auto const& variable = lang::Type::makeMatching<lang::Variable>(variable_access.variable());

    if (assign_)
    {
        Shared<lang::Value> pointer   = variable.getValuePointer(native_build_.cc());
        Shared<lang::Value> reference = native_build_.computeReferenceFromPointer(pointer);

        return erase(reference);
    }
    else if (variable_access.type().getStateCount().isUnit())
    {
        return erase(native_build_.getDefault(variable_access.type()));
    }
    else
    {
        Shared<lang::Value> value = variable.getValue(native_build_.cc());

        return erase(value);
    }
}

std::any NativeBuilder::visit(VectorDefinition const& vector_definition)
{
    lang::Type const& vector_element_type = vector_definition.type().getElementType();

    std::vector<std::reference_wrapper<Expression const>> const elements = vector_definition.values();

    std::vector<Shared<lang::Value>> values;
    values.reserve(elements.size());

    for (auto& element : elements)
    {
        Shared<lang::Value> value = getV(element.get());
        value                     = lang::Type::makeMatching(vector_element_type, value, native_build_.cc());

        values.emplace_back(std::move(value));
    }

    lang::VectorType const* vector_type = vector_definition.type().isVectorType();
    assert(vector_type);

    Shared<lang::Value> value = vector_type->createValue(std::move(values), native_build_.cc());

    return erase(value);
}

std::any NativeBuilder::visit(lang::CodeBlock const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(Assertion const& assertion)
{
    Shared<lang::Value> condition = getV(assertion.condition());
    std::string const   message   = std::format("Assertion failed at [{}] {}",
                                            native_build_.cc().unit().getName(),
                                            native_build_.cc().getLocationString());

    native_build_.cc().runtime().buildAssert(condition, message, native_build_.cc());

    return {};
}

std::any NativeBuilder::visit(Assignment const& assignment_statement)
{
    assign_ = true;

    Shared<lang::Value> destination_reference = getV(assignment_statement.assignable());
    assert(destination_reference->type().isReferenceType());

    lang::Type const& target_type = destination_reference->type().getElementType();

    assign_ = false;

    Shared<lang::Value> assigned_value = getV(assignment_statement.assigned());
    assigned_value                     = lang::Type::makeMatching(target_type, assigned_value, native_build_.cc());

    if (target_type.getStateCount().isUnit()) return {};

    Shared<lang::Value> destination_pointer = native_build_.computePointerFromReference(destination_reference);
    Shared<lang::Value> value_pointer       = native_build_.computeAddressOf(assigned_value);

    target_type.performCopyInitializer(destination_pointer, value_pointer, native_build_.cc());

    return {};
}

std::any NativeBuilder::visit(Break const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(Continue const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(Delete const& delete_statement)
{
    Shared<lang::Value> to_delete        = getV(delete_statement.toDelete());
    bool const          is_buffer_delete = delete_statement.isBufferDelete();

    native_build_.cc().runtime().deleteDynamic(to_delete, is_buffer_delete, native_build_.cc());

    return {};
}

std::any NativeBuilder::visit(Erase const& erase_statement)
{
    auto const& variable = lang::Type::makeMatching<lang::Variable>(erase_statement.variable());

    variable.buildFinalization(native_build_.cc());

    return {};
}

std::any NativeBuilder::visit(ExpressionStatement const& expression_statement)
{
    getV(expression_statement.expression());

    return {};
}

std::any NativeBuilder::visit(If const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(LocalReferenceVariableDefinition const& local_reference_variable_definition)
{
    lang::Variable const& variable = local_reference_variable_definition.variable();

    variable.buildInitialization(native_build_.cc());

    return {};
}

std::any NativeBuilder::visit(LocalVariableDefinition const& local_variable_definition)
{
    lang::Variable const& variable = local_variable_definition.variable();

    variable.buildInitialization(native_build_.cc());

    return {};
}

std::any NativeBuilder::visit(Match const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(Return const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(While const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any NativeBuilder::visit(Loop const&)
{
    throw std::logic_error("Not part of expanded AST");
}

Shared<lang::Constant> NativeBuilder::getC(Expression const& expression)
{
    Shared<lang::Value> value = getV(expression);
    return value.cast<lang::Constant>();
}

Shared<lang::Value> NativeBuilder::getV(Expression const& expression)
{
    std::any const value = visitTree(expression);
    return erasedCast<Shared<lang::Value>>(value);
}
