#include "SourceVisitor.h"

#include <stdexcept>

#include "compiler/Application.h"
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

#include "lang/statement/Assertion.h"
#include "lang/statement/Assignment.h"
#include "lang/statement/Delete.h"
#include "lang/statement/Drop.h"
#include "lang/statement/ExpressionStatement.h"
#include "lang/statement/If.h"
#include "lang/statement/LocalReferenceVariableDefinition.h"
#include "lang/statement/LocalVariableDefinition.h"
#include "lang/statement/Match.h"
#include "lang/statement/Return.h"
#include "lang/statement/While.h"

#include "lang/expression/Addressof.h"
#include "lang/expression/Allocation.h"
#include "lang/expression/And.h"
#include "lang/expression/ArrayDefinition.h"
#include "lang/expression/BinaryOperation.h"
#include "lang/expression/BindRef.h"
#include "lang/expression/BindRefTo.h"
#include "lang/expression/ConstantLiteral.h"
#include "lang/expression/FunctionCall.h"
#include "lang/expression/IfSelect.h"
#include "lang/expression/Indirection.h"
#include "lang/expression/MatchSelect.h"
#include "lang/expression/MemberAccess.h"
#include "lang/expression/Or.h"
#include "lang/expression/Parenthesis.h"
#include "lang/expression/SizeofExpression.h"
#include "lang/expression/SizeofType.h"
#include "lang/expression/Subscript.h"
#include "lang/expression/UnaryOperation.h"
#include "lang/expression/VariableAccess.h"
#include "lang/expression/VectorDefinition.h"

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

SourceVisitor::SourceVisitor(Application& application) : application_(application) {}

std::any SourceVisitor::visitVariableDeclaration(anceParser::VariableDeclarationContext* ctx)
{
    lang::AccessModifier access      = std::any_cast<lang::AccessModifier>(visit(ctx->accessModifier()));
    bool                 is_constant = ctx->CONST();

    std::optional<lang::ResolvingHandle<lang::Type>> type;
    lang::Location                                   type_location = lang::Location::global();

    if (ctx->type())
    {
        type          = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
        type_location = location(ctx->type());
    }

    lang::Identifier identifier = ident(ctx->IDENTIFIER());

    Expression*    initial_value;
    lang::Assigner assigner = lang::Assigner::UNSPECIFIED;

    if (ctx->expression())
    {
        assigner      = std::any_cast<lang::Assigner>(visit(ctx->assigner()));
        initial_value = std::any_cast<Expression*>(visit(ctx->expression()));
    }
    else { initial_value = nullptr; }

    application_.globalScope().defineGlobalVariable(access,
                                                    is_constant,
                                                    identifier,
                                                    type,
                                                    type_location,
                                                    assigner,
                                                    std::unique_ptr<Expression>(initial_value),
                                                    location(ctx));

    return {};
}

std::any SourceVisitor::visitStructDefinition(anceParser::StructDefinitionContext* ctx)
{
    lang::AccessModifier access     = std::any_cast<lang::AccessModifier>(visit(ctx->accessModifier()));
    lang::Identifier     identifier = ident(ctx->IDENTIFIER());

    std::vector<std::unique_ptr<lang::Member>> members;

    for (auto member : ctx->member())
    {
        members.push_back(std::unique_ptr<lang::Member>(std::any_cast<lang::Member*>(visit(member))));
    }

    application_.globalScope().defineStruct(access, identifier, std::move(members), location(ctx));

    return {};
}

std::any SourceVisitor::visitMember(anceParser::MemberContext* ctx)
{
    lang::AccessModifier              access     = std::any_cast<lang::AccessModifier>(visit(ctx->accessModifier()));
    lang::Identifier                  identifier = ident(ctx->IDENTIFIER());
    lang::ResolvingHandle<lang::Type> type       = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));

    ConstantExpression* const_expr = nullptr;
    lang::Assigner      assigner   = lang::Assigner::UNSPECIFIED;

    if (ctx->literalExpression())
    {
        assigner = std::any_cast<lang::Assigner>(visit(ctx->assigner()));

        Expression* expr = std::any_cast<Expression*>(visit(ctx->literalExpression()));
        const_expr       = dynamic_cast<ConstantExpression*>(expr);
    }

    return new lang::Member(access,
                            identifier,
                            type,
                            assigner,
                            std::unique_ptr<ConstantExpression>(const_expr),
                            location(ctx),
                            location(ctx->type()));
}

std::any SourceVisitor::visitFunctionDefinition(anceParser::FunctionDefinitionContext* ctx)
{
    lang::AccessModifier              access     = std::any_cast<lang::AccessModifier>(visit(ctx->accessModifier()));
    lang::Identifier                  identifier = ident(ctx->IDENTIFIER());
    lang::ResolvingHandle<lang::Type> return_type =
        ctx->type() ? std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type())) : lang::VoidType::get();

    lang::Location declaration_location = location(ctx);
    lang::Location definition_location  = ctx->code().empty() ? declaration_location : location(ctx->code()[0]);

    std::vector<lang::Parameter*> parameters = std::any_cast<std::vector<lang::Parameter*>>(visit(ctx->parameters()));

    std::vector<std::shared_ptr<lang::Parameter>> shared_parameters;
    shared_parameters.reserve(parameters.size());
    for (lang::Parameter* parameter_ptr : parameters) { shared_parameters.emplace_back(parameter_ptr); }

    lang::Location return_type_location = ctx->type() ? location(ctx->type()) : lang::Location::global();

    auto function_block = lang::CodeBlock::makeInitial(location(ctx));

    for (auto code_context : ctx->code())
    {
        lang::CodeBlock* block     = std::any_cast<lang::CodeBlock*>(visit(code_context));
        auto             block_ptr = std::unique_ptr<lang::CodeBlock>(block);

        function_block->append(std::move(block_ptr));
    }

    application_.globalScope().defineCustomFunction(identifier,
                                                    access,
                                                    return_type,
                                                    return_type_location,
                                                    shared_parameters,
                                                    std::move(function_block),
                                                    declaration_location,
                                                    definition_location);

    return {};
}

std::any SourceVisitor::visitExternFunctionDeclaration(anceParser::ExternFunctionDeclarationContext* ctx)
{
    lang::Identifier                  identifier = ident(ctx->IDENTIFIER());
    lang::ResolvingHandle<lang::Type> return_type =
        ctx->type() ? std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type())) : lang::VoidType::get();
    std::vector<lang::Parameter*> parameters = std::any_cast<std::vector<lang::Parameter*>>(visit(ctx->parameters()));

    std::vector<std::shared_ptr<lang::Parameter>> shared_parameters;
    shared_parameters.reserve(parameters.size());
    for (lang::Parameter* parameter_ptr : parameters) { shared_parameters.emplace_back(parameter_ptr); }

    lang::Location return_type_location = ctx->type() ? location(ctx->type()) : lang::Location::global();

    application_.globalScope().defineExternFunction(identifier,
                                                    return_type,
                                                    return_type_location,
                                                    shared_parameters,
                                                    location(ctx));

    return {};
}

std::any SourceVisitor::visitParameters(anceParser::ParametersContext* ctx)
{
    std::vector<lang::Parameter*> params;

    for (auto* param : ctx->parameter()) { params.push_back(std::any_cast<lang::Parameter*>(visit(param))); }

    return params;
}

std::any SourceVisitor::visitParameter(anceParser::ParameterContext* ctx)
{
    lang::ResolvingHandle<lang::Type> type       = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::Identifier                  identifier = ident(ctx->IDENTIFIER());

    return new lang::Parameter(type, location(ctx->type()), identifier, location(ctx));
}

std::any SourceVisitor::visitDefineAlias(anceParser::DefineAliasContext* ctx)
{
    lang::ResolvingHandle<lang::Type> other      = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::Identifier                  identifier = ident(ctx->IDENTIFIER());

    application_.globalScope().defineTypeAliasOther(identifier, other, location(ctx), location(ctx->type()));

    return {};
}

std::any SourceVisitor::visitBlock(anceParser::BlockContext* ctx)
{
    lang::CodeBlock* block = lang::CodeBlock::makeScoped(location(ctx));

    for (auto code_context : ctx->code())
    {
        lang::CodeBlock* code     = std::any_cast<lang::CodeBlock*>(visit(code_context));
        auto             code_ptr = std::unique_ptr<lang::CodeBlock>(code);

        block->append(std::move(code_ptr));
    }

    return block;
}

std::any SourceVisitor::visitExpressionStatement(anceParser::ExpressionStatementContext* ctx)
{
    Expression*                          expression = std::any_cast<Expression*>(visit(ctx->independentExpression()));
    std::unique_ptr<BuildableExpression> buildable_expression(dynamic_cast<BuildableExpression*>(expression));

    auto statement = std::make_unique<ExpressionStatement>(std::move(buildable_expression), location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

std::any SourceVisitor::visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx)
{
    lang::Identifier identifier = ident(ctx->IDENTIFIER());

    std::optional<lang::ResolvingHandle<lang::Type>> type;
    if (ctx->type()) type = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));

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

    auto statement = std::make_unique<LocalVariableDefinition>(identifier,
                                                  type,
                                                  ctx->type() ? location(ctx->type()) : lang::Location::global(),
                                                  assigner,
                                                  std::unique_ptr<Expression>(assigned),
                                                  location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

std::any SourceVisitor::visitLocalReferenceDefinition(anceParser::LocalReferenceDefinitionContext* ctx)
{
    lang::ResolvingHandle<lang::Type> type       = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::Identifier                  identifier = ident(ctx->IDENTIFIER());

    Expression* ref = std::any_cast<Expression*>(visit(ctx->bindRef()));

    auto statement = std::make_unique<LocalReferenceVariableDefinition>(identifier,
                                                                        type,
                                                                        location(ctx->type()),
                                                                        std::unique_ptr<Expression>(ref),
                                                                        location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

std::any SourceVisitor::visitDropStatement(anceParser::DropStatementContext* ctx)
{
    lang::Identifier identifier = ident(ctx->IDENTIFIER());
    auto             variable   = lang::makeHandled<lang::Variable>(identifier);

    auto statement = std::make_unique<Drop>(variable, location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

std::any SourceVisitor::visitAssignment(anceParser::AssignmentContext* ctx)
{
    Expression*    assignable = std::any_cast<Expression*>(visit(ctx->assignable));
    lang::Assigner assigner   = std::any_cast<lang::Assigner>(visit(ctx->assigner()));
    Expression*    assigned   = std::any_cast<Expression*>(visit(ctx->assigned));

    auto statement = std::make_unique<Assignment>(std::unique_ptr<Expression>(assignable),
                                                  assigner,
                                                  std::unique_ptr<Expression>(assigned),
                                                  location(ctx));

    return lang::CodeBlock::wrapStatement(std::move(statement));
}

std::any SourceVisitor::visitDeleteStatement(anceParser::DeleteStatementContext* ctx)
{
    Expression* expression    = std::any_cast<Expression*>(visit(ctx->expression()));
    bool        delete_buffer = ctx->BUFFER();

    auto statement = std::make_unique<Delete>(std::unique_ptr<Expression>(expression), delete_buffer, location(ctx));

    return lang::CodeBlock::wrapStatement(std::move(statement));
}

std::any SourceVisitor::visitReturnStatement(anceParser::ReturnStatementContext* ctx)
{
    Expression* return_value = nullptr;

    if (ctx->expression() != nullptr) { return_value = std::any_cast<Expression*>(visit(ctx->expression())); }

    auto statement = std::make_unique<Return>(std::unique_ptr<Expression>(return_value), location(ctx));

    return lang::CodeBlock::wrapStatement(std::move(statement));
}

std::any SourceVisitor::visitAssertStatement(anceParser::AssertStatementContext* ctx)
{
    Expression* condition = std::any_cast<Expression*>(visit(ctx->expression()));

    auto statement = std::make_unique<Assertion>(std::unique_ptr<Expression>(condition), location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

std::any SourceVisitor::visitIfStatement(anceParser::IfStatementContext* ctx)
{
    Expression* condition = std::any_cast<Expression*>(visit(ctx->expression()));
    bool        has_else  = ctx->elseBlock != nullptr;

    auto if_block = std::unique_ptr<lang::CodeBlock>(std::any_cast<lang::CodeBlock*>(visit(ctx->ifBlock)));
    auto else_block =
        has_else ? std::unique_ptr<lang::CodeBlock>(std::any_cast<lang::CodeBlock*>(visit(ctx->elseBlock))) : nullptr;

    return lang::CodeBlock::wrapStatement(std::make_unique<If>(std::unique_ptr<Expression>(condition),
                                                               std::move(if_block),
                                                               std::move(else_block),
                                                               location(ctx)));
}

std::any SourceVisitor::visitWhileStatement(anceParser::WhileStatementContext* ctx)
{
    Expression* condition = std::any_cast<Expression*>(visit(ctx->expression()));

    auto block = (std::unique_ptr<lang::CodeBlock>(std::any_cast<lang::CodeBlock*>(visit(ctx->code()))));

    return lang::CodeBlock::wrapStatement(
        std::make_unique<While>(std::unique_ptr<Expression>(condition), std::move(block), location(ctx)));
}

std::any SourceVisitor::visitMatchStatement(anceParser::MatchStatementContext* ctx)
{
    Expression* expression = std::any_cast<Expression*>(visit(ctx->expression()));

    std::vector<std::unique_ptr<Case>> cases;
    for (auto& case_ctx : ctx->matchCase())
    {
        Case* case_instance = std::any_cast<Case*>(visit(case_ctx));
        cases.push_back(std::unique_ptr<Case>(case_instance));
    }

    return lang::CodeBlock::wrapStatement(
        std::make_unique<Match>(std::move(cases), std::unique_ptr<Expression>(expression), location(ctx)));
}

std::any SourceVisitor::visitLiteralCase(anceParser::LiteralCaseContext* ctx)
{
    auto block = std::unique_ptr<lang::CodeBlock>(std::any_cast<lang::CodeBlock*>(visit(ctx->code())));

    std::vector<std::unique_ptr<ConstantExpression>> cases;
    for (auto& condition_ctx : ctx->literalExpression())
    {
        auto condition = dynamic_cast<ConstantExpression*>(std::any_cast<Expression*>(visit(condition_ctx)));
        cases.push_back(std::unique_ptr<ConstantExpression>(condition));
    }

    return Case::createCase(std::move(cases), std::move(block));
}

std::any SourceVisitor::visitDefaultCase(anceParser::DefaultCaseContext* ctx)
{
    auto block = std::unique_ptr<lang::CodeBlock>(std::any_cast<lang::CodeBlock*>(visit(ctx->code())));

    return Case::createDefault(std::move(block));
}

std::any SourceVisitor::visitMemberAccess(anceParser::MemberAccessContext* ctx)
{
    Expression*      accessed = std::any_cast<Expression*>(visit(ctx->accessed));
    lang::Identifier member   = ident(ctx->IDENTIFIER());

    return static_cast<Expression*>(new MemberAccess(std::unique_ptr<Expression>(accessed), member, location(ctx)));
}

std::any SourceVisitor::visitFunctionCall(anceParser::FunctionCallContext* ctx)
{
    std::optional<lang::ResolvingHandle<lang::FunctionGroup>> function_group;
    std::optional<lang::ResolvingHandle<lang::Type>>          constructed_type;

    if (ctx->type()) { constructed_type = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type())); }
    else
    {
        lang::Identifier identifier = ident(ctx->IDENTIFIER());

        function_group   = lang::makeHandled<lang::FunctionGroup>(identifier);
        constructed_type = lang::makeHandled<lang::Type>(identifier);
    }

    std::vector<Expression*> arguments = std::any_cast<std::vector<Expression*>>(visit(ctx->arguments()));

    std::vector<std::unique_ptr<Expression>> unique_expressions;
    unique_expressions.reserve(arguments.size());
    for (Expression* argument_ptr : arguments) { unique_expressions.emplace_back(argument_ptr); }

    return static_cast<Expression*>(
        new FunctionCall(function_group, constructed_type.value(), std::move(unique_expressions), location(ctx)));
}

std::any SourceVisitor::visitArguments(anceParser::ArgumentsContext* ctx)
{
    std::vector<Expression*> arguments;

    for (auto* argument : ctx->expression()) { arguments.push_back(std::any_cast<Expression*>(visit(argument))); }

    return arguments;
}

std::any SourceVisitor::visitVariableAccess(anceParser::VariableAccessContext* ctx)
{
    lang::Identifier identifier = ident(ctx->IDENTIFIER());
    auto             variable   = lang::makeHandled<lang::Variable>(identifier);

    return static_cast<Expression*>(new VariableAccess(variable, location(ctx)));
}

std::any SourceVisitor::visitAllocation(anceParser::AllocationContext* ctx)
{
    Runtime::Allocator                allocator = std::any_cast<Runtime::Allocator>(visit(ctx->allocator()));
    lang::ResolvingHandle<lang::Type> type      = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    Expression*                       count     = nullptr;

    if (ctx->expression()) { count = std::any_cast<Expression*>(visit(ctx->expression())); }

    return static_cast<Expression*>(
        new Allocation(allocator, type, std::unique_ptr<Expression>(count), location(ctx), location(ctx->type())));
}

std::any SourceVisitor::visitAddressof(anceParser::AddressofContext* ctx)
{
    Expression* arg = std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new Addressof(std::unique_ptr<Expression>(arg), location(ctx)));
}

std::any SourceVisitor::visitBindReference(anceParser::BindReferenceContext* ctx)
{
    Expression* value = std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new BindRef(std::unique_ptr<Expression>(value), location(ctx)));
}

std::any SourceVisitor::visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx)
{
    Expression* address = std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new BindRefTo(std::unique_ptr<Expression>(address), location(ctx)));
}

std::any SourceVisitor::visitSizeofType(anceParser::SizeofTypeContext* ctx)
{
    lang::ResolvingHandle<lang::Type> type = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));

    return static_cast<Expression*>(new SizeofType(type, location(ctx->type()), location(ctx)));
}

std::any SourceVisitor::visitSizeofExpression(anceParser::SizeofExpressionContext* ctx)
{
    Expression* expr = std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new SizeofExpression(std::unique_ptr<Expression>(expr), location(ctx)));
}

std::any SourceVisitor::visitSubscript(anceParser::SubscriptContext* ctx)
{
    Expression* indexed = std::any_cast<Expression*>(visit(ctx->indexed));
    Expression* index   = std::any_cast<Expression*>(visit(ctx->index));

    return static_cast<Expression*>(
        new Subscript(std::unique_ptr<Expression>(indexed), std::unique_ptr<Expression>(index), location(ctx)));
}

std::any SourceVisitor::visitBinaryOperation(anceParser::BinaryOperationContext* ctx)
{
    Expression* left  = std::any_cast<Expression*>(visit(ctx->left));
    Expression* right = std::any_cast<Expression*>(visit(ctx->right));

    std::optional<lang::BinaryOperator> op;
    if (ctx->binaryOperatorMultiplicative())
        op = std::any_cast<lang::BinaryOperator>(visit(ctx->binaryOperatorMultiplicative()));
    if (ctx->binaryOperatorAdditive()) op = std::any_cast<lang::BinaryOperator>(visit(ctx->binaryOperatorAdditive()));
    if (ctx->binaryOperatorRelational())
        op = std::any_cast<lang::BinaryOperator>(visit(ctx->binaryOperatorRelational()));
    if (ctx->binaryOperatorEquality()) op = std::any_cast<lang::BinaryOperator>(visit(ctx->binaryOperatorEquality()));
    assert(op.has_value());

    return static_cast<Expression*>(new BinaryOperation(std::unique_ptr<Expression>(left),
                                                        op.value(),
                                                        std::unique_ptr<Expression>(right),
                                                        location(ctx)));
}

std::any SourceVisitor::visitParenthesis(anceParser::ParenthesisContext* ctx)
{
    Expression* contained = std::any_cast<Expression*>(visit(ctx->expression()));
    return static_cast<Expression*>(new Parenthesis(std::unique_ptr<Expression>(contained), location(ctx)));
}

std::any SourceVisitor::visitNotOperation(anceParser::NotOperationContext* ctx)
{
    Expression* value = std::any_cast<Expression*>(visit(ctx->expression()));
    return static_cast<Expression*>(
        new UnaryOperation(lang::UnaryOperator::NOT, std::unique_ptr<Expression>(value), location(ctx)));
}

std::any SourceVisitor::visitLogicalAnd(anceParser::LogicalAndContext* ctx)
{
    bool        negated = ctx->NOT();
    Expression* left    = std::any_cast<Expression*>(visit(ctx->left));
    Expression* right = std::any_cast<Expression*>(visit(ctx->right));

    return static_cast<Expression*>(
        new And(negated, std::unique_ptr<Expression>(left), std::unique_ptr<Expression>(right), location(ctx)));
}

std::any SourceVisitor::visitLogicalOr(anceParser::LogicalOrContext* ctx)
{
    bool        negated = ctx->NOT();
    Expression* left    = std::any_cast<Expression*>(visit(ctx->left));
    Expression* right = std::any_cast<Expression*>(visit(ctx->right));

    return static_cast<Expression*>(
        new Or(negated, std::unique_ptr<Expression>(left), std::unique_ptr<Expression>(right), location(ctx)));
}

std::any SourceVisitor::visitIfExpression(anceParser::IfExpressionContext* ctx)
{
    Expression* condition = std::any_cast<Expression*>(visit(ctx->condition));

    Expression* then_expression = std::any_cast<Expression*>(visit(ctx->thenBlock));
    Expression* else_expression = std::any_cast<Expression*>(visit(ctx->elseBlock));

    return static_cast<Expression*>(new IfSelect(std::unique_ptr<Expression>(condition),
                                                 std::unique_ptr<Expression>(then_expression),
                                                 std::unique_ptr<Expression>(else_expression),
                                                 location(ctx)));
}

std::any SourceVisitor::visitMatchExpression(anceParser::MatchExpressionContext* ctx)
{
    Expression* expression = std::any_cast<Expression*>(visit(ctx->expression()));

    std::vector<std::unique_ptr<Case>> cases;
    for (auto& case_ctx : ctx->matchExpressionCase())
    {
        Case* case_instance = std::any_cast<Case*>(visit(case_ctx));
        cases.push_back(std::unique_ptr<Case>(case_instance));
    }

    return static_cast<Expression*>(
        new MatchSelect(std::unique_ptr<Expression>(expression), std::move(cases), location(ctx)));
}

std::any SourceVisitor::visitIndirection(anceParser::IndirectionContext* ctx)
{
    Expression* value = std::any_cast<Expression*>(visit(ctx->expression()));
    return static_cast<Expression*>(new Indirection(std::unique_ptr<Expression>(value), location(ctx)));
}

std::any SourceVisitor::visitVectorDefinition(anceParser::VectorDefinitionContext* ctx)
{
    std::optional<lang::ResolvingHandle<lang::Type>> type;
    lang::Location                                   type_location = lang::Location::global();

    if (ctx->type())
    {
        type          = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
        type_location = location(ctx->type());
    }

    std::vector<std::unique_ptr<Expression>> elements;

    for (auto& element_ctx : ctx->expression())
    {
        elements.push_back(std::unique_ptr<Expression>(std::any_cast<Expression*>(visit(element_ctx))));
    }

    return static_cast<Expression*>(new VectorDefinition(type, type_location, std::move(elements), location(ctx)));
}

std::any SourceVisitor::visitArrayDefinition(anceParser::ArrayDefinitionContext* ctx)
{
    std::optional<lang::ResolvingHandle<lang::Type>> type;
    lang::Location                                   type_location = lang::Location::global();

    if (ctx->type())
    {
        type          = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
        type_location = location(ctx->type());
    }

    std::vector<std::unique_ptr<Expression>> elements;

    for (auto& element_ctx : ctx->expression())
    {
        elements.push_back(std::unique_ptr<Expression>(std::any_cast<Expression*>(visit(element_ctx))));
    }

    return static_cast<Expression*>(new ArrayDefinition(type, type_location, std::move(elements), location(ctx)));
}

std::any SourceVisitor::visitDefaultExpressionCase(anceParser::DefaultExpressionCaseContext* ctx)
{
    auto expression = std::unique_ptr<Expression>(std::any_cast<Expression*>(visit(ctx->expression())));

    return Case::createDefault(std::move(expression));
}

std::any SourceVisitor::visitLiteralExpressionCase(anceParser::LiteralExpressionCaseContext* ctx)
{
    auto block = std::unique_ptr<Expression>(std::any_cast<Expression*>(visit(ctx->expression())));

    std::vector<std::unique_ptr<ConstantExpression>> cases;
    for (auto& condition_ctx : ctx->literalExpression())
    {
        auto condition = dynamic_cast<ConstantExpression*>(std::any_cast<Expression*>(visit(condition_ctx)));
        cases.push_back(std::unique_ptr<ConstantExpression>(condition));
    }

    return Case::createCase(std::move(cases), std::move(block));
}

std::any SourceVisitor::visitStringLiteral(anceParser::StringLiteralContext* ctx)
{
    std::string prefix;

    if (ctx->prefix) { prefix = ctx->prefix->getText(); }

    std::shared_ptr<lang::Constant> string = std::make_shared<lang::StringConstant>(prefix, ctx->STRING()->getText());
    return static_cast<Expression*>(new ConstantLiteral(string, location(ctx)));
}

std::any SourceVisitor::visitCharLiteral(anceParser::CharLiteralContext* ctx)
{
    std::string prefix;

    if (ctx->prefix) { prefix = ctx->prefix->getText(); }

    std::shared_ptr<lang::Constant> byte = std::make_shared<lang::CharConstant>(prefix, ctx->CHAR()->getText());
    return static_cast<Expression*>(new ConstantLiteral(byte, location(ctx)));
}

std::any SourceVisitor::visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx)
{
    std::shared_ptr<lang::Constant> flt;

    if (ctx->HALF())
    {
        flt = std::make_shared<lang::FloatConstant>(ctx->getText().erase(ctx->getText().size() - 1),
                                                    llvm::APFloat::IEEEhalf(),
                                                    lang::HalfType::get());
    }

    if (ctx->SINGLE())
    {
        flt = std::make_shared<lang::FloatConstant>(ctx->getText().erase(ctx->getText().size() - 1),
                                                    llvm::APFloat::IEEEsingle(),
                                                    lang::SingleType::get());
    }

    if (ctx->DOUBLE())
    {
        flt = std::make_shared<lang::FloatConstant>(ctx->getText().erase(ctx->getText().size() - 1),
                                                    llvm::APFloat::IEEEdouble(),
                                                    lang::DoubleType::get());
    }

    if (ctx->QUAD())
    {
        flt = std::make_shared<lang::FloatConstant>(ctx->getText().erase(ctx->getText().size() - 1),
                                                    llvm::APFloat::IEEEquad(),
                                                    lang::QuadType::get());
    }

    return static_cast<Expression*>(new ConstantLiteral(flt, location(ctx)));
}

std::any SourceVisitor::visitTrue(anceParser::TrueContext* ctx)
{
    std::shared_ptr<lang::Constant> constant = lang::BooleanConstant::createTrue();
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitFalse(anceParser::FalseContext* ctx)
{
    std::shared_ptr<lang::Constant> constant = lang::BooleanConstant::createFalse();
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitNull(anceParser::NullContext* ctx)
{
    std::shared_ptr<lang::Constant> constant = lang::NullConstant::create();
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitSizeLiteral(anceParser::SizeLiteralContext* ctx)
{
    std::string                     value = ctx->INTEGER()->getText();
    std::shared_ptr<lang::Constant> constant =
        std::make_shared<lang::IntegerConstant>(value, 10, lang::SizeType::getSize());

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitDiffLiteral(anceParser::DiffLiteralContext* ctx)
{
    std::string                     value = ctx->SIGNED_INTEGER()->getText();
    std::shared_ptr<lang::Constant> constant =
        std::make_shared<lang::IntegerConstant>(value, 10, lang::SizeType::getDiff());

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitUiptrLiteral(anceParser::UiptrLiteralContext* ctx)
{
    std::string value = ctx->HEX_INTEGER()->getText();
    value.erase(0, 2);

    std::shared_ptr<lang::Constant> constant =
        std::make_shared<lang::IntegerConstant>(value, 16, lang::UnsignedIntegerPointerType::get());

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

std::any SourceVisitor::visitNormalInteger(anceParser::NormalIntegerContext* ctx)
{
    bool        is_signed    = ctx->svalue;
    std::string literal_text = is_signed ? ctx->svalue->getText() : ctx->uvalue->getText();

    std::shared_ptr<lang::Constant> integer_constant;

    if (ctx->width)
    {
        uint64_t size    = parseIntegerTypeSize(ctx->width->getText());
        integer_constant = std::make_shared<lang::IntegerConstant>(literal_text,
                                                                   10,
                                                                   lang::FixedWidthIntegerType::get(size, is_signed));
    }
    else {
        integer_constant = std::make_shared<lang::IntegerConstant>(literal_text, is_signed);
    }

    return static_cast<Expression*>(new ConstantLiteral(integer_constant, location(ctx)));
}

std::any SourceVisitor::visitSpecialInteger(anceParser::SpecialIntegerContext* ctx)
{
    uint64_t size = parseIntegerTypeSize(ctx->width->getText());

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

    std::shared_ptr<lang::Constant> integer_constant =
        std::make_shared<lang::IntegerConstant>(integer_str, radix, lang::FixedWidthIntegerType::get(size, false));
    return static_cast<Expression*>(new ConstantLiteral(integer_constant, location(ctx)));
}

std::any SourceVisitor::visitIntegerType(anceParser::IntegerTypeContext* ctx)
{
    std::string integer_type_str = ctx->NATIVE_INTEGER_TYPE()->getText();

    bool     is_unsigned = integer_type_str[0] == 'u';
    uint64_t size        = parseIntegerTypeSize(integer_type_str.substr(1 + integer_type_str.find('i')));

    lang::ResolvingHandle<lang::Type> type = lang::FixedWidthIntegerType::get(size, !is_unsigned);
    return type;
}

std::any SourceVisitor::visitBooleanType(anceParser::BooleanTypeContext*)
{
    return lang::BooleanType::get();
}

std::any SourceVisitor::visitArrayType(anceParser::ArrayTypeContext* ctx)
{
    lang::ResolvingHandle<lang::Type> element_type =
        std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    uint64_t                          size = parseCompoundTypeSize(ctx->INTEGER()->getText());
    lang::ResolvingHandle<lang::Type> type = lang::ArrayType::get(element_type, size);

    return type;
}

std::any SourceVisitor::visitVectorType(anceParser::VectorTypeContext* ctx)
{
    lang::ResolvingHandle<lang::Type> element_type =
        std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    uint64_t                          size = parseCompoundTypeSize(ctx->INTEGER()->getText());
    lang::ResolvingHandle<lang::Type> type = lang::VectorType::get(element_type, size);

    return type;
}

std::any SourceVisitor::visitKeywordType(anceParser::KeywordTypeContext* ctx)
{
    return application_.globalScope().getType(createIdentifier(ctx->getText(), location(ctx))).value();
}

std::any SourceVisitor::visitPointer(anceParser::PointerContext* ctx)
{
    lang::ResolvingHandle<lang::Type> element_type =
        std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::ResolvingHandle<lang::Type> type = lang::PointerType::get(element_type);

    return type;
}

std::any SourceVisitor::visitBuffer(anceParser::BufferContext* ctx)
{
    lang::ResolvingHandle<lang::Type> element_type =
        std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::ResolvingHandle<lang::Type> type = lang::BufferType::get(element_type);

    return type;
}

std::any SourceVisitor::visitReference(anceParser::ReferenceContext* ctx)
{
    lang::ResolvingHandle<lang::Type> element_type =
        std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::ResolvingHandle<lang::Type> type = lang::ReferenceType::get(element_type);

    return type;
}

std::any SourceVisitor::visitCustom(anceParser::CustomContext* ctx)
{
    return lang::makeHandled<lang::Type>(createIdentifier(ctx->getText(), location(ctx)));
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

std::any SourceVisitor::visitAutomatic(anceParser::AutomaticContext*)
{
    Runtime::Allocator allocator = Runtime::Allocator::AUTOMATIC;
    return allocator;
}

std::any SourceVisitor::visitDynamic(anceParser::DynamicContext*)
{
    Runtime::Allocator allocator = Runtime::Allocator::DYNAMIC;
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
    // todo: move assignment

    lang::Assigner assigner = lang::Assigner::MOVE_ASSIGNMENT;
    return assigner;
}

std::any SourceVisitor::visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext*)
{
    lang::Assigner assigner = lang::Assigner::FINAL_COPY_ASSIGNMENT;
    return assigner;
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

lang::Location SourceVisitor::location(antlr4::ParserRuleContext* ctx)
{
    size_t start_line   = ctx->getStart()->getLine();
    size_t start_column = ctx->getStart()->getCharPositionInLine() + 1;

    size_t end_line   = ctx->getStop()->getLine();
    size_t end_column = ctx->getStop()->getCharPositionInLine() + ctx->getStop()->getText().size();

    return {start_line, start_column, end_line, end_column};
}

lang::Identifier SourceVisitor::ident(antlr4::tree::TerminalNode* i)
{
    std::string text = i->getText();

    auto   token        = i->getSymbol();
    size_t start_line   = token->getLine();
    size_t start_column = token->getCharPositionInLine() + 1;

    size_t end_line   = start_line;
    size_t end_column = start_column + text.size() - 1;

    return createIdentifier(text, {start_line, start_column, end_line, end_column});
}

lang::Identifier SourceVisitor::createIdentifier(const std::string& text, lang::Location location)
{
    return lang::Identifier::from(text, location);
}

uint64_t SourceVisitor::parseIntegerTypeSize(const std::string& str)
{
    return parseInRange(str, lang::FixedWidthIntegerType::MAX_INTEGER_SIZE);
}

uint64_t SourceVisitor::parseCompoundTypeSize(const std::string& str)
{
    return parseInRange(str, lang::ArrayType::MAX_ARRAY_TYPE_SIZE);
}

uint64_t SourceVisitor::parseInRange(const std::string& str, uint64_t max)
{
    uint64_t value;

    try
    {
        value = std::stoull(str);
    }
    catch (const std::exception&)
    {
        value = max + 1;
    }

    if (value > max) { value = max + 1; }

    return value;
}
