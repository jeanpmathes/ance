#include "SourceVisitor.h"

#include <stdexcept>

#include "compiler/Application.h"

#include "lang/type/ArrayType.h"
#include "lang/type/DoubleType.h"
#include "lang/type/HalfType.h"
#include "lang/type/IntegerType.h"
#include "lang/type/PointerType.h"
#include "lang/type/QuadType.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SingleType.h"
#include "lang/type/BooleanType.h"
#include "lang/type/VoidType.h"

#include "lang/statement/Assignment.h"
#include "lang/statement/Delete.h"
#include "lang/statement/ExpressionStatement.h"
#include "lang/statement/LocalReferenceVariableDefinition.h"
#include "lang/statement/LocalVariableDefinition.h"
#include "lang/statement/Drop.h"
#include "lang/statement/Return.h"
#include "lang/statement/Assertion.h"
#include "lang/statement/If.h"
#include "lang/statement/While.h"
#include "lang/statement/Match.h"

#include "lang/expression/MemberAccess.h"
#include "lang/expression/Addressof.h"
#include "lang/expression/Allocation.h"
#include "lang/expression/BinaryOperation.h"
#include "lang/expression/UnaryOperation.h"
#include "lang/expression/BindRef.h"
#include "lang/expression/BindRefTo.h"
#include "lang/expression/ConstantLiteral.h"
#include "lang/expression/FunctionCall.h"
#include "lang/expression/SizeofExpression.h"
#include "lang/expression/SizeofType.h"
#include "lang/expression/Subscript.h"
#include "lang/expression/VariableAccess.h"
#include "lang/expression/Parenthesis.h"
#include "lang/expression/And.h"
#include "lang/expression/Or.h"
#include "lang/expression/IfSelect.h"
#include "lang/expression/MatchSelect.h"
#include "lang/expression/Indirection.h"

#include "lang/construct/constant/BooleanConstant.h"
#include "lang/construct/constant/ByteConstant.h"
#include "lang/construct/constant/DiffConstant.h"
#include "lang/construct/constant/FloatConstant.h"
#include "lang/construct/constant/IntegerConstant.h"
#include "lang/construct/constant/SizeConstant.h"
#include "lang/construct/constant/StringConstant.h"

#include "lang/construct/CodeBlock.h"
#include "lang/construct/Member.h"

#include "lang/AccessModifier.h"
#include "lang/Assigner.h"

SourceVisitor::SourceVisitor(Application& application) : application_(application) {}

antlrcpp::Any SourceVisitor::visitVariableDeclaration(anceParser::VariableDeclarationContext* ctx)
{
    lang::AccessModifier              access      = std::any_cast<lang::AccessModifier>(visit(ctx->accessModifier()));
    bool                              is_constant = ctx->CONST();
    lang::ResolvingHandle<lang::Type> type       = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::Identifier                  identifier = ident(ctx->IDENTIFIER());

    ConstantExpression* const_expr;
    lang::Assigner      assigner = lang::Assigner::UNSPECIFIED;

    if (ctx->literalExpression())
    {
        assigner = std::any_cast<lang::Assigner>(visit(ctx->assigner()));

        Expression* expr = std::any_cast<Expression*>(visit(ctx->literalExpression()));
        const_expr       = dynamic_cast<ConstantExpression*>(expr);
    }
    else
    { const_expr = nullptr; }

    application_.globalScope().defineGlobalVariable(access,
                                                    is_constant,
                                                    identifier,
                                                    type,
                                                    location(ctx->type()),
                                                    assigner,
                                                    std::unique_ptr<ConstantExpression>(const_expr),
                                                    location(ctx));

    return {};
}

antlrcpp::Any SourceVisitor::visitStructDefinition(anceParser::StructDefinitionContext* ctx)
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

antlrcpp::Any SourceVisitor::visitMember(anceParser::MemberContext* ctx)
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

antlrcpp::Any SourceVisitor::visitFunctionDefinition(anceParser::FunctionDefinitionContext* ctx)
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

antlrcpp::Any SourceVisitor::visitExternFunctionDeclaration(anceParser::ExternFunctionDeclarationContext* ctx)
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

antlrcpp::Any SourceVisitor::visitParameters(anceParser::ParametersContext* ctx)
{
    std::vector<lang::Parameter*> params;

    for (auto* param : ctx->parameter()) { params.push_back(std::any_cast<lang::Parameter*>(visit(param))); }

    return params;
}

antlrcpp::Any SourceVisitor::visitParameter(anceParser::ParameterContext* ctx)
{
    lang::ResolvingHandle<lang::Type> type       = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::Identifier                  identifier = ident(ctx->IDENTIFIER());

    return new lang::Parameter(type, location(ctx->type()), identifier, location(ctx));
}

antlrcpp::Any SourceVisitor::visitDefineAlias(anceParser::DefineAliasContext* ctx)
{
    lang::ResolvingHandle<lang::Type> other      = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::Identifier                  identifier = ident(ctx->IDENTIFIER());

    application_.globalScope().defineTypeAliasOther(identifier, other, location(ctx), location(ctx->type()));

    return {};
}

antlrcpp::Any SourceVisitor::visitBlock(anceParser::BlockContext* ctx)
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

antlrcpp::Any SourceVisitor::visitExpressionStatement(anceParser::ExpressionStatementContext* ctx)
{
    Expression*                          expression = std::any_cast<Expression*>(visit(ctx->independentExpression()));
    std::unique_ptr<BuildableExpression> buildable_expression(dynamic_cast<BuildableExpression*>(expression));

    auto statement = std::make_unique<ExpressionStatement>(std::move(buildable_expression), location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx)
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

antlrcpp::Any SourceVisitor::visitLocalReferenceDefinition(anceParser::LocalReferenceDefinitionContext* ctx)
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

antlrcpp::Any SourceVisitor::visitDropStatement(anceParser::DropStatementContext* ctx)
{
    lang::Identifier identifier = ident(ctx->IDENTIFIER());
    auto             variable   = lang::makeHandled<lang::Variable>(identifier);

    auto statement = std::make_unique<Drop>(variable, location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitAssignment(anceParser::AssignmentContext* ctx)
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

antlrcpp::Any SourceVisitor::visitDeleteStatement(anceParser::DeleteStatementContext* ctx)
{
    Expression* expression    = std::any_cast<Expression*>(visit(ctx->expression()));
    bool        delete_buffer = ctx->BUFFER();

    auto statement = std::make_unique<Delete>(std::unique_ptr<Expression>(expression), delete_buffer, location(ctx));

    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitReturnStatement(anceParser::ReturnStatementContext* ctx)
{
    Expression* return_value = nullptr;

    if (ctx->expression() != nullptr) { return_value = std::any_cast<Expression*>(visit(ctx->expression())); }

    auto statement = std::make_unique<Return>(std::unique_ptr<Expression>(return_value), location(ctx));

    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitAssertStatement(anceParser::AssertStatementContext* ctx)
{
    Expression* condition = std::any_cast<Expression*>(visit(ctx->expression()));

    auto statement = std::make_unique<Assertion>(std::unique_ptr<Expression>(condition), location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitIfStatement(anceParser::IfStatementContext* ctx)
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

antlrcpp::Any SourceVisitor::visitWhileStatement(anceParser::WhileStatementContext* ctx)
{
    Expression* condition = std::any_cast<Expression*>(visit(ctx->expression()));

    auto block = (std::unique_ptr<lang::CodeBlock>(std::any_cast<lang::CodeBlock*>(visit(ctx->code()))));

    return lang::CodeBlock::wrapStatement(
        std::make_unique<While>(std::unique_ptr<Expression>(condition), std::move(block), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitMatchStatement(anceParser::MatchStatementContext* ctx)
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

antlrcpp::Any SourceVisitor::visitLiteralCase(anceParser::LiteralCaseContext* ctx)
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

antlrcpp::Any SourceVisitor::visitDefaultCase(anceParser::DefaultCaseContext* ctx)
{
    auto block = std::unique_ptr<lang::CodeBlock>(std::any_cast<lang::CodeBlock*>(visit(ctx->code())));

    return Case::createDefault(std::move(block));
}

antlrcpp::Any SourceVisitor::visitMemberAccess(anceParser::MemberAccessContext* ctx)
{
    Expression*      accessed = std::any_cast<Expression*>(visit(ctx->accessed));
    lang::Identifier member   = ident(ctx->IDENTIFIER());

    return static_cast<Expression*>(new MemberAccess(std::unique_ptr<Expression>(accessed), member, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitFunctionCall(anceParser::FunctionCallContext* ctx)
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

antlrcpp::Any SourceVisitor::visitArguments(anceParser::ArgumentsContext* ctx)
{
    std::vector<Expression*> arguments;

    for (auto* argument : ctx->expression()) { arguments.push_back(std::any_cast<Expression*>(visit(argument))); }

    return arguments;
}

antlrcpp::Any SourceVisitor::visitVariableAccess(anceParser::VariableAccessContext* ctx)
{
    lang::Identifier identifier = ident(ctx->IDENTIFIER());
    auto             variable   = lang::makeHandled<lang::Variable>(identifier);

    return static_cast<Expression*>(new VariableAccess(variable, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitAllocation(anceParser::AllocationContext* ctx)
{
    Runtime::Allocator                allocator = std::any_cast<Runtime::Allocator>(visit(ctx->allocator()));
    lang::ResolvingHandle<lang::Type> type      = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    Expression*                       count     = nullptr;

    if (ctx->expression()) { count = std::any_cast<Expression*>(visit(ctx->expression())); }

    return static_cast<Expression*>(
        new Allocation(allocator, type, std::unique_ptr<Expression>(count), location(ctx), location(ctx->type())));
}

antlrcpp::Any SourceVisitor::visitAddressof(anceParser::AddressofContext* ctx)
{
    Expression* arg = std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new Addressof(std::unique_ptr<Expression>(arg), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitBindReference(anceParser::BindReferenceContext* ctx)
{
    Expression* value = std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new BindRef(std::unique_ptr<Expression>(value), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx)
{
    Expression* address = std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new BindRefTo(std::unique_ptr<Expression>(address), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSizeofType(anceParser::SizeofTypeContext* ctx)
{
    lang::ResolvingHandle<lang::Type> type = std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));

    return static_cast<Expression*>(new SizeofType(type, location(ctx->type()), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSizeofExpression(anceParser::SizeofExpressionContext* ctx)
{
    Expression* expr = std::any_cast<Expression*>(visit(ctx->expression()));

    return static_cast<Expression*>(new SizeofExpression(std::unique_ptr<Expression>(expr), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSubscript(anceParser::SubscriptContext* ctx)
{
    Expression* indexed = std::any_cast<Expression*>(visit(ctx->indexed));
    Expression* index   = std::any_cast<Expression*>(visit(ctx->index));

    return static_cast<Expression*>(
        new Subscript(std::unique_ptr<Expression>(indexed), std::unique_ptr<Expression>(index), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitBinaryOperation(anceParser::BinaryOperationContext* ctx)
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

antlrcpp::Any SourceVisitor::visitParenthesis(anceParser::ParenthesisContext* ctx)
{
    Expression* contained = std::any_cast<Expression*>(visit(ctx->expression()));
    return static_cast<Expression*>(new Parenthesis(std::unique_ptr<Expression>(contained), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitNotOperation(anceParser::NotOperationContext* ctx)
{
    Expression* value = std::any_cast<Expression*>(visit(ctx->expression()));
    return static_cast<Expression*>(
        new UnaryOperation(lang::UnaryOperator::NOT, std::unique_ptr<Expression>(value), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitLogicalAnd(anceParser::LogicalAndContext* ctx)
{
    Expression* left  = std::any_cast<Expression*>(visit(ctx->left));
    Expression* right = std::any_cast<Expression*>(visit(ctx->right));

    return static_cast<Expression*>(
        new And(std::unique_ptr<Expression>(left), std::unique_ptr<Expression>(right), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitLogicalOr(anceParser::LogicalOrContext* ctx)
{
    Expression* left  = std::any_cast<Expression*>(visit(ctx->left));
    Expression* right = std::any_cast<Expression*>(visit(ctx->right));

    return static_cast<Expression*>(
        new Or(std::unique_ptr<Expression>(left), std::unique_ptr<Expression>(right), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitIfExpression(anceParser::IfExpressionContext* ctx)
{
    Expression* condition = std::any_cast<Expression*>(visit(ctx->condition));

    Expression* then_expression = std::any_cast<Expression*>(visit(ctx->thenBlock));
    Expression* else_expression = std::any_cast<Expression*>(visit(ctx->elseBlock));

    return static_cast<Expression*>(new IfSelect(std::unique_ptr<Expression>(condition),
                                                 std::unique_ptr<Expression>(then_expression),
                                                 std::unique_ptr<Expression>(else_expression),
                                                 location(ctx)));
}

antlrcpp::Any SourceVisitor::visitMatchExpression(anceParser::MatchExpressionContext* ctx)
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

antlrcpp::Any SourceVisitor::visitIndirection(anceParser::IndirectionContext* ctx)
{
    Expression* value = std::any_cast<Expression*>(visit(ctx->expression()));
    return static_cast<Expression*>(new Indirection(std::unique_ptr<Expression>(value), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitDefaultExpressionCase(anceParser::DefaultExpressionCaseContext* ctx)
{
    auto expression = std::unique_ptr<Expression>(std::any_cast<Expression*>(visit(ctx->expression())));

    return Case::createDefault(std::move(expression));
}

antlrcpp::Any SourceVisitor::visitLiteralExpressionCase(anceParser::LiteralExpressionCaseContext* ctx)
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

antlrcpp::Any SourceVisitor::visitStringLiteral(anceParser::StringLiteralContext* ctx)
{
    std::string prefix;

    if (ctx->prefix) { prefix = ctx->prefix->getText(); }

    std::string str = lang::StringConstant::parse(ctx->STRING()->getText());

    std::shared_ptr<lang::Constant> string = std::make_shared<lang::StringConstant>(prefix, str);
    return static_cast<Expression*>(new ConstantLiteral(string, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitByteLiteral(anceParser::ByteLiteralContext* ctx)
{
    uint8_t b = lang::ByteConstant::parse(ctx->BYTE()->getText());

    std::shared_ptr<lang::Constant> byte = std::make_shared<lang::ByteConstant>(b);
    return static_cast<Expression*>(new ConstantLiteral(byte, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx)
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

antlrcpp::Any SourceVisitor::visitTrue(anceParser::TrueContext* ctx)
{
    std::shared_ptr<lang::Constant> constant = lang::BooleanConstant::createTrue();
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitFalse(anceParser::FalseContext* ctx)
{
    std::shared_ptr<lang::Constant> constant = lang::BooleanConstant::createFalse();
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSizeLiteral(anceParser::SizeLiteralContext* ctx)
{
    std::string                     value    = ctx->INTEGER()->getText();
    std::shared_ptr<lang::Constant> constant = std::make_shared<lang::SizeConstant>(value);

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitDiffLiteral(anceParser::DiffLiteralContext* ctx)
{
    std::string                     value    = ctx->SIGNED_INTEGER()->getText();
    std::shared_ptr<lang::Constant> constant = std::make_shared<lang::DiffConstant>(value);

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitNormalInteger(anceParser::NormalIntegerContext* ctx)
{
    bool        is_signed    = ctx->svalue;
    std::string literal_text = is_signed ? ctx->svalue->getText() : ctx->uvalue->getText();

    std::shared_ptr<lang::Constant> integer_constant;

    if (ctx->width)
    {
        uint64_t size    = parseIntegerTypeSize(ctx->width->getText());
        integer_constant = std::make_shared<lang::IntegerConstant>(literal_text, size, is_signed);
    }
    else {
        integer_constant = std::make_shared<lang::IntegerConstant>(literal_text, is_signed);
    }

    return static_cast<Expression*>(new ConstantLiteral(integer_constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSpecialInteger(anceParser::SpecialIntegerContext* ctx)
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
        std::make_shared<lang::IntegerConstant>(integer_str, size, false, radix);
    return static_cast<Expression*>(new ConstantLiteral(integer_constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitIntegerType(anceParser::IntegerTypeContext* ctx)
{
    std::string integer_type_str = ctx->NATIVE_INTEGER_TYPE()->getText();

    bool     is_unsigned = integer_type_str[0] == 'u';
    uint64_t size        = parseIntegerTypeSize(integer_type_str.substr(1 + integer_type_str.find('i')));

    lang::ResolvingHandle<lang::Type> type = lang::IntegerType::get(size, !is_unsigned);
    return type;
}

antlrcpp::Any SourceVisitor::visitBooleanType(anceParser::BooleanTypeContext*)
{
    return lang::BooleanType::get();
}

antlrcpp::Any SourceVisitor::visitArrayType(anceParser::ArrayTypeContext* ctx)
{
    lang::ResolvingHandle<lang::Type> element_type =
        std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    uint64_t                          size = parseArrayTypeSize(ctx->INTEGER()->getText());
    lang::ResolvingHandle<lang::Type> type         = lang::ArrayType::get(element_type, size);

    return type;
}

antlrcpp::Any SourceVisitor::visitKeywordType(anceParser::KeywordTypeContext* ctx)
{
    return application_.globalScope().getType(createIdentifier(ctx->getText(), location(ctx))).value();
}

antlrcpp::Any SourceVisitor::visitPointer(anceParser::PointerContext* ctx)
{
    lang::ResolvingHandle<lang::Type> element_type =
        std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::ResolvingHandle<lang::Type> type = lang::PointerType::get(element_type);

    return type;
}

antlrcpp::Any SourceVisitor::visitReference(anceParser::ReferenceContext* ctx)
{
    lang::ResolvingHandle<lang::Type> element_type =
        std::any_cast<lang::ResolvingHandle<lang::Type>>(visit(ctx->type()));
    lang::ResolvingHandle<lang::Type> type = lang::ReferenceType::get(element_type);

    return type;
}

antlrcpp::Any SourceVisitor::visitCustom(anceParser::CustomContext* ctx)
{
    return lang::makeHandled<lang::Type>(createIdentifier(ctx->getText(), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitPublic(anceParser::PublicContext*)
{
    lang::AccessModifier access_modifier = lang::AccessModifier::PUBLIC_ACCESS;
    return access_modifier;
}

antlrcpp::Any SourceVisitor::visitPrivate(anceParser::PrivateContext*)
{
    lang::AccessModifier access_modifier = lang::AccessModifier::PRIVATE_ACCESS;
    return access_modifier;
}

antlrcpp::Any SourceVisitor::visitAutomatic(anceParser::AutomaticContext*)
{
    Runtime::Allocator allocator = Runtime::Allocator::AUTOMATIC;
    return allocator;
}

antlrcpp::Any SourceVisitor::visitDynamic(anceParser::DynamicContext*)
{
    Runtime::Allocator allocator = Runtime::Allocator::DYNAMIC;
    return allocator;
}

antlrcpp::Any SourceVisitor::visitCopyAssignment(anceParser::CopyAssignmentContext*)
{
    lang::Assigner assigner = lang::Assigner::COPY_ASSIGNMENT;
    return assigner;
}

antlrcpp::Any SourceVisitor::visitMoveAssignment(anceParser::MoveAssignmentContext*)
{
    assert(false && "Move assignment currently not supported.");
    // todo: move assignment

    lang::Assigner assigner = lang::Assigner::MOVE_ASSIGNMENT;
    return assigner;
}

antlrcpp::Any SourceVisitor::visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext*)
{
    lang::Assigner assigner = lang::Assigner::FINAL_COPY_ASSIGNMENT;
    return assigner;
}

antlrcpp::Any SourceVisitor::visitAddition(anceParser::AdditionContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::ADDITION;
    return op;
}

antlrcpp::Any SourceVisitor::visitSubtraction(anceParser::SubtractionContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::SUBTRACTION;
    return op;
}

antlrcpp::Any SourceVisitor::visitMultiplication(anceParser::MultiplicationContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::MULTIPLICATION;
    return op;
}

antlrcpp::Any SourceVisitor::visitDivision(anceParser::DivisionContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::DIVISION;
    return op;
}

antlrcpp::Any SourceVisitor::visitRemainder(anceParser::RemainderContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::REMAINDER;
    return op;
}

antlrcpp::Any SourceVisitor::visitLessThan(anceParser::LessThanContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::LESS_THAN;
    return op;
}

antlrcpp::Any SourceVisitor::visitLessThanOrEqual(anceParser::LessThanOrEqualContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::LESS_THAN_OR_EQUAL;
    return op;
}

antlrcpp::Any SourceVisitor::visitGreaterThan(anceParser::GreaterThanContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::GREATER_THAN;
    return op;
}

antlrcpp::Any SourceVisitor::visitGreaterThanOrEqual(anceParser::GreaterThanOrEqualContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::GREATER_THAN_OR_EQUAL;
    return op;
}

antlrcpp::Any SourceVisitor::visitEqual(anceParser::EqualContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::EQUAL;
    return op;
}

antlrcpp::Any SourceVisitor::visitNotEqual(anceParser::NotEqualContext*)
{
    lang::BinaryOperator op = lang::BinaryOperator::NOT_EQUAL;
    return op;
}

lang::Location SourceVisitor::location(antlr4::ParserRuleContext* ctx)
{
    unsigned start_line   = ctx->getStart()->getLine();
    unsigned start_column = ctx->getStart()->getCharPositionInLine() + 1;

    unsigned end_line   = ctx->getStop()->getLine();
    unsigned end_column = ctx->getStop()->getCharPositionInLine() + ctx->getStop()->getText().size();

    return {start_line, start_column, end_line, end_column};
}

lang::Identifier SourceVisitor::ident(antlr4::tree::TerminalNode* i)
{
    std::string text = i->getText();

    auto     token        = i->getSymbol();
    unsigned start_line   = token->getLine();
    unsigned start_column = token->getCharPositionInLine() + 1;

    unsigned end_line   = start_line;
    unsigned end_column = start_column + text.size() - 1;

    return createIdentifier(text, {start_line, start_column, end_line, end_column});
}

lang::Identifier SourceVisitor::createIdentifier(const std::string& text, lang::Location location)
{
    return lang::Identifier::from(text, location);
}

uint64_t SourceVisitor::parseIntegerTypeSize(const std::string& str)
{
    return parseInRange(str, lang::IntegerType::MAX_INTEGER_SIZE);
}

uint64_t SourceVisitor::parseArrayTypeSize(const std::string& str)
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
    catch (const std::exception& e)
    {
        value = max + 1;
    }

    if (value > max) { value = max + 1; }

    return value;
}

