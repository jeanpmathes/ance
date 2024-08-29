#include "Builder.h"

#include "lang/type/ArrayType.h"
#include "lang/type/VectorType.h"
#include "lang/utility/Erased.h"

std::any Builder::visit(lang::GlobalScope const& global_scope)
{
    g_phase_ = GlobalPhase::DECLARE;

    for (auto& used_type : global_scope.getUsedBuiltInTypes()) { used_type.get().registerDeclaration(exec()); }

    for (auto& description : global_scope.getDescriptionsInDeclarationOrder())
    {
        if (!isDescriptionAccepted(description)) continue;

        visitTree(description);
    }

    exec().ctx().registerDeclarations(exec());

    g_phase_ = GlobalPhase::DEFINE;

    for (auto& used_type : global_scope.getUsedBuiltInTypes()) { used_type.get().registerDefinition(exec()); }

    for (auto& description : global_scope.getDescriptionsInDefinitionOrder())
    {
        if (!isDescriptionAccepted(description)) continue;

        visitTree(description);
    }

    exec().ctx().registerDefinitions(exec());

    g_phase_ = GlobalPhase::INVALID;

    return {};
}

bool Builder::isDescriptionAccepted(lang::Description const&) const
{
    return true;
}

std::any Builder::visit(lang::FunctionDescription const& function_description)
{
    return visitTree(*function_description.function());
}

std::any Builder::visit(lang::VariableDescription const& variable_description)
{
    switch (g_phase_)
    {
        case GlobalPhase::DECLARE:
        {
            variable_description.variable()->registerDeclaration(exec());
        }
        break;
        case GlobalPhase::DEFINE:
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

std::any Builder::visit(lang::StructDescription const& struct_description)
{
    switch (g_phase_)
    {
        case GlobalPhase::DECLARE:
        {
            struct_description.type().registerDeclaration(exec());
        }
        break;
        case GlobalPhase::DEFINE:
        {
            struct_description.type().registerDefinition(exec());
        }
        break;
        default:
            throw std::logic_error("Invalid global scope phase");
    }

    return {};
}

std::any Builder::visit(lang::AliasDescription const& alias_description)
{
    switch (g_phase_)
    {
        case GlobalPhase::DECLARE:
        {
            alias_description.type().registerDeclaration(exec());
        }
        break;
        case GlobalPhase::DEFINE:
        {
            alias_description.type().registerDefinition(exec());
        }
        break;
        default:
            throw std::logic_error("Invalid global scope phase");
    }

    return {};
}

std::any Builder::visit(lang::Member const&)
{
    throw std::logic_error("Members are built trough their parent struct");
}

std::any Builder::visit(lang::Function const& function)
{
    switch (g_phase_)
    {
        case GlobalPhase::DECLARE:
        {
            function.registerDeclaration(exec());
        }
        break;
        case GlobalPhase::DEFINE:
        {
            visitFunctionDefinition(function);
        }
        break;
        default:
            throw std::logic_error("Invalid global scope phase");
    }

    return {};
}

std::any Builder::visit(Addressof const& addressof)
{
    Shared<lang::Value> value   = getV(addressof.argument());
    Shared<lang::Value> address = exec().computeAddressOf(value);

    return erase(address);
}

std::any Builder::visit(Allocation const& allocation)
{
    Optional<Shared<lang::Value>> count = {};

    if (allocation.count() != nullptr)
    {
        count = getV(*allocation.count());
        count = lang::Type::makeMatching(exec().ctx().getSizeType(), count.value(), exec());
    }

    auto const& allocated_type = lang::Type::makeMatching<lang::Type>(allocation.allocatedType());

    Shared<lang::Value> allocated = exec().runtime().allocate(allocation.allocator(), allocated_type, count, exec());

    return erase(allocated);
}

std::any Builder::visit(And const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(ArrayDefinition const& array_definition)
{
    lang::Type const& array_element_type = array_definition.type().getElementType();

    std::vector<std::reference_wrapper<Expression const>> const elements = array_definition.values();

    std::vector<Shared<lang::Value>> values;
    values.reserve(elements.size());

    for (auto& element : elements)
    {
        Shared<lang::Value> value = getV(element.get());

        value = lang::Type::makeMatching(array_element_type, value, exec());
        values.emplace_back(std::move(value));
    }

    lang::ArrayType const* array_type = array_definition.type().isArrayType();
    assert(array_type);

    auto value = array_type->createValue(values, exec());

    return erase(value);
}

std::any Builder::visit(BinaryOperation const& binary_operation)
{
    Shared<lang::Value> left  = getV(binary_operation.left());
    Shared<lang::Value> right = getV(binary_operation.right());

    if (!lang::Type::areSame(right->type(), binary_operation.getRightType()))
    {
        right = right->type().execImplicitConversion(binary_operation.getRightType(), right, exec());
    }

    Shared<lang::Value> result = left->type().execOperator(binary_operation.op(), left, right, exec());

    return erase(result);
}

std::any Builder::visit(BindRef const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(BindRefTo const& bind_ref_to)
{
    Shared<lang::Value> value     = getV(bind_ref_to.address());
    Shared<lang::Value> reference = exec().computeReferenceFromPointer(value);

    return erase(reference);
}

std::any Builder::visit(Cast const& cast)
{
    auto const& target_type = lang::Type::makeMatching<lang::Type>(cast.target());

    Shared<lang::Value> value = getV(cast.value());

    if (lang::Type::areSame(value->type(), target_type)) { return erase(value); }
    else
    {
        Shared<lang::Value> casted_value = value->type().execCast(target_type, value, exec());
        return erase(casted_value);
    }
}

std::any Builder::visit(LiteralExpression const& constant_literal)
{
    Shared<lang::Constant> constant = constant_literal.constant().embed(exec());
    Shared<lang::Value>    value    = constant;

    return erase(value);
}

std::any Builder::visit(FunctionCall const& function_call)
{
    std::vector<std::reference_wrapper<Expression const>> const arguments = function_call.arguments();

    std::vector<Shared<lang::Value>> arg_values;
    arg_values.reserve(arguments.size());

    for (auto& arg : arguments)
    {
        Shared<lang::Value> value = getV(arg.get());
        arg_values.emplace_back(std::move(value));
    }

    Shared<lang::Value> return_value = function_call.function().execCall(arg_values, exec());

    return erase(return_value);
}

std::any Builder::visit(IfSelect const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(Indirection const& indirection)
{
    Shared<lang::Value> value     = getV(indirection.value());
    Shared<lang::Value> reference = value->type().execIndirection(value, exec());

    return erase(reference);
}

std::any Builder::visit(MatchSelect const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(MemberAccess const& member_access)
{
    Shared<lang::Value>     struct_value = getV(member_access.value());
    lang::Identifier const& member       = member_access.member();

    Shared<lang::Value> value = struct_value->type().execMemberAccess(struct_value, member, exec());

    return erase(value);
}

std::any Builder::visit(Or const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(Parenthesis const& parenthesis)
{
    Shared<lang::Value> value = getV(parenthesis.contained());

    return erase(value);
}

std::any Builder::visit(SizeofExpression const& sizeof_expression)
{
    lang::Type const& expression_type = sizeof_expression.expression().type();

    Shared<lang::Value> size = exec().getSizeOf(expression_type);

    return erase(size);
}

std::any Builder::visit(SizeofType const& sizeof_type)
{
    lang::Entity const& target      = sizeof_type.target();
    auto const&         target_type = lang::Type::makeMatching<lang::Type>(target);

    Shared<lang::Value> size = exec().getSizeOf(target_type);

    return erase(size);
}

std::any Builder::visit(Subscript const& subscript)
{
    Shared<lang::Value> indexed = getV(subscript.indexed());
    Shared<lang::Value> index   = getV(subscript.index());

    Shared<lang::Value> value = indexed->type().execSubscript(indexed, index, exec());

    return erase(value);
}

std::any Builder::visit(UnaryOperation const& unary_operation)
{
    Shared<lang::Value> operand = getV(unary_operation.operand());
    Shared<lang::Value> result  = operand->type().execOperator(unary_operation.op(), operand, exec());

    return erase(result);
}

std::any Builder::visit(VariableAccess const& variable_access)
{
    auto const& variable = lang::Type::makeMatching<lang::Variable>(variable_access.variable());

    if (assign_)
    {
        Shared<lang::Value> pointer   = variable.getValuePointer(exec());
        Shared<lang::Value> reference = exec().computeReferenceFromPointer(pointer);

        return erase(reference);
    }
    else if (variable_access.type().getStateCount().isUnit())
    {
        Shared<lang::Value> default_value = exec().getDefault(variable_access.type());

        return erase(default_value);
    }
    else
    {
        Shared<lang::Value> value = variable.getValue(exec());

        return erase(value);
    }
}

std::any Builder::visit(VectorDefinition const& vector_definition)
{
    lang::Type const& vector_element_type = vector_definition.type().getElementType();

    std::vector<std::reference_wrapper<Expression const>> const elements = vector_definition.values();

    std::vector<Shared<lang::Value>> values;
    values.reserve(elements.size());

    for (auto& element : elements)
    {
        Shared<lang::Value> value = getV(element.get());
        value                     = lang::Type::makeMatching(vector_element_type, value, exec());

        values.emplace_back(std::move(value));
    }

    lang::VectorType const* vector_type = vector_definition.type().isVectorType();
    assert(vector_type);

    Shared<lang::Value> value = vector_type->createValue(values, exec());

    return erase(value);
}

std::any Builder::visit(lang::CodeBlock const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(Assertion const& assertion)
{
    Shared<lang::Value> condition = getV(assertion.condition());
    std::string const   message =
        std::format("Assertion failed at [{}] {}", exec().unit().getName(), exec().getLocationString());

    exec().runtime().execAssert(condition, message, exec());

    return {};
}

std::any Builder::visit(Assignment const& assignment_statement)
{
    assign_ = true;

    Shared<lang::Value> destination_reference = getV(assignment_statement.assignable());
    assert(destination_reference->type().isReferenceType());

    assign_ = false;

    lang::Type const& target_type = assignment_statement.assignable().assignableType();

    if (lang::Type::areSame(destination_reference->type().getElementType(), exec().ctx().getReferenceType(target_type)))
    {
        // For target type T, destination reference type is &&T, so we need to dereference it to get &T.

        destination_reference = exec().performDereference(destination_reference);
    }

    Shared<lang::Value> assigned_value = getV(assignment_statement.assigned());
    assigned_value                     = lang::Type::makeMatching(target_type, assigned_value, exec());

    if (target_type.getStateCount().isUnit()) return {};

    Shared<lang::Value> destination_pointer = exec().computePointerFromReference(destination_reference);
    Shared<lang::Value> value_pointer       = exec().computeAddressOf(assigned_value);

    target_type.performCopyInitializer(destination_pointer, value_pointer, exec());

    return {};
}

std::any Builder::visit(Break const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(Continue const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(Delete const& delete_statement)
{
    Shared<lang::Value> to_delete        = getV(delete_statement.toDelete());
    bool const          is_buffer_delete = delete_statement.isBufferDelete();

    exec().runtime().deleteDynamic(to_delete, is_buffer_delete, exec());

    return {};
}

std::any Builder::visit(Erase const& erase_statement)
{
    auto const& variable = lang::Type::makeMatching<lang::Variable>(erase_statement.variable());

    variable.performFinalization(exec());

    return {};
}

std::any Builder::visit(ExpressionStatement const& expression_statement)
{
    getV(expression_statement.expression());

    return {};
}

std::any Builder::visit(If const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(LocalReferenceVariableDefinition const& local_reference_variable_definition)
{
    lang::Variable const& variable = local_reference_variable_definition.variable();

    variable.performInitialization(exec());

    return {};
}

std::any Builder::visit(LocalVariableDefinition const& local_variable_definition)
{
    lang::Variable const& variable = local_variable_definition.variable();

    variable.performInitialization(exec());

    return {};
}

std::any Builder::visit(Match const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(Return const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(While const&)
{
    throw std::logic_error("Not part of expanded AST");
}

std::any Builder::visit(Loop const&)
{
    throw std::logic_error("Not part of expanded AST");
}

Shared<lang::Constant> Builder::getC(Expression const& expression)
{
    Shared<lang::Value> value = getV(expression);
    return value.cast<lang::Constant>();
}

Shared<lang::Value> Builder::getV(Expression const& expression)
{
    std::any const value = visitTree(expression);
    return erasedCast<Shared<lang::Value>>(value);
}
