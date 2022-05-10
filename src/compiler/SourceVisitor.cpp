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

#include "lang/expression/Addressof.h"
#include "lang/expression/Allocation.h"
#include "lang/expression/BackingExpression.h"
#include "lang/expression/BinaryOperation.h"
#include "lang/expression/UnaryOperation.h"
#include "lang/expression/BindRef.h"
#include "lang/expression/ConstantLiteral.h"
#include "lang/expression/DefaultValue.h"
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

#include "lang/construct/constant/BooleanConstant.h"
#include "lang/construct/constant/ByteConstant.h"
#include "lang/construct/constant/DiffConstant.h"
#include "lang/construct/constant/FloatConstant.h"
#include "lang/construct/constant/IntegerConstant.h"
#include "lang/construct/constant/SizeConstant.h"
#include "lang/construct/constant/StringConstant.h"

#include "lang/construct/CodeBlock.h"

#include "lang/AccessModifier.h"
#include "lang/Assigner.h"

SourceVisitor::SourceVisitor(Application& application) : application_(application) {}

antlrcpp::Any SourceVisitor::visitVariableDeclaration(anceParser::VariableDeclarationContext* ctx)
{
    lang::AccessModifier              access      = visit(ctx->accessModifier()).as<lang::AccessModifier>();
    bool                              is_constant = ctx->CONST();
    lang::ResolvingHandle<lang::Type> type        = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    std::string                       identifier  = ctx->IDENTIFIER()->getText();

    ConstantExpression* const_expr;
    lang::Assigner      assigner = lang::Assigner::COPY_ASSIGNMENT;

    if (ctx->literalExpression())
    {
        assigner = visit(ctx->assigner()).as<lang::Assigner>();

        Expression* expr = visit(ctx->literalExpression()).as<Expression*>();
        const_expr       = dynamic_cast<ConstantExpression*>(expr);
    }
    else if (is_constant)
    {
        const_expr = nullptr;
    }
    else
    {
        const_expr = new DefaultValue(type, location(ctx));
    }

    application_.globalScope().defineGlobalVariable(access,
                                                    is_constant,
                                                    identifier,
                                                    type,
                                                    location(ctx->type()),
                                                    assigner,
                                                    std::unique_ptr<ConstantExpression>(const_expr),
                                                    location(ctx));

    return this->visitChildren(ctx);
}

antlrcpp::Any SourceVisitor::visitFunctionDefinition(anceParser::FunctionDefinitionContext* ctx)
{
    lang::AccessModifier              access     = visit(ctx->accessModifier()).as<lang::AccessModifier>();
    std::string                       identifier = ctx->IDENTIFIER()->getText();
    lang::ResolvingHandle<lang::Type> return_type =
        ctx->type() ? visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>() : lang::VoidType::get();

    lang::Location declaration_location = location(ctx);
    lang::Location definition_location  = ctx->code().empty() ? declaration_location : location(ctx->code()[0]);

    std::vector<lang::Parameter*> parameters = visit(ctx->parameters()).as<std::vector<lang::Parameter*>>();

    std::vector<std::shared_ptr<lang::Parameter>> shared_parameters;
    shared_parameters.reserve(parameters.size());
    for (lang::Parameter* parameter_ptr : parameters) { shared_parameters.emplace_back(parameter_ptr); }

    lang::Location return_type_location = ctx->type() ? location(ctx->type()) : lang::Location(0, 0, 0, 0);

    auto function_block = lang::CodeBlock::makeInitial(location(ctx));

    for (auto code_context : ctx->code())
    {
        lang::CodeBlock* block     = visit(code_context).as<lang::CodeBlock*>();
        auto             block_ptr = std::unique_ptr<lang::CodeBlock>(block);

        function_block->append(std::move(block_ptr));
    }

    auto function = application_.globalScope().defineCustomFunction(identifier,
                                                                    access,
                                                                    return_type,
                                                                    return_type_location,
                                                                    shared_parameters,
                                                                    std::move(function_block),
                                                                    declaration_location,
                                                                    definition_location);

    return this->visitChildren(ctx);
}

antlrcpp::Any SourceVisitor::visitExternFunctionDeclaration(anceParser::ExternFunctionDeclarationContext* ctx)
{
    std::string                       identifier = ctx->IDENTIFIER()->getText();
    lang::ResolvingHandle<lang::Type> return_type =
        ctx->type() ? visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>() : lang::VoidType::get();
    std::vector<lang::Parameter*> parameters = visit(ctx->parameters()).as<std::vector<lang::Parameter*>>();

    std::vector<std::shared_ptr<lang::Parameter>> shared_parameters;
    shared_parameters.reserve(parameters.size());
    for (lang::Parameter* parameter_ptr : parameters) { shared_parameters.emplace_back(parameter_ptr); }

    lang::Location return_type_location = ctx->type() ? location(ctx->type()) : lang::Location(0, 0, 0, 0);

    application_.globalScope().defineExternFunction(identifier,
                                                    return_type,
                                                    return_type_location,
                                                    shared_parameters,
                                                    location(ctx));

    return this->visitChildren(ctx);
}

antlrcpp::Any SourceVisitor::visitParameters(anceParser::ParametersContext* ctx)
{
    std::vector<lang::Parameter*> params;

    for (auto* param : ctx->parameter()) { params.push_back(visit(param).as<lang::Parameter*>()); }

    return params;
}

antlrcpp::Any SourceVisitor::visitParameter(anceParser::ParameterContext* ctx)
{
    lang::ResolvingHandle<lang::Type> type         = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    const std::string                 k_identifier = ctx->IDENTIFIER()->getText();

    return new lang::Parameter(type, location(ctx->type()), k_identifier, location(ctx));
}

antlrcpp::Any SourceVisitor::visitDefineAs(anceParser::DefineAsContext* ctx)
{
    lang::ResolvingHandle<lang::Type> other = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    application_.globalScope().defineTypeAsOther(ctx->IDENTIFIER()->getText(),
                                                 other,
                                                 location(ctx),
                                                 location(ctx->type()));

    return this->visitChildren(ctx);
}

antlrcpp::Any SourceVisitor::visitDefineAlias(anceParser::DefineAliasContext* ctx)
{
    lang::ResolvingHandle<lang::Type> other = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    application_.globalScope().defineTypeAliasOther(ctx->IDENTIFIER()->getText(),
                                                    other,
                                                    location(ctx),
                                                    location(ctx->type()));

    return this->visitChildren(ctx);
}

antlrcpp::Any SourceVisitor::visitBlock(anceParser::BlockContext* ctx)
{
    lang::CodeBlock* block = lang::CodeBlock::makeScoped(location(ctx));

    for (auto code_context : ctx->code())
    {
        lang::CodeBlock* code     = visit(code_context).as<lang::CodeBlock*>();
        auto             code_ptr = std::unique_ptr<lang::CodeBlock>(code);

        block->append(std::move(code_ptr));
    }

    return block;
}

antlrcpp::Any SourceVisitor::visitExpressionStatement(anceParser::ExpressionStatementContext* ctx)
{
    Expression*                          expression = visit(ctx->independentExpression()).as<Expression*>();
    std::unique_ptr<BuildableExpression> buildable_expression(dynamic_cast<BuildableExpression*>(expression));

    auto statement = std::make_unique<ExpressionStatement>(std::move(buildable_expression), location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx)
{
    lang::ResolvingHandle<lang::Type> type       = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    std::string                       identifier = ctx->IDENTIFIER()->getText();

    lang::Assigner assigner {};
    Expression*    assigned;

    if (ctx->expression())
    {
        assigner = visit(ctx->assigner()).as<lang::Assigner>();
        assigned = visit(ctx->expression()).as<Expression*>();
    }
    else {
        assigner = lang::Assigner::COPY_ASSIGNMENT;
        assigned = nullptr;
    }

    auto statement = std::make_unique<LocalVariableDefinition>(identifier,
                                                               type,
                                                               location(ctx->type()),
                                                               assigner,
                                                               std::unique_ptr<Expression>(assigned),
                                                               location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitLocalReferenceToValueDefinition(
    anceParser::LocalReferenceToValueDefinitionContext* ctx)
{
    lang::ResolvingHandle<lang::Type> type       = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    std::string                       identifier = ctx->IDENTIFIER()->getText();

    Expression* value = visit(ctx->expression()).as<Expression*>();

    auto statement = LocalReferenceVariableDefinition::defineReferring(identifier,
                                                                       type,
                                                                       location(ctx->type()),
                                                                       std::unique_ptr<Expression>(value),
                                                                       location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitLocalReferenceToPointerDefinition(
    anceParser::LocalReferenceToPointerDefinitionContext* ctx)
{
    lang::ResolvingHandle<lang::Type> type       = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    std::string                       identifier = ctx->IDENTIFIER()->getText();

    Expression* address = visit(ctx->expression()).as<Expression*>();

    auto statement = LocalReferenceVariableDefinition::defineReferringTo(identifier,
                                                                         type,
                                                                         location(ctx->type()),
                                                                         std::unique_ptr<Expression>(address),
                                                                         location(ctx));

    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitDropStatement(anceParser::DropStatementContext* ctx)
{
    std::string identifier = ctx->IDENTIFIER()->getText();
    auto        variable   = lang::makeHandled<lang::Variable>(identifier);

    auto statement = std::make_unique<Drop>(variable, location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitAssignment(anceParser::AssignmentContext* ctx)
{
    Expression*    assignable = visit(ctx->assignable).as<Expression*>();
    lang::Assigner assigner   = visit(ctx->assigner()).as<lang::Assigner>();
    Expression*    assigned   = visit(ctx->assigned).as<Expression*>();

    auto statement = std::make_unique<Assignment>(std::unique_ptr<Expression>(assignable),
                                                  assigner,
                                                  std::unique_ptr<Expression>(assigned),
                                                  location(ctx));

    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitDeleteStatement(anceParser::DeleteStatementContext* ctx)
{
    Expression* expression    = visit(ctx->expression()).as<Expression*>();
    bool        delete_buffer = ctx->BUFFER();

    auto statement = std::make_unique<Delete>(std::unique_ptr<Expression>(expression), delete_buffer, location(ctx));

    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitReturnStatement(anceParser::ReturnStatementContext* ctx)
{
    Expression* return_value = nullptr;

    if (ctx->expression() != nullptr) { return_value = visit(ctx->expression()).as<Expression*>(); }

    auto statement = std::make_unique<Return>(std::unique_ptr<Expression>(return_value), location(ctx));

    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitAssertStatement(anceParser::AssertStatementContext* ctx)
{
    Expression* condition = visit(ctx->expression()).as<Expression*>();

    auto statement = std::make_unique<Assertion>(std::unique_ptr<Expression>(condition), location(ctx));
    return lang::CodeBlock::wrapStatement(std::move(statement));
}

antlrcpp::Any SourceVisitor::visitIfStatement(anceParser::IfStatementContext* ctx)
{
    Expression* condition = visit(ctx->expression()).as<Expression*>();
    bool        has_else  = ctx->elseBlock != nullptr;

    auto if_block = std::unique_ptr<lang::CodeBlock>(visit(ctx->ifBlock).as<lang::CodeBlock*>());
    auto else_block =
        has_else ? std::unique_ptr<lang::CodeBlock>(visit(ctx->elseBlock).as<lang::CodeBlock*>()) : nullptr;

    return lang::CodeBlock::wrapStatement(std::make_unique<If>(std::unique_ptr<Expression>(condition),
                                                               std::move(if_block),
                                                               std::move(else_block),
                                                               location(ctx)));
}

antlrcpp::Any SourceVisitor::visitWhileStatement(anceParser::WhileStatementContext* ctx)
{
    Expression* condition = visit(ctx->expression()).as<Expression*>();

    auto block = std::unique_ptr<lang::CodeBlock>(visit(ctx->code()).as<lang::CodeBlock*>());

    return lang::CodeBlock::wrapStatement(
        std::make_unique<While>(std::unique_ptr<Expression>(condition), std::move(block), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitMatchStatement(anceParser::MatchStatementContext* ctx)
{
    Expression* expression = visit(ctx->expression()).as<Expression*>();

    std::vector<std::unique_ptr<Case>> cases;
    for (auto& case_ctx : ctx->matchCase())
    {
        Case* case_instance = visit(case_ctx).as<Case*>();
        cases.push_back(std::unique_ptr<Case>(case_instance));
    }

    return lang::CodeBlock::wrapStatement(
        std::make_unique<Match>(std::move(cases), std::unique_ptr<Expression>(expression), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitLiteralCase(anceParser::LiteralCaseContext* ctx)
{
    auto block = std::unique_ptr<lang::CodeBlock>(visit(ctx->code()).as<lang::CodeBlock*>());

    std::vector<std::unique_ptr<ConstantExpression>> cases;
    for (auto& condition_ctx : ctx->literalExpression())
    {
        auto condition = dynamic_cast<ConstantExpression*>(visit(condition_ctx).as<Expression*>());
        cases.push_back(std::unique_ptr<ConstantExpression>(condition));
    }

    return Case::createCase(std::move(cases), std::move(block));
}

antlrcpp::Any SourceVisitor::visitDefaultCase(anceParser::DefaultCaseContext* ctx)
{
    auto block = std::unique_ptr<lang::CodeBlock>(visit(ctx->code()).as<lang::CodeBlock*>());

    return Case::createDefault(std::move(block));
}

antlrcpp::Any SourceVisitor::visitFunctionCall(anceParser::FunctionCallContext* ctx)
{
    std::string              function_name = ctx->IDENTIFIER()->getText();
    std::vector<Expression*> arguments     = visit(ctx->arguments()).as<std::vector<Expression*>>();

    std::vector<std::unique_ptr<Expression>> unique_expressions;
    unique_expressions.reserve(arguments.size());
    for (Expression* argument_ptr : arguments) { unique_expressions.emplace_back(argument_ptr); }

    auto function_group = lang::makeHandled<lang::FunctionGroup>(function_name);

    return static_cast<Expression*>(new FunctionCall(function_group, std::move(unique_expressions), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitArguments(anceParser::ArgumentsContext* ctx)
{
    std::vector<Expression*> arguments;

    for (auto* argument : ctx->expression()) { arguments.push_back(visit(argument).as<Expression*>()); }

    return arguments;
}

antlrcpp::Any SourceVisitor::visitVariableAccess(anceParser::VariableAccessContext* ctx)
{
    std::string identifier = ctx->IDENTIFIER()->getText();
    auto        variable   = lang::makeHandled<lang::Variable>(identifier);

    return static_cast<Expression*>(new VariableAccess(variable, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitAllocation(anceParser::AllocationContext* ctx)
{
    Runtime::Allocator                allocator = visit(ctx->allocator()).as<Runtime::Allocator>();
    lang::ResolvingHandle<lang::Type> type      = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    Expression*                       count     = nullptr;

    if (ctx->expression()) { count = visit(ctx->expression()).as<Expression*>(); }

    return static_cast<Expression*>(
        new Allocation(allocator, type, std::unique_ptr<Expression>(count), location(ctx), location(ctx->type())));
}

antlrcpp::Any SourceVisitor::visitAddressof(anceParser::AddressofContext* ctx)
{
    Expression* arg = visit(ctx->expression()).as<Expression*>();

    return static_cast<Expression*>(new Addressof(std::unique_ptr<Expression>(arg), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitBindReference(anceParser::BindReferenceContext* ctx)
{
    Expression* value = visit(ctx->expression()).as<Expression*>();

    return static_cast<Expression*>(BindRef::refer(std::unique_ptr<Expression>(value), location(ctx)).release());
}

antlrcpp::Any SourceVisitor::visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx)
{
    Expression* address = visit(ctx->expression()).as<Expression*>();

    return static_cast<Expression*>(BindRef::referTo(std::unique_ptr<Expression>(address), location(ctx)).release());
}

antlrcpp::Any SourceVisitor::visitSizeofType(anceParser::SizeofTypeContext* ctx)
{
    lang::ResolvingHandle<lang::Type> type = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();

    return static_cast<Expression*>(new SizeofType(type, location(ctx->type()), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSizeofExpression(anceParser::SizeofExpressionContext* ctx)
{
    Expression* expr = visit(ctx->expression()).as<Expression*>();

    return static_cast<Expression*>(new SizeofExpression(std::unique_ptr<Expression>(expr), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSubscript(anceParser::SubscriptContext* ctx)
{
    Expression* indexed = visit(ctx->indexed).as<Expression*>();
    Expression* index   = visit(ctx->index).as<Expression*>();

    return static_cast<Expression*>(
        new Subscript(std::unique_ptr<Expression>(indexed), std::unique_ptr<Expression>(index), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitBinaryOperation(anceParser::BinaryOperationContext* ctx)
{
    Expression* left  = visit(ctx->left).as<Expression*>();
    Expression* right = visit(ctx->right).as<Expression*>();

    std::optional<lang::BinaryOperator> op;
    if (ctx->binaryOperatorMultiplicative()) op = visit(ctx->binaryOperatorMultiplicative()).as<lang::BinaryOperator>();
    if (ctx->binaryOperatorAdditive()) op = visit(ctx->binaryOperatorAdditive()).as<lang::BinaryOperator>();
    if (ctx->binaryOperatorRelational()) op = visit(ctx->binaryOperatorRelational()).as<lang::BinaryOperator>();
    if (ctx->binaryOperatorEquality()) op = visit(ctx->binaryOperatorEquality()).as<lang::BinaryOperator>();
    assert(op.has_value());

    return static_cast<Expression*>(new BinaryOperation(std::unique_ptr<Expression>(left),
                                                        op.value(),
                                                        std::unique_ptr<Expression>(right),
                                                        location(ctx)));
}

antlrcpp::Any SourceVisitor::visitParenthesis(anceParser::ParenthesisContext* ctx)
{
    Expression* contained = visit(ctx->expression()).as<Expression*>();
    return static_cast<Expression*>(new Parenthesis(std::unique_ptr<Expression>(contained), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitNotOperation(anceParser::NotOperationContext* ctx)
{
    Expression* value = visit(ctx->expression()).as<Expression*>();
    return static_cast<Expression*>(
        new UnaryOperation(lang::UnaryOperator::NOT, std::unique_ptr<Expression>(value), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitLogicalAnd(anceParser::LogicalAndContext* ctx)
{
    Expression* left  = visit(ctx->left).as<Expression*>();
    Expression* right = visit(ctx->right).as<Expression*>();

    return static_cast<Expression*>(
        new And(std::unique_ptr<Expression>(left), std::unique_ptr<Expression>(right), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitLogicalOr(anceParser::LogicalOrContext* ctx)
{
    Expression* left  = visit(ctx->left).as<Expression*>();
    Expression* right = visit(ctx->right).as<Expression*>();

    return static_cast<Expression*>(
        new Or(std::unique_ptr<Expression>(left), std::unique_ptr<Expression>(right), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitIfExpression(anceParser::IfExpressionContext* ctx)
{
    Expression* condition = visit(ctx->condition).as<Expression*>();

    Expression* then_expression = visit(ctx->thenBlock).as<Expression*>();
    Expression* else_expression = visit(ctx->elseBlock).as<Expression*>();

    return static_cast<Expression*>(new IfSelect(std::unique_ptr<Expression>(condition),
                                                 std::unique_ptr<Expression>(then_expression),
                                                 std::unique_ptr<Expression>(else_expression),
                                                 location(ctx)));
}

antlrcpp::Any SourceVisitor::visitMatchExpression(anceParser::MatchExpressionContext* ctx)
{
    Expression* expression = visit(ctx->expression()).as<Expression*>();

    std::vector<std::unique_ptr<Case>> cases;
    for (auto& case_ctx : ctx->matchExpressionCase())
    {
        Case* case_instance = visit(case_ctx).as<Case*>();
        cases.push_back(std::unique_ptr<Case>(case_instance));
    }

    return static_cast<Expression*>(
        new MatchSelect(std::unique_ptr<Expression>(expression), std::move(cases), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitDefaultExpressionCase(anceParser::DefaultExpressionCaseContext* ctx)
{
    auto expression = std::unique_ptr<Expression>(visit(ctx->expression()).as<Expression*>());

    return Case::createDefault(std::move(expression));
}

antlrcpp::Any SourceVisitor::visitLiteralExpressionCase(anceParser::LiteralExpressionCaseContext* ctx)
{
    auto block = std::unique_ptr<Expression>(visit(ctx->expression()).as<Expression*>());

    std::vector<std::unique_ptr<ConstantExpression>> cases;
    for (auto& condition_ctx : ctx->literalExpression())
    {
        auto condition = dynamic_cast<ConstantExpression*>(visit(condition_ctx).as<Expression*>());
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

antlrcpp::Any SourceVisitor::visitUnsignedInteger(anceParser::UnsignedIntegerContext* ctx)
{
    uint64_t size = parseIntegerTypeSize(ctx->width->getText());

    std::shared_ptr<lang::Constant> integer_constant =
        std::make_shared<lang::IntegerConstant>(ctx->value->getText(), size, false);
    return static_cast<Expression*>(new ConstantLiteral(integer_constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSignedInteger(anceParser::SignedIntegerContext* ctx)
{
    uint64_t size = parseIntegerTypeSize(ctx->width->getText());

    std::shared_ptr<lang::Constant> integer_constant =
        std::make_shared<lang::IntegerConstant>(ctx->value->getText(), size, true);
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
    lang::ResolvingHandle<lang::Type> element_type = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    uint64_t                          size         = parseArrayTypeSize(ctx->INTEGER()->getText());
    lang::ResolvingHandle<lang::Type> type         = lang::ArrayType::get(element_type, size);

    return type;
}

antlrcpp::Any SourceVisitor::visitKeywordType(anceParser::KeywordTypeContext* ctx)
{
    return application_.globalScope().getType(ctx->getText()).value();
}

antlrcpp::Any SourceVisitor::visitPointer(anceParser::PointerContext* ctx)
{
    lang::ResolvingHandle<lang::Type> element_type = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    lang::ResolvingHandle<lang::Type> type         = lang::PointerType::get(element_type);

    return type;
}

antlrcpp::Any SourceVisitor::visitReference(anceParser::ReferenceContext* ctx)
{
    lang::ResolvingHandle<lang::Type> element_type = visit(ctx->type()).as<lang::ResolvingHandle<lang::Type>>();
    lang::ResolvingHandle<lang::Type> type         = lang::ReferenceType::get(element_type);

    return type;
}

antlrcpp::Any SourceVisitor::visitCustom(anceParser::CustomContext* ctx)
{
    return lang::makeHandled<lang::Type>(ctx->getText());
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
