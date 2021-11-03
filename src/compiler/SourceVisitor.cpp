#include "SourceVisitor.h"

#include <stdexcept>

#include "compiler/Application.h"

#include "ance/type/ArrayType.h"
#include "ance/type/DoubleType.h"
#include "ance/type/HalfType.h"
#include "ance/type/IntegerType.h"
#include "ance/type/PointerType.h"
#include "ance/type/QuadType.h"
#include "ance/type/ReferenceType.h"
#include "ance/type/SingleType.h"
#include "ance/type/VoidType.h"

#include "ance/scope/LocalScope.h"

#include "ance/statement/AssignmentStatement.h"
#include "ance/statement/DeleteStatement.h"
#include "ance/statement/ExpressionStatement.h"
#include "ance/statement/LocalReferenceVariableDefinition.h"
#include "ance/statement/LocalVariableDefinition.h"
#include "ance/statement/ReturnStatement.h"

#include "ance/expression/Addressof.h"
#include "ance/expression/Allocation.h"
#include "ance/expression/BackingExpression.h"
#include "ance/expression/BindRef.h"
#include "ance/expression/ConstantLiteral.h"
#include "ance/expression/DefaultValue.h"
#include "ance/expression/FunctionCall.h"
#include "ance/expression/RoughCast.h"
#include "ance/expression/SizeofExpression.h"
#include "ance/expression/SizeofType.h"
#include "ance/expression/Subscript.h"
#include "ance/expression/VariableAccess.h"

#include "ance/construct/constant/BooleanConstant.h"
#include "ance/construct/constant/ByteConstant.h"
#include "ance/construct/constant/DiffConstant.h"
#include "ance/construct/constant/FloatConstant.h"
#include "ance/construct/constant/IntegerConstant.h"
#include "ance/construct/constant/SizeConstant.h"
#include "ance/construct/constant/StringConstant.h"

SourceVisitor::SourceVisitor(Application& application) : application_(application) {}

antlrcpp::Any SourceVisitor::visitVariableDeclaration(anceParser::VariableDeclarationContext* ctx)
{
    AccessModifier access      = visit(ctx->accessModifier());
    bool           is_constant = ctx->CONST();
    ance::Type*    type        = visit(ctx->type());
    std::string    identifier  = ctx->IDENTIFIER()->getText();

    ConstantExpression* const_expr;
    Assigner            assigner = Assigner::COPY_ASSIGNMENT;

    if (ctx->literalExpression())
    {
        assigner = visit(ctx->assigner());

        Expression* expr = visit(ctx->literalExpression());
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

    application_.globalScope()
        .defineGlobalVariable(access, is_constant, identifier, type, assigner, const_expr, location(ctx));

    return this->visitChildren(ctx);
}

antlrcpp::Any SourceVisitor::visitFunctionDefinition(anceParser::FunctionDefinitionContext* ctx)
{
    AccessModifier access      = visit(ctx->accessModifier());
    std::string    identifier  = ctx->IDENTIFIER()->getText();
    ance::Type*    return_type = ctx->type() ? (ance::Type*) visit(ctx->type()) : ance::VoidType::get();

    ance::Location declaration_location = location(ctx);
    ance::Location definition_location =
        ctx->statement().empty() ? declaration_location : location(ctx->statement()[0]);

    std::vector<ance::Parameter*> parameters = visit(ctx->parameters());

    std::vector<std::shared_ptr<ance::Parameter>> shared_parameters;
    shared_parameters.reserve(parameters.size());
    for (ance::Parameter* parameter_ptr : parameters) { shared_parameters.emplace_back(parameter_ptr); }

    auto function = application_.globalScope().defineCustomFunction(identifier,
                                                                    access,
                                                                    return_type,
                                                                    shared_parameters,
                                                                    declaration_location,
                                                                    definition_location);

    for (auto statement_context : ctx->statement())
    {
        Statement* statement = visit(statement_context);
        function->pushStatement(statement);
    }

    return this->visitChildren(ctx);
}

antlrcpp::Any SourceVisitor::visitExternFunctionDeclaration(anceParser::ExternFunctionDeclarationContext* ctx)
{
    std::string                   identifier  = ctx->IDENTIFIER()->getText();
    ance::Type*                   return_type = ctx->type() ? (ance::Type*) visit(ctx->type()) : ance::VoidType::get();
    std::vector<ance::Parameter*> parameters  = visit(ctx->parameters());

    std::vector<std::shared_ptr<ance::Parameter>> shared_parameters;
    shared_parameters.reserve(parameters.size());
    for (ance::Parameter* parameter_ptr : parameters) { shared_parameters.emplace_back(parameter_ptr); }

    application_.globalScope().defineExternFunction(identifier, return_type, shared_parameters, location(ctx));

    return this->visitChildren(ctx);
}

antlrcpp::Any SourceVisitor::visitParameters(anceParser::ParametersContext* ctx)
{
    std::vector<ance::Parameter*> params;

    for (auto* param : ctx->parameter()) { params.push_back(visit(param)); }

    return params;
}

antlrcpp::Any SourceVisitor::visitParameter(anceParser::ParameterContext* ctx)
{
    ance::Type*       type         = visit(ctx->type());
    const std::string k_identifier = ctx->IDENTIFIER()->getText();

    return new ance::Parameter(type, k_identifier, location(ctx));
}

antlrcpp::Any SourceVisitor::visitExpressionStatement(anceParser::ExpressionStatementContext* ctx)
{
    Expression*                          expression = visit(ctx->independentExpression());
    std::unique_ptr<BuildableExpression> buildable_expression(dynamic_cast<BuildableExpression*>(expression));

    auto* statement = new ExpressionStatement(std::move(buildable_expression), location(ctx));
    return static_cast<Statement*>(statement);
}

antlrcpp::Any SourceVisitor::visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx)
{
    ance::Type* type       = visit(ctx->type());
    std::string identifier = ctx->IDENTIFIER()->getText();

    Assigner    assigner {};
    Expression* assigned;

    if (ctx->expression())
    {
        assigner = visit(ctx->assigner());
        assigned = visit(ctx->expression());
    }
    else
    {
        assigner = Assigner::COPY_ASSIGNMENT;
        assigned = new DefaultValue(type, location(ctx));
    }

    return static_cast<Statement*>(
        new LocalVariableDefinition(identifier, type, assigner, std::unique_ptr<Expression>(assigned), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitLocalReferenceToValueDefinition(
    anceParser::LocalReferenceToValueDefinitionContext* ctx)
{
    ance::Type* type       = visit(ctx->type());
    std::string identifier = ctx->IDENTIFIER()->getText();

    Expression* value = visit(ctx->expression());

    return static_cast<Statement*>(LocalReferenceVariableDefinition::defineReferring(identifier,
                                                                                     type,
                                                                                     std::unique_ptr<Expression>(value),
                                                                                     location(ctx)));
}

antlrcpp::Any SourceVisitor::visitLocalReferenceToPointerDefinition(
    anceParser::LocalReferenceToPointerDefinitionContext* ctx)
{
    ance::Type* type       = visit(ctx->type());
    std::string identifier = ctx->IDENTIFIER()->getText();

    Expression* address = visit(ctx->expression());

    return static_cast<Statement*>(
        LocalReferenceVariableDefinition::defineReferringTo(identifier,
                                                            type,
                                                            std::unique_ptr<Expression>(address),
                                                            location(ctx)));
}

antlrcpp::Any SourceVisitor::visitAssignment(anceParser::AssignmentContext* ctx)
{
    Expression* assignable = visit(ctx->assignable);
    Assigner    assigner   = visit(ctx->assigner());
    Expression* assigned   = visit(ctx->assigned);

    return static_cast<Statement*>(new AssignmentStatement(std::unique_ptr<Expression>(assignable),
                                                           assigner,
                                                           std::unique_ptr<Expression>(assigned),
                                                           location(ctx)));
}

antlrcpp::Any SourceVisitor::visitDeleteStatement(anceParser::DeleteStatementContext* ctx)
{
    Expression* expression    = visit(ctx->expression());
    bool        delete_buffer = ctx->BUFFER();

    return static_cast<Statement*>(
        new DeleteStatement(std::unique_ptr<Expression>(expression), delete_buffer, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitReturnStatement(anceParser::ReturnStatementContext* ctx)
{
    Expression* return_value = nullptr;

    if (ctx->expression() != nullptr) { return_value = visit(ctx->expression()); }

    return static_cast<Statement*>(new ReturnStatement(std::unique_ptr<Expression>(return_value), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitFunctionCall(anceParser::FunctionCallContext* ctx)
{
    std::string              function_name = ctx->IDENTIFIER()->getText();
    std::vector<Expression*> arguments     = visit(ctx->arguments());

    std::vector<std::unique_ptr<Expression>> unique_expressions;
    unique_expressions.reserve(arguments.size());
    for (Expression* argument_ptr : arguments) { unique_expressions.emplace_back(argument_ptr); }

    auto function = ance::makeHandled<ance::Function>(function_name);

    return static_cast<Expression*>(new FunctionCall(function, std::move(unique_expressions), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitArguments(anceParser::ArgumentsContext* ctx)
{
    std::vector<Expression*> arguments;

    for (auto* argument : ctx->expression()) { arguments.push_back(visit(argument)); }

    return arguments;
}

antlrcpp::Any SourceVisitor::visitVariableAccess(anceParser::VariableAccessContext* ctx)
{
    std::string identifier = ctx->IDENTIFIER()->getText();
    auto        variable   = ance::makeHandled<ance::Variable>(identifier);

    return static_cast<Expression*>(new VariableAccess(variable, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitAllocation(anceParser::AllocationContext* ctx)
{
    Runtime::Allocator allocator = visit(ctx->allocator());
    ance::Type*        type      = visit(ctx->type());
    Expression*        count     = nullptr;

    if (ctx->expression()) { count = visit(ctx->expression()); }

    return static_cast<Expression*>(new Allocation(allocator, type, std::unique_ptr<Expression>(count), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitRoughCast(anceParser::RoughCastContext* ctx)
{
    ance::Type* type = visit(ctx->type());
    Expression* expr = visit(ctx->expression());

    return static_cast<Expression*>(new RoughCast(type, std::unique_ptr<Expression>(expr), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitAddressof(anceParser::AddressofContext* ctx)
{
    Expression* arg = visit(ctx->expression());

    return static_cast<Expression*>(new Addressof(std::unique_ptr<Expression>(arg), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitBindReference(anceParser::BindReferenceContext* ctx)
{
    Expression* value = visit(ctx->expression());

    return static_cast<Expression*>(BindRef::refer(std::unique_ptr<Expression>(value), location(ctx)).release());
}

antlrcpp::Any SourceVisitor::visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx)
{
    Expression* address = visit(ctx->expression());

    return static_cast<Expression*>(BindRef::referTo(std::unique_ptr<Expression>(address), location(ctx)).release());
}

antlrcpp::Any SourceVisitor::visitSizeofType(anceParser::SizeofTypeContext* ctx)
{
    ance::Type* type = visit(ctx->type());

    return static_cast<Expression*>(new SizeofType(type, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSizeofExpression(anceParser::SizeofExpressionContext* ctx)
{
    Expression* expr = visit(ctx->expression());

    return static_cast<Expression*>(new SizeofExpression(std::unique_ptr<Expression>(expr), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSubscript(anceParser::SubscriptContext* ctx)
{
    Expression* indexed = visit(ctx->indexed);
    Expression* index   = visit(ctx->index);

    return static_cast<Expression*>(
        new Subscript(std::unique_ptr<Expression>(indexed), std::unique_ptr<Expression>(index), location(ctx)));
}

antlrcpp::Any SourceVisitor::visitStringLiteral(anceParser::StringLiteralContext* ctx)
{
    std::string prefix;

    if (ctx->prefix) { prefix = ctx->prefix->getText(); }

    std::string str = ance::StringConstant::parse(ctx->STRING()->getText());

    std::shared_ptr<ance::Constant> string = std::make_shared<ance::StringConstant>(prefix, str);
    return static_cast<Expression*>(new ConstantLiteral(string, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitByteLiteral(anceParser::ByteLiteralContext* ctx)
{
    uint8_t b = ance::ByteConstant::parse(ctx->BYTE()->getText());

    std::shared_ptr<ance::Constant> byte = std::make_shared<ance::ByteConstant>(b);
    return static_cast<Expression*>(new ConstantLiteral(byte, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx)
{
    llvm::APFloat            number = llvm::APFloat::getZero(llvm::APFloat::Bogus());
    ance::FloatingPointType* type   = nullptr;

    if (ctx->HALF())
    {
        number = llvm::APFloat(llvm::APFloat::IEEEhalf(), ctx->getText().erase(ctx->getText().size() - 1));
        type   = ance::HalfType::get();
    }

    if (ctx->SINGLE())
    {
        number = llvm::APFloat(llvm::APFloat::IEEEsingle(), ctx->getText().erase(ctx->getText().size() - 1));
        type   = ance::SingleType::get();
    }

    if (ctx->DOUBLE())
    {
        number = llvm::APFloat(llvm::APFloat::IEEEdouble(), ctx->getText().erase(ctx->getText().size() - 1));
        type   = ance::DoubleType::get();
    }

    if (ctx->QUAD())
    {
        number = llvm::APFloat(llvm::APFloat::IEEEquad(), ctx->getText().erase(ctx->getText().size() - 1));
        type   = ance::QuadType::get();
    }

    std::shared_ptr<ance::Constant> flt = std::make_shared<ance::FloatConstant>(number, type);
    return static_cast<Expression*>(new ConstantLiteral(flt, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitTrue(anceParser::TrueContext* ctx)
{
    std::shared_ptr<ance::Constant> constant = ance::BooleanConstant::createTrue();
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitFalse(anceParser::FalseContext* ctx)
{
    std::shared_ptr<ance::Constant> constant = ance::BooleanConstant::createFalse();
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSizeLiteral(anceParser::SizeLiteralContext* ctx)
{
    std::string                     value    = ctx->INTEGER()->getText();
    std::shared_ptr<ance::Constant> constant = std::make_shared<ance::SizeConstant>(value);

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitDiffLiteral(anceParser::DiffLiteralContext* ctx)
{
    std::string                     value    = ctx->SIGNED_INTEGER()->getText();
    std::shared_ptr<ance::Constant> constant = std::make_shared<ance::DiffConstant>(value);

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitUnsignedInteger(anceParser::UnsignedIntegerContext* ctx)
{
    uint64_t size = std::stoi(ctx->width->getText());

    const llvm::APInt               integer(size, ctx->value->getText(), 10);
    std::shared_ptr<ance::Constant> integer_constant = std::make_shared<ance::IntegerConstant>(integer, false);
    return static_cast<Expression*>(new ConstantLiteral(integer_constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSignedInteger(anceParser::SignedIntegerContext* ctx)
{
    uint64_t size = std::stoi(ctx->width->getText());

    const llvm::APInt               integer(size, ctx->value->getText(), 10);
    std::shared_ptr<ance::Constant> integer_constant = std::make_shared<ance::IntegerConstant>(integer, true);
    return static_cast<Expression*>(new ConstantLiteral(integer_constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSpecialInteger(anceParser::SpecialIntegerContext* ctx)
{
    uint64_t size = std::stoi(ctx->width->getText());

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

    const llvm::APInt               integer(size, integer_str, radix);
    std::shared_ptr<ance::Constant> integer_constant = std::make_shared<ance::IntegerConstant>(integer, false);
    return static_cast<Expression*>(new ConstantLiteral(integer_constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitIntegerType(anceParser::IntegerTypeContext* ctx)
{
    ance::Type* type;

    std::string integer_type_str = ctx->NATIVE_INTEGER_TYPE()->getText();

    bool     is_unsigned = integer_type_str[0] == 'u';
    uint64_t size        = std::stoi(integer_type_str.substr(1 + integer_type_str.find('i')));

    type = ance::IntegerType::get(size, !is_unsigned);

    return type;
}

antlrcpp::Any SourceVisitor::visitArrayType(anceParser::ArrayTypeContext* ctx)
{
    ance::Type* type;

    ance::Type* element_type = visit(ctx->type());
    uint64_t    size         = std::stoi(ctx->INTEGER()->getText());
    type                     = ance::ArrayType::get(element_type, size);

    return type;
}

antlrcpp::Any SourceVisitor::visitKeywordType(anceParser::KeywordTypeContext* ctx)
{
    ance::Type* type = application_.globalScope().getType(ctx->getText());
    return type;
}

antlrcpp::Any SourceVisitor::visitPointer(anceParser::PointerContext* ctx)
{
    ance::Type* element_type = visit(ctx->type());
    ance::Type* type         = ance::PointerType::get(element_type);

    return type;
}

antlrcpp::Any SourceVisitor::visitReference(anceParser::ReferenceContext* ctx)
{
    ance::Type* element_type = visit(ctx->type());
    ance::Type* type         = ance::ReferenceType::get(element_type);

    return type;
}

antlrcpp::Any SourceVisitor::visitPublic(anceParser::PublicContext*)
{
    AccessModifier access_modifier = AccessModifier::PUBLIC_ACCESS;
    return access_modifier;
}

antlrcpp::Any SourceVisitor::visitPrivate(anceParser::PrivateContext*)
{
    AccessModifier access_modifier = AccessModifier::PRIVATE_ACCESS;
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
    Assigner assigner = Assigner::COPY_ASSIGNMENT;
    return assigner;
}

antlrcpp::Any SourceVisitor::visitMoveAssignment(anceParser::MoveAssignmentContext*)
{
    assert(false && "Move assignment currently not supported.");
    // todo: move assignment

    Assigner assigner = Assigner::MOVE_ASSIGNMENT;
    return assigner;
}

antlrcpp::Any SourceVisitor::visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext*)
{
    Assigner assigner = Assigner::FINAL_COPY_ASSIGNMENT;
    return assigner;
}

ance::Location SourceVisitor::location(antlr4::ParserRuleContext* ctx)
{
    unsigned start_line   = ctx->getStart()->getLine();
    unsigned start_column = ctx->getStart()->getCharPositionInLine() + 1;

    unsigned end_line   = ctx->getStop()->getLine();
    unsigned end_column = ctx->getStop()->getCharPositionInLine() + ctx->getStop()->getText().size();

    return ance::Location(start_line, start_column, end_line, end_column);
}
