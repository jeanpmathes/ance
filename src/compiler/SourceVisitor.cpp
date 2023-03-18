#include "SourceVisitor.h"

#include <stdexcept>

#include "compiler/ProjectDescription.h"
#include "compiler/Unit.h"
#include "lang/ApplicationVisitor.h"

#include "lang/type/ArrayType.h"
#include "lang/type/BooleanType.h"
#include "lang/type/BufferType.h"
#include "lang/type/DoubleType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/HalfType.h"
#include "lang/type/PointerType.h"
#include "lang/type/QuadType.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SingleType.h"
#include "lang/type/SizeType.h"
#include "lang/type/UnsignedIntegerPointerType.h"
#include "lang/type/VectorType.h"
#include "lang/type/VoidType.h"

#include "lang/construct/constant/BooleanConstant.h"
#include "lang/construct/constant/CharConstant.h"
#include "lang/construct/constant/FloatConstant.h"
#include "lang/construct/constant/IntegerConstant.h"
#include "lang/construct/constant/NullConstant.h"
#include "lang/construct/constant/StringConstant.h"

#include "lang/construct/CodeBlock.h"
#include "lang/construct/Member.h"

#include "lang/AccessModifier.h"
#include "lang/Assigner.h"

SourceVisitor::SourceVisitor(Unit& unit) : file_context_(nullptr), unit_(unit) {}

void SourceVisitor::setFileContext(FileContext& file_context)
{
    file_context_ = &file_context;
}

std::any SourceVisitor::visitProjectFile(anceParser::ProjectFileContext* ctx)
{
    {// Project Description Function
        auto                   access = lang::AccessModifier::EXTERN_ACCESS;
        lang::Identifier const identifier =
            lang::Identifier::like(ProjectDescription::ANCE_PROJECT_DEFINITION_FUNCTION);
        lang::ResolvingHandle<lang::Type> return_type = unit_.globalScope().context().getVoidType();

        lang::Location const declaration_location = lang::Location::global();
        lang::Location const definition_location  = lang::Location::global();

        std::vector<Shared<lang::Parameter>> parameters;
        parameters.emplace_back(makeShared<lang::Parameter>(unit_.globalScope().context().getPointerType(
                                            lang::makeHandled<lang::Type>(lang::Identifier::like("Project"))),
                                        lang::Location::global(),
                                        lang::Identifier::like("project"),
                                        lang::Location::global()));

        lang::Location const return_type_location = lang::Location::global();

        auto function_block = lang::CodeBlock::makeInitial(location(ctx));

        for (auto code_context : ctx->code())
        {
            lang::CodeBlock& block     = *std::any_cast<lang::CodeBlock*>(visit(code_context));
            auto             block_ptr = Owned<lang::CodeBlock>(block);

            function_block->append(std::move(block_ptr));
        }

        Owned<Statement> block_statement = std::move(function_block);

        Owned<lang::FunctionDescription> description = makeOwned<lang::FunctionDescription>(access,
                                                                                            identifier,
                                                                                            return_type,
                                                                                            return_type_location,
                                                                                            parameters,
                                                                                            std::move(block_statement),
                                                                                            declaration_location,
                                                                                            definition_location);

        unit_.globalScope().addDescription(std::move(description));
    }

    {// Global Constants
        auto declare_constant = [this](std::string const& name, std::string const& value) {
            Owned<lang::VariableDescription> description = makeOwned<lang::VariableDescription>(
                lang::Identifier::like(name),
                unit_.globalScope().context().getFixedWidthIntegerType(32, false),
                lang::Location::global(),
                lang::AccessModifier::PRIVATE_ACCESS,
                makeOptional<Owned<Expression>>(
                    makeOwned<ConstantLiteral>(makeShared<lang::IntegerConstant>(
                                                   value,
                                                   10,
                                                   unit_.globalScope().context().getFixedWidthIntegerType(32, false)),
                                               lang::Location::global())),
                lang::Assigner::FINAL_COPY_ASSIGNMENT,
                true,
                lang::Location::global());

            unit_.globalScope().addDescription(std::move(description));
        };

        declare_constant("Executable", "1");
        declare_constant("Library", "2");
    }

    {// Project Description Struct
        std::vector<Owned<lang::Member>> members;

        auto push_member = [&members](lang::Identifier member_identifier, lang::ResolvingHandle<lang::Type> type) {
            members.emplace_back(makeOwned<lang::Member>(lang::AccessModifier::PUBLIC_ACCESS,
                                                         member_identifier,
                                                         type,
                                                         lang::Assigner::UNSPECIFIED,
                                                         std::nullopt,
                                                         lang::Location::global(),
                                                         lang::Location::global()));
        };

        auto string_type = unit_.globalScope().context().getPointerType(
            unit_.globalScope().context().getFixedWidthIntegerType(8, false));
        auto string_list_type = unit_.globalScope().context().getBufferType(string_type);

        push_member(lang::Identifier::like("name"), string_type);
        push_member(lang::Identifier::like("kind"), unit_.globalScope().context().getFixedWidthIntegerType(32, false));
        push_member(lang::Identifier::like("libraries"), string_list_type);
        push_member(lang::Identifier::like("library_paths"), string_list_type);
        push_member(lang::Identifier::like("binary_dependencies"), string_list_type);
        push_member(lang::Identifier::like("opt_level"),
                    unit_.globalScope().context().getFixedWidthIntegerType(32, false));
        push_member(lang::Identifier::like("warning_as_error_enabled"), unit_.globalScope().context().getBooleanType());
        push_member(lang::Identifier::like("ignoring_assert"), unit_.globalScope().context().getBooleanType());
        push_member(lang::Identifier::like("extra_emission_enabled"), unit_.globalScope().context().getBooleanType());
        push_member(lang::Identifier::like("runtime_excluded"), unit_.globalScope().context().getBooleanType());
        push_member(lang::Identifier::like("including_whole_archives"), unit_.globalScope().context().getBooleanType());

        Owned<lang::StructDescription> description =
            makeOwned<lang::StructDescription>(lang::AccessModifier::PUBLIC_ACCESS,
                                               lang::Identifier::like("Project"),
                                               std::move(members),
                                               lang::Location::global());

        unit_.globalScope().addDescription(std::move(description));
    }

    {// Exit Function
        auto                              access      = lang::AccessModifier::PUBLIC_ACCESS;
        lang::Identifier const            identifier  = lang::Identifier::like("exit");
        lang::ResolvingHandle<lang::Type> return_type = unit_.globalScope().context().getVoidType();

        lang::Location const declaration_location = lang::Location::global();
        lang::Location const definition_location  = lang::Location::global();

        std::vector<Shared<lang::Parameter>> parameters;
        parameters.emplace_back(
            makeShared<lang::Parameter>(unit_.globalScope().context().getFixedWidthIntegerType(32, false),
                                        lang::Location::global(),
                                        lang::Identifier::like("exitcode"),
                                        lang::Location::global()));

        lang::Location const return_type_location = lang::Location::global();

        auto             function_block  = lang::CodeBlock::makeInitial(location(ctx));
        Owned<Statement> block_statement = std::move(function_block);

        Owned<lang::FunctionDescription> description = makeOwned<lang::FunctionDescription>(access,
                                                                                            identifier,
                                                                                            return_type,
                                                                                            return_type_location,
                                                                                            parameters,
                                                                                            std::move(block_statement),
                                                                                            declaration_location,
                                                                                            definition_location);

        unit_.globalScope().addDescription(std::move(description));
    }

    return {};
}

std::any SourceVisitor::visitGlobal(anceParser::GlobalContext* ctx)
{
    for (auto description_context : ctx->description())
    {
        lang::Description& description = *std::any_cast<lang::Description*>(visit(description_context));
        unit_.globalScope().addDescription(Owned<lang::Description>(description));
    }

    return {};
}

std::any SourceVisitor::visitVariableDescription(anceParser::VariableDescriptionContext* ctx)
{
    auto       access      = std::any_cast<lang::AccessModifier>(visit(ctx->accessModifier()));
    bool const is_constant = ctx->CONST();

    Optional<lang::ResolvingHandle<lang::Type>> type;
    lang::Location                              type_location = lang::Location::global();

    if (ctx->type())
    {
        type          = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
        type_location = location(ctx->type());
    }

    lang::Identifier const identifier = ident(ctx->IDENTIFIER());

    Expression*    initial_value = nullptr;
    lang::Assigner assigner      = lang::Assigner::UNSPECIFIED;

    if (ctx->expression())
    {
        assigner      = std::any_cast<lang::Assigner>(visit(ctx->assigner()));
        initial_value = std::any_cast<Expression*>(visit(ctx->expression()));
    }

    return static_cast<lang::Description*>(new lang::VariableDescription(identifier,
                                                                         type,
                                                                         type_location,
                                                                         access,
                                                                         wrap(initial_value),

                                                                         assigner,
                                                                         is_constant,

                                                                         location(ctx)));
}

std::any SourceVisitor::visitStructDescription(anceParser::StructDescriptionContext* ctx)
{
    auto                   access     = std::any_cast<lang::AccessModifier>(visit(ctx->accessModifier()));
    lang::Identifier const identifier = ident(ctx->IDENTIFIER());

    std::vector<Owned<lang::Member>> members;

    for (auto member : ctx->member()) { members.emplace_back(*std::any_cast<lang::Member*>(visit(member))); }

    return static_cast<lang::Description*>(
        new lang::StructDescription(access, identifier, std::move(members), location(ctx)));
}

std::any SourceVisitor::visitMember(anceParser::MemberContext* ctx)
{
    auto                   access     = std::any_cast<lang::AccessModifier>(visit(ctx->accessModifier()));
    lang::Identifier const identifier = ident(ctx->IDENTIFIER());
    auto                   type       = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));

    ConstantExpression* const_expr = nullptr;
    lang::Assigner      assigner   = lang::Assigner::UNSPECIFIED;

    if (ctx->literalExpression())
    {
        assigner = std::any_cast<lang::Assigner>(visit(ctx->assigner()));

        auto* expr = std::any_cast<Expression*>(visit(ctx->literalExpression()));
        const_expr = dynamic_cast<ConstantExpression*>(expr);
    }

    return new lang::Member(access, identifier, type, assigner, wrap(const_expr), location(ctx), location(ctx->type()));
}

std::any SourceVisitor::visitFunctionDescription(anceParser::FunctionDescriptionContext* ctx)
{
    auto                              access     = std::any_cast<lang::AccessModifier>(visit(ctx->accessModifier()));
    lang::Identifier const            identifier = ident(ctx->IDENTIFIER());
    lang::ResolvingHandle<lang::Type> return_type =
        ctx->type() ? erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()))
                    : unit_.globalScope().context().getVoidType();

    lang::Location const declaration_location = location(ctx);
    lang::Location const definition_location =
        ctx->functionBlock() == nullptr ? declaration_location : location(ctx->functionBlock());

    auto parameters = std::any_cast<std::vector<lang::Parameter*>>(visit(ctx->parameters()));

    std::vector<Shared<lang::Parameter>> shared_parameters;
    shared_parameters.reserve(parameters.size());
    for (lang::Parameter* parameter_ptr : parameters) { shared_parameters.emplace_back(*parameter_ptr); }

    lang::Location const return_type_location = ctx->type() ? location(ctx->type()) : lang::Location::global();

    Optional<Owned<Statement>> code;

    if (ctx->functionBlock() != nullptr)
    {
        Owned<lang::CodeBlock> function_block = lang::CodeBlock::makeInitial(location(ctx));

        for (auto code_context : ctx->functionBlock()->code())
        {
            lang::CodeBlock& block     = *std::any_cast<lang::CodeBlock*>(visit(code_context));
            auto             block_ptr = Owned<lang::CodeBlock>(block);

            function_block->append(std::move(block_ptr));
        }

        code = std::move(function_block);
    }

    return static_cast<lang::Description*>(new lang::FunctionDescription(access,
                                                                         identifier,
                                                                         return_type,
                                                                         return_type_location,
                                                                         shared_parameters,
                                                                         std::move(code),
                                                                         declaration_location,
                                                                         definition_location));
}

std::any SourceVisitor::visitParameters(anceParser::ParametersContext* ctx)
{
    std::vector<lang::Parameter*> params;

    for (auto* param : ctx->parameter()) { params.push_back(std::any_cast<lang::Parameter*>(visit(param))); }

    return params;
}

std::any SourceVisitor::visitParameter(anceParser::ParameterContext* ctx)
{
    auto                   type       = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::Identifier const identifier = ident(ctx->IDENTIFIER());

    return new lang::Parameter(type, location(ctx->type()), identifier, location(ctx));
}

std::any SourceVisitor::visitAliasDescription(anceParser::AliasDescriptionContext* ctx)
{
    auto                   access     = std::any_cast<lang::AccessModifier>(visit(ctx->accessModifier()));
    auto                   other      = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::Identifier const identifier = ident(ctx->IDENTIFIER());

    return static_cast<lang::Description*>(
        new lang::AliasDescription(access, identifier, other, location(ctx), location(ctx->type())));
}

std::any SourceVisitor::visitBlock(anceParser::BlockContext* ctx)
{
    lang::CodeBlock* block = unwrap(lang::CodeBlock::makeScoped(location(ctx)));

    for (auto code_context : ctx->code())
    {
        lang::CodeBlock& code     = *std::any_cast<lang::CodeBlock*>(visit(code_context));
        auto             code_ptr = Owned<lang::CodeBlock>(code);

        block->append(std::move(code_ptr));
    }

    return block;
}

std::any SourceVisitor::visitExpressionStatement(anceParser::ExpressionStatementContext* ctx)
{
    BuildableExpression* expression =
        dynamic_cast<BuildableExpression*>(std::any_cast<Expression*>(visit(ctx->independentExpression())));
    Owned<BuildableExpression> buildable_expression(*expression);

    auto statement = makeOwned<ExpressionStatement>(std::move(buildable_expression), location(ctx));
    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx)
{
    lang::Identifier const identifier = ident(ctx->IDENTIFIER());

    Optional<lang::ResolvingHandle<lang::Type>> type;
    if (ctx->type()) type = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));

    lang::Assigner assigner {};
    Expression*    assigned;

    if (ctx->expression())
    {
        assigner = std::any_cast<lang::Assigner>(visit(ctx->assigner()));
        assigned = std::any_cast<Expression*>(visit(ctx->expression()));
    }
    else
    {
        assigner = lang::Assigner::UNSPECIFIED;
        assigned = nullptr;
    }

    auto statement = makeOwned<LocalVariableDefinition>(identifier,
                                                        type,
                                                        ctx->type() ? location(ctx->type()) : lang::Location::global(),
                                                        assigner,
                                                        wrap(assigned),
                                                        location(ctx));

    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitLocalReferenceDefinition(anceParser::LocalReferenceDefinitionContext* ctx)
{
    auto                   type       = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::Identifier const identifier = ident(ctx->IDENTIFIER());

    Expression& ref = *std::any_cast<Expression*>(visit(ctx->bindRef()));

    auto statement = makeOwned<LocalReferenceVariableDefinition>(identifier,
                                                                 type,
                                                                 location(ctx->type()),
                                                                 Owned<Expression>(ref),
                                                                 location(ctx));

    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitDropStatement(anceParser::DropStatementContext* ctx)
{
    lang::Identifier const identifier = ident(ctx->IDENTIFIER());
    auto                   variable   = lang::makeHandled<lang::Variable>(identifier);

    auto statement = makeOwned<Drop>(variable, location(ctx));
    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitAssignment(anceParser::AssignmentContext* ctx)
{
    Expression& assignable = *std::any_cast<Expression*>(visit(ctx->assignable));
    auto        assigner   = std::any_cast<lang::Assigner>(visit(ctx->assigner()));
    Expression& assigned   = *std::any_cast<Expression*>(visit(ctx->assigned));

    auto statement =
        makeOwned<Assignment>(Owned<Expression>(assignable), assigner, Owned<Expression>(assigned), location(ctx));

    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitDeleteStatement(anceParser::DeleteStatementContext* ctx)
{
    Expression& expression    = *std::any_cast<Expression*>(visit(ctx->expression()));
    bool const  delete_buffer = ctx->BUFFER();

    auto statement = makeOwned<Delete>(Owned<Expression>(expression), delete_buffer, location(ctx));

    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitBreakStatement(anceParser::BreakStatementContext* ctx)
{
    auto statement = makeOwned<Break>(location(ctx));
    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitContinueStatement(anceParser::ContinueStatementContext* ctx)
{
    auto statement = makeOwned<Continue>(location(ctx));
    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitReturnStatement(anceParser::ReturnStatementContext* ctx)
{
    Expression* return_value = nullptr;

    if (ctx->expression() != nullptr) { return_value = std::any_cast<Expression*>(visit(ctx->expression())); }

    auto statement = makeOwned<Return>(wrap(return_value), location(ctx));

    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitAssertStatement(anceParser::AssertStatementContext* ctx)
{
    Expression& condition = *std::any_cast<Expression*>(visit(ctx->expression()));

    auto statement = makeOwned<Assertion>(Owned<Expression>(condition), location(ctx));
    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitIfStatement(anceParser::IfStatementContext* ctx)
{
    Expression& condition = *std::any_cast<Expression*>(visit(ctx->expression()));
    bool const  has_else  = ctx->elseBlock != nullptr;

    auto if_block = Owned<lang::CodeBlock>(*std::any_cast<lang::CodeBlock*>(visit(ctx->ifBlock)));

    Optional<Owned<Statement>> else_block;

    if (has_else) { else_block = Owned<Statement>(*std::any_cast<lang::CodeBlock*>(visit(ctx->elseBlock))); }

    auto statement =
        makeOwned<If>(Owned<Expression>(condition), std::move(if_block), std::move(else_block), location(ctx));
    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitWhileStatement(anceParser::WhileStatementContext* ctx)
{
    Expression& condition = *std::any_cast<Expression*>(visit(ctx->expression()));

    auto block = (Owned<lang::CodeBlock>(*std::any_cast<lang::CodeBlock*>(visit(ctx->code()))));

    auto statement = makeOwned<While>(Owned<Expression>(condition), std::move(block), location(ctx));
    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitMatchStatement(anceParser::MatchStatementContext* ctx)
{
    Expression& expression = *std::any_cast<Expression*>(visit(ctx->expression()));

    std::vector<Owned<Case>> cases;
    for (auto& case_ctx : ctx->matchCase())
    {
        Case& case_instance = *std::any_cast<Case*>(visit(case_ctx));
        cases.emplace_back(case_instance);
    }

    auto statement = makeOwned<Match>(std::move(cases), Owned<Expression>(expression), location(ctx));
    return unwrap(lang::CodeBlock::makeWithStatement(std::move(statement)));
}

std::any SourceVisitor::visitLiteralCase(anceParser::LiteralCaseContext* ctx)
{
    lang::CodeBlock& code_block = *std::any_cast<lang::CodeBlock*>(visit(ctx->code()));
    auto             block      = Owned<lang::CodeBlock>(code_block);

    std::vector<Owned<ConstantExpression>> cases;
    for (auto& condition_ctx : ctx->literalExpression())
    {
        auto condition = dynamic_cast<ConstantExpression*>(std::any_cast<Expression*>(visit(condition_ctx)));
        cases.emplace_back(*condition);
    }

    return Case::createCase(std::move(cases), std::move(block));
}

std::any SourceVisitor::visitDefaultCase(anceParser::DefaultCaseContext* ctx)
{
    lang::CodeBlock& code_block = *std::any_cast<lang::CodeBlock*>(visit(ctx->code()));
    auto             block      = Owned<lang::CodeBlock>(code_block);

    return Case::createDefault(std::move(block));
}

std::any SourceVisitor::visitMemberAccess(anceParser::MemberAccessContext* ctx)
{
    Expression&            accessed = *std::any_cast<Expression*>(visit(ctx->accessed));
    lang::Identifier const member   = ident(ctx->IDENTIFIER());

    return static_cast<Expression*>(new MemberAccess(Owned<Expression>(accessed), member, location(ctx)));
}

std::any SourceVisitor::visitFunctionCall(anceParser::FunctionCallContext* ctx)
{
    Optional<lang::ResolvingHandle<lang::FunctionGroup>> function_group;
    Optional<lang::ResolvingHandle<lang::Type>>          constructed_type;

    if (ctx->type()) { constructed_type = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type())); }
    else
    {
        lang::Identifier const identifier = ident(ctx->IDENTIFIER());

        function_group   = lang::makeHandled<lang::FunctionGroup>(identifier);
        constructed_type = lang::makeHandled<lang::Type>(identifier);
    }

    auto arguments = std::any_cast<std::vector<Expression*>>(visit(ctx->arguments()));

    std::vector<Owned<Expression>> unique_expressions;
    unique_expressions.reserve(arguments.size());
    for (Expression* argument_ptr : arguments) { unique_expressions.emplace_back(*argument_ptr); }

    return static_cast<Expression*>(new FunctionCall(std::move(function_group),
                                                     constructed_type.value(),
                                                     std::move(unique_expressions),
                                                     location(ctx)));
}

std::any SourceVisitor::visitArguments(anceParser::ArgumentsContext* ctx)
{
    std::vector<Expression*> arguments;

    for (auto* argument : ctx->expression()) { arguments.push_back(std::any_cast<Expression*>(visit(argument))); }

    return arguments;
}

std::any SourceVisitor::visitVariableAccess(anceParser::VariableAccessContext* ctx)
{
    lang::Identifier const identifier = ident(ctx->IDENTIFIER());
    auto                   variable   = lang::makeHandled<lang::Variable>(identifier);

    return static_cast<Expression*>(new VariableAccess(variable, location(ctx)));
}

std::any SourceVisitor::visitAllocation(anceParser::AllocationContext* ctx)
{
    auto        allocator = std::any_cast<Runtime::Allocator>(visit(ctx->allocator()));
    auto        type      = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    Expression* count     = nullptr;

    if (ctx->expression()) { count = std::any_cast<Expression*>(visit(ctx->expression())); }

    return static_cast<Expression*>(new Allocation(allocator,
                                                   type,
                                                   wrap(count),
                                                   location(ctx),
                                                   location(ctx->type()),
                                                   unit_.globalScope().context()));
}

std::any SourceVisitor::visitAddressof(anceParser::AddressofContext* ctx)
{
    Expression& arg = *std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new Addressof(Owned<Expression>(arg), location(ctx)));
}

std::any SourceVisitor::visitBindReference(anceParser::BindReferenceContext* ctx)
{
    Expression& value = *std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new BindRef(Owned<Expression>(value), location(ctx)));
}

std::any SourceVisitor::visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx)
{
    Expression& address = *std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new BindRefTo(Owned<Expression>(address), location(ctx)));
}

std::any SourceVisitor::visitSizeofType(anceParser::SizeofTypeContext* ctx)
{
    auto type = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));

    return static_cast<Expression*>(new SizeofType(type, location(ctx->type()), location(ctx)));
}

std::any SourceVisitor::visitSizeofExpression(anceParser::SizeofExpressionContext* ctx)
{
    Expression& expr = *std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new SizeofExpression(Owned<Expression>(expr), location(ctx)));
}

std::any SourceVisitor::visitSubscript(anceParser::SubscriptContext* ctx)
{
    Expression& indexed = *std::any_cast<Expression*>(visit(ctx->indexed));
    Expression& index   = *std::any_cast<Expression*>(visit(ctx->index));

    return static_cast<Expression*>(new Subscript(Owned<Expression>(indexed), Owned<Expression>(index), location(ctx)));
}

std::any SourceVisitor::visitUnaryOperation(anceParser::UnaryOperationContext* ctx)
{
    auto        op    = std::any_cast<lang::UnaryOperator>(visit(ctx->unaryOperator()));
    Expression& value = *std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new UnaryOperation(op, Owned<Expression>(value), location(ctx)));
}

std::any SourceVisitor::visitBinaryOperation(anceParser::BinaryOperationContext* ctx)
{
    Expression& left  = *std::any_cast<Expression*>(visit(ctx->left));
    Expression& right = *std::any_cast<Expression*>(visit(ctx->right));

    Optional<lang::BinaryOperator> op;

    if (ctx->binaryOperatorMultiplicative())
        op = std::any_cast<lang::BinaryOperator>(visit(ctx->binaryOperatorMultiplicative()));
    if (ctx->binaryOperatorAdditive()) op = std::any_cast<lang::BinaryOperator>(visit(ctx->binaryOperatorAdditive()));
    if (ctx->binaryOperatorRelational())
        op = std::any_cast<lang::BinaryOperator>(visit(ctx->binaryOperatorRelational()));
    if (ctx->binaryOperatorEquality()) op = std::any_cast<lang::BinaryOperator>(visit(ctx->binaryOperatorEquality()));
    if (ctx->binaryOperatorBitwise()) op = std::any_cast<lang::BinaryOperator>(visit(ctx->binaryOperatorBitwise()));
    if (ctx->binaryOperatorShift()) op = std::any_cast<lang::BinaryOperator>(visit(ctx->binaryOperatorShift()));

    assert(op.hasValue());

    return static_cast<Expression*>(
        new BinaryOperation(Owned<Expression>(left), op.value(), Owned<Expression>(right), location(ctx)));
}

std::any SourceVisitor::visitParenthesis(anceParser::ParenthesisContext* ctx)
{
    Expression& contained = *std::any_cast<Expression*>(visit(ctx->expression()));
    return static_cast<Expression*>(new Parenthesis(Owned<Expression>(contained), location(ctx)));
}

std::any SourceVisitor::visitLogicalAnd(anceParser::LogicalAndContext* ctx)
{
    bool const  negated = ctx->NOT();
    Expression& left    = *std::any_cast<Expression*>(visit(ctx->left));
    Expression& right   = *std::any_cast<Expression*>(visit(ctx->right));

    return static_cast<Expression*>(new And(negated, Owned<Expression>(left), Owned<Expression>(right), location(ctx)));
}

std::any SourceVisitor::visitLogicalOr(anceParser::LogicalOrContext* ctx)
{
    bool const  negated = ctx->NOT();
    Expression& left    = *std::any_cast<Expression*>(visit(ctx->left));
    Expression& right   = *std::any_cast<Expression*>(visit(ctx->right));

    return static_cast<Expression*>(new Or(negated, Owned<Expression>(left), Owned<Expression>(right), location(ctx)));
}

std::any SourceVisitor::visitIfExpression(anceParser::IfExpressionContext* ctx)
{
    Expression& condition = *std::any_cast<Expression*>(visit(ctx->condition));

    Expression& then_expression = *std::any_cast<Expression*>(visit(ctx->thenBlock));
    Expression& else_expression = *std::any_cast<Expression*>(visit(ctx->elseBlock));

    return static_cast<Expression*>(new IfSelect(Owned<Expression>(condition),
                                                 Owned<Expression>(then_expression),
                                                 Owned<Expression>(else_expression),
                                                 location(ctx)));
}

std::any SourceVisitor::visitMatchExpression(anceParser::MatchExpressionContext* ctx)
{
    Expression& expression = *std::any_cast<Expression*>(visit(ctx->expression()));

    std::vector<Owned<Case>> cases;
    for (auto& case_ctx : ctx->matchExpressionCase())
    {
        Case& case_instance = *std::any_cast<Case*>(visit(case_ctx));
        cases.emplace_back(case_instance);
    }

    return static_cast<Expression*>(new MatchSelect(Owned<Expression>(expression), std::move(cases), location(ctx)));
}

std::any SourceVisitor::visitIndirection(anceParser::IndirectionContext* ctx)
{
    Expression& value = *std::any_cast<Expression*>(visit(ctx->expression()));
    return static_cast<Expression*>(new Indirection(Owned<Expression>(value), location(ctx)));
}

std::any SourceVisitor::visitVectorDefinition(anceParser::VectorDefinitionContext* ctx)
{
    Optional<lang::ResolvingHandle<lang::Type>> type;
    lang::Location                              type_location = lang::Location::global();

    if (ctx->type())
    {
        type          = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
        type_location = location(ctx->type());
    }

    std::vector<Owned<Expression>> elements;

    for (auto& element_ctx : ctx->expression())
    {
        Expression& element = *std::any_cast<Expression*>(visit(element_ctx));
        elements.emplace_back(element);
    }

    return static_cast<Expression*>(new VectorDefinition(type, type_location, std::move(elements), location(ctx)));
}

std::any SourceVisitor::visitArrayDefinition(anceParser::ArrayDefinitionContext* ctx)
{
    Optional<lang::ResolvingHandle<lang::Type>> type;
    lang::Location                              type_location = lang::Location::global();

    if (ctx->type())
    {
        type          = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
        type_location = location(ctx->type());
    }

    std::vector<Owned<Expression>> elements;

    for (auto& element_ctx : ctx->expression())
    {
        Expression& element = *std::any_cast<Expression*>(visit(element_ctx));
        elements.emplace_back(element);
    }

    return static_cast<Expression*>(new ArrayDefinition(type, type_location, std::move(elements), location(ctx)));
}

std::any SourceVisitor::visitDefaultExpressionCase(anceParser::DefaultExpressionCaseContext* ctx)
{
    Expression& exp        = *std::any_cast<Expression*>(visit(ctx->expression()));
    auto        expression = Owned<Expression>(exp);

    return Case::createDefault(std::move(expression));
}

std::any SourceVisitor::visitLiteralExpressionCase(anceParser::LiteralExpressionCaseContext* ctx)
{
    Expression& exp   = *std::any_cast<Expression*>(visit(ctx->expression()));
    auto        block = Owned<Expression>(exp);

    std::vector<Owned<ConstantExpression>> cases;
    for (auto& condition_ctx : ctx->literalExpression())
    {
        auto& condition = *dynamic_cast<ConstantExpression*>(std::any_cast<Expression*>(visit(condition_ctx)));
        cases.emplace_back(condition);
    }

    return Case::createCase(std::move(cases), std::move(block));
}

std::any SourceVisitor::visitStringLiteral(anceParser::StringLiteralContext* ctx)
{
    std::string prefix;

    if (ctx->prefix) { prefix = ctx->prefix->getText(); }

    Shared<lang::Constant> string =
        makeShared<lang::StringConstant>(prefix, ctx->STRING()->getText(), unit_.globalScope().context());
    return static_cast<Expression*>(new ConstantLiteral(string, location(ctx)));
}

std::any SourceVisitor::visitCharLiteral(anceParser::CharLiteralContext* ctx)
{
    std::string prefix;

    if (ctx->prefix) { prefix = ctx->prefix->getText(); }

    Shared<lang::Constant> byte =
        makeShared<lang::CharConstant>(prefix, ctx->CHAR()->getText(), unit_.globalScope().context());
    return static_cast<Expression*>(new ConstantLiteral(byte, location(ctx)));
}

std::any SourceVisitor::visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx)
{
    Optional<Shared<lang::Constant>> flt;

    if (ctx->HALF())
    {
        flt = makeShared<lang::FloatConstant>(ctx->getText().erase(ctx->getText().size() - 1),
                                              llvm::APFloat::IEEEhalf(),
                                              unit_.globalScope().context().getHalfType());
    }

    if (ctx->SINGLE())
    {
        flt = makeShared<lang::FloatConstant>(ctx->getText().erase(ctx->getText().size() - 1),
                                              llvm::APFloat::IEEEsingle(),
                                              unit_.globalScope().context().getSingleType());
    }

    if (ctx->DOUBLE())
    {
        flt = makeShared<lang::FloatConstant>(ctx->getText().erase(ctx->getText().size() - 1),
                                              llvm::APFloat::IEEEdouble(),
                                              unit_.globalScope().context().getDoubleType());
    }

    if (ctx->QUAD())
    {
        flt = makeShared<lang::FloatConstant>(ctx->getText().erase(ctx->getText().size() - 1),
                                              llvm::APFloat::IEEEquad(),
                                              unit_.globalScope().context().getQuadType());
    }

    return static_cast<Expression*>(new ConstantLiteral(flt.value(), location(ctx)));
}

std::any SourceVisitor::visitTrue(anceParser::TrueContext* ctx)
{
    Shared<lang::Constant> constant = lang::BooleanConstant::createTrue(unit_.globalScope().context());
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitFalse(anceParser::FalseContext* ctx)
{
    Shared<lang::Constant> constant = lang::BooleanConstant::createFalse(unit_.globalScope().context());
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitNull(anceParser::NullContext* ctx)
{
    Shared<lang::Constant> constant = lang::NullConstant::create(unit_.globalScope().context());
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitSizeLiteral(anceParser::SizeLiteralContext* ctx)
{
    std::string const      value = ctx->INTEGER()->getText();
    Shared<lang::Constant> constant =
        makeShared<lang::IntegerConstant>(value, 10, unit_.globalScope().context().getSizeType());

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitDiffLiteral(anceParser::DiffLiteralContext* ctx)
{
    std::string const      value = ctx->SIGNED_INTEGER()->getText();
    Shared<lang::Constant> constant =
        makeShared<lang::IntegerConstant>(value, 10, unit_.globalScope().context().getDiffType());

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitUiptrLiteral(anceParser::UiptrLiteralContext* ctx)
{
    std::string value = ctx->HEX_INTEGER()->getText();
    value.erase(0, 2);

    Shared<lang::Constant> constant =
        makeShared<lang::IntegerConstant>(value, 16, unit_.globalScope().context().getUnsignedIntegerPointerType());

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitNormalInteger(anceParser::NormalIntegerContext* ctx)
{
    bool const        is_signed    = ctx->svalue;
    std::string const literal_text = is_signed ? ctx->svalue->getText() : ctx->uvalue->getText();

    Optional<Shared<lang::Constant>> integer_constant;

    if (ctx->width)
    {
        uint64_t const size = parseIntegerTypeSize(ctx->width->getText());
        integer_constant =
            makeShared<lang::IntegerConstant>(literal_text,
                                              10,
                                              unit_.globalScope().context().getFixedWidthIntegerType(size, is_signed));
    }
    else
    {
        integer_constant = makeShared<lang::IntegerConstant>(literal_text, is_signed, unit_.globalScope().context());
    }

    return static_cast<Expression*>(new ConstantLiteral(integer_constant.value(), location(ctx)));
}

std::any SourceVisitor::visitSpecialInteger(anceParser::SpecialIntegerContext* ctx)
{
    uint64_t const size = parseIntegerTypeSize(ctx->width->getText());

    std::string integer_str;
    int         radix;

    if (ctx->HEX_INTEGER())
    {
        integer_str = ctx->HEX_INTEGER()->getText();
        radix       = 16;
    }

    if (ctx->BIN_INTEGER())
    {
        integer_str = ctx->BIN_INTEGER()->getText();
        radix       = 2;
    }

    if (ctx->OCT_INTEGER())
    {
        integer_str = ctx->OCT_INTEGER()->getText();
        radix       = 8;
    }

    integer_str.erase(0, 2);

    Shared<lang::Constant> integer_constant =
        makeShared<lang::IntegerConstant>(integer_str,
                                          radix,
                                          unit_.globalScope().context().getFixedWidthIntegerType(size, false));
    return static_cast<Expression*>(new ConstantLiteral(integer_constant, location(ctx)));
}

std::any SourceVisitor::visitIntegerType(anceParser::IntegerTypeContext* ctx)
{
    std::string integer_type_str = ctx->NATIVE_INTEGER_TYPE()->getText();

    bool const     is_signed = integer_type_str[0] == 'i';
    uint64_t const size      = parseIntegerTypeSize(integer_type_str.substr(1));

    lang::ResolvingHandle<lang::Type> type = unit_.globalScope().context().getFixedWidthIntegerType(size, is_signed);
    return erase(type);
}

std::any SourceVisitor::visitBooleanType(anceParser::BooleanTypeContext*)
{
    return erase(unit_.globalScope().context().getBooleanType());
}

std::any SourceVisitor::visitArrayType(anceParser::ArrayTypeContext* ctx)
{
    auto                              element_type = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    uint64_t const                    size         = parseCompoundTypeSize(ctx->INTEGER()->getText());
    lang::ResolvingHandle<lang::Type> type         = unit_.globalScope().context().getArrayType(element_type, size);

    return erase(type);
}

std::any SourceVisitor::visitVectorType(anceParser::VectorTypeContext* ctx)
{
    auto                              element_type = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    uint64_t const                    size         = parseCompoundTypeSize(ctx->INTEGER()->getText());
    lang::ResolvingHandle<lang::Type> type         = unit_.globalScope().context().getVectorType(element_type, size);

    return erase(type);
}

std::any SourceVisitor::visitKeywordType(anceParser::KeywordTypeContext* ctx)
{
    return erase(unit_.globalScope().getType(createIdentifier(ctx->getText(), location(ctx))).value());
}

std::any SourceVisitor::visitPointer(anceParser::PointerContext* ctx)
{
    auto                              element_type = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::ResolvingHandle<lang::Type> type         = unit_.globalScope().context().getPointerType(element_type);

    return erase(type);
}

std::any SourceVisitor::visitBuffer(anceParser::BufferContext* ctx)
{
    auto                              element_type = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::ResolvingHandle<lang::Type> type         = unit_.globalScope().context().getBufferType(element_type);

    return erase(type);
}

std::any SourceVisitor::visitReference(anceParser::ReferenceContext* ctx)
{
    auto                              element_type = erasedCast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::ResolvingHandle<lang::Type> type         = unit_.globalScope().context().getReferenceType(element_type);

    return erase(type);
}

std::any SourceVisitor::visitCustom(anceParser::CustomContext* ctx)
{
    return erase(lang::makeHandled<lang::Type>(createIdentifier(ctx->getText(), location(ctx))));
}

std::any SourceVisitor::visitPublic(anceParser::PublicContext*)
{
    lang::AccessModifier access_modifier = lang::AccessModifier::PUBLIC_ACCESS;
    return access_modifier;
}

std::any SourceVisitor::visitPrivate(anceParser::PrivateContext*)
{
    lang::AccessModifier access_modifier = lang::AccessModifier::PRIVATE_ACCESS;
    return access_modifier;
}

std::any SourceVisitor::visitExtern(anceParser::ExternContext*)
{
    lang::AccessModifier access_modifier = lang::AccessModifier::EXTERN_ACCESS;
    return access_modifier;
}

std::any SourceVisitor::visitAutomatic(anceParser::AutomaticContext*)
{
    Runtime::Allocator const allocator = Runtime::Allocator::AUTOMATIC;
    return allocator;
}

std::any SourceVisitor::visitDynamic(anceParser::DynamicContext*)
{
    Runtime::Allocator const allocator = Runtime::Allocator::DYNAMIC;
    return allocator;
}

std::any SourceVisitor::visitCopyAssignment(anceParser::CopyAssignmentContext*)
{
    lang::Assigner assigner = lang::Assigner::COPY_ASSIGNMENT;
    return assigner;
}

std::any SourceVisitor::visitMoveAssignment(anceParser::MoveAssignmentContext*)
{
    assert(false && "Move assignment currently not supported.");

    lang::Assigner assigner = lang::Assigner::MOVE_ASSIGNMENT;
    return assigner;
}

std::any SourceVisitor::visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext*)
{
    lang::Assigner assigner = lang::Assigner::FINAL_COPY_ASSIGNMENT;
    return assigner;
}

std::any SourceVisitor::visitBitwiseNot(anceParser::BitwiseNotContext*)
{
    lang::UnaryOperator op = lang::UnaryOperator::BITWISE_NOT;
    return op;
}

std::any SourceVisitor::visitNot(anceParser::NotContext*)
{
    lang::UnaryOperator op = lang::UnaryOperator::NOT;
    return op;
}

std::any SourceVisitor::visitNegation(anceParser::NegationContext*)
{
    lang::UnaryOperator op = lang::UnaryOperator::NEGATION;
    return op;
}

std::any SourceVisitor::visitAddition(anceParser::AdditionContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::ADDITION;
    return op;
}

std::any SourceVisitor::visitSubtraction(anceParser::SubtractionContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::SUBTRACTION;
    return op;
}

std::any SourceVisitor::visitMultiplication(anceParser::MultiplicationContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::MULTIPLICATION;
    return op;
}

std::any SourceVisitor::visitDivision(anceParser::DivisionContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::DIVISION;
    return op;
}

std::any SourceVisitor::visitRemainder(anceParser::RemainderContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::REMAINDER;
    return op;
}

std::any SourceVisitor::visitLessThan(anceParser::LessThanContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::LESS_THAN;
    return op;
}

std::any SourceVisitor::visitLessThanOrEqual(anceParser::LessThanOrEqualContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::LESS_THAN_OR_EQUAL;
    return op;
}

std::any SourceVisitor::visitGreaterThan(anceParser::GreaterThanContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::GREATER_THAN;
    return op;
}

std::any SourceVisitor::visitGreaterThanOrEqual(anceParser::GreaterThanOrEqualContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::GREATER_THAN_OR_EQUAL;
    return op;
}

std::any SourceVisitor::visitEqual(anceParser::EqualContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::EQUAL;
    return op;
}

std::any SourceVisitor::visitNotEqual(anceParser::NotEqualContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::NOT_EQUAL;
    return op;
}

std::any SourceVisitor::visitBitwiseAnd(anceParser::BitwiseAndContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::BITWISE_AND;
    return op;
}

std::any SourceVisitor::visitBitwiseOr(anceParser::BitwiseOrContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::BITWISE_OR;
    return op;
}

std::any SourceVisitor::visitBitwiseXor(anceParser::BitwiseXorContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::BITWISE_XOR;
    return op;
}

std::any SourceVisitor::visitLeftShift(anceParser::LeftShiftContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::SHIFT_LEFT;
    return op;
}

std::any SourceVisitor::visitRightShift(anceParser::RightShiftContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::SHIFT_RIGHT;
    return op;
}

lang::Location SourceVisitor::location(antlr4::ParserRuleContext* ctx)
{
    size_t const start_line   = ctx->getStart()->getLine();
    size_t const start_column = file_context_->getUtf8Index(start_line, ctx->getStart()->getCharPositionInLine()) + 1;

    size_t const end_line   = ctx->getStop()->getLine();
    size_t const end_column = file_context_->getUtf8Index(end_line, ctx->getStop()->getCharPositionInLine())
                            + ctx->getStop()->getText().size();

    return {start_line, start_column, end_line, end_column, file_context_->getFileIndex()};
}

lang::Identifier SourceVisitor::ident(antlr4::tree::TerminalNode* i)
{
    std::string const text = i->getText();

    auto         token        = i->getSymbol();
    size_t const start_line   = token->getLine();
    size_t const start_column = file_context_->getUtf8Index(start_line, token->getCharPositionInLine()) + 1;

    size_t const end_line   = start_line;
    size_t const end_column = start_column + text.size() - 1;

    return createIdentifier(text, {start_line, start_column, end_line, end_column, file_context_->getFileIndex()});
}

lang::Identifier SourceVisitor::createIdentifier(std::string const& text, lang::Location location)
{
    return lang::Identifier::like(text, location);
}

uint64_t SourceVisitor::parseIntegerTypeSize(std::string const& str)
{
    return parseInRange(str, lang::FixedWidthIntegerType::MAX_INTEGER_SIZE);
}

uint64_t SourceVisitor::parseCompoundTypeSize(std::string const& str)
{
    return parseInRange(str, lang::ArrayType::MAX_ARRAY_TYPE_SIZE);
}

uint64_t SourceVisitor::parseInRange(std::string const& str, uint64_t max)
{
    uint64_t value;

    try
    {
        value = std::stoull(str);
    }
    catch (std::exception const&)
    {
        value = max + 1;
    }

    if (value > max) { value = max + 1; }

    return value;
}
