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

#include "ance/scope/GlobalScope.h"
#include "ance/scope/LocalScope.h"

#include "ance/construct/DefinedFunction.h"
#include "ance/construct/ExternFunction.h"
#include "ance/construct/Parameter.h"

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
        ->defineGlobalVariable(access, is_constant, identifier, type, assigner, const_expr, location(ctx));

    return this->visitChildren(ctx);
}

antlrcpp::Any SourceVisitor::visitFunctionDefinition(anceParser::FunctionDefinitionContext* ctx)
{
    AccessModifier access      = visit(ctx->accessModifier());
    ance::Type*    return_type = visit(ctx->type());

    ance::Location declaration_location = location(ctx);
    ance::Location definition_location =
        ctx->statement().empty() ? declaration_location : location(ctx->statement()[0]);

    std::vector<ance::Parameter*> parameters = visit(ctx->parameters());

    auto* function = new ance::DefinedFunction(access,
                                               ctx->IDENTIFIER()->getText(),
                                               return_type,
                                               parameters,
                                               application_.globalScope(),
                                               declaration_location,
                                               definition_location);

    application_.globalScope()->addFunction(function);

    for (auto statement_context : ctx->statement())
    {
        Statement* statement = visit(statement_context);
        function->pushStatement(statement);
    }

    return this->visitChildren(ctx);
}

antlrcpp::Any SourceVisitor::visitExternFunctionDeclaration(anceParser::ExternFunctionDeclarationContext* ctx)
{
    ance::Type*                   return_type = visit(ctx->type());
    std::vector<ance::Parameter*> parameters  = visit(ctx->parameters());

    auto* function = new ance::ExternFunction(ctx->IDENTIFIER()->getText(), return_type, parameters, location(ctx));
    application_.globalScope()->addFunction(function);

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
    Expression* expression           = visit(ctx->independentExpression());
    auto*       buildable_expression = dynamic_cast<BuildableExpression*>(expression);

    auto* statement = new ExpressionStatement(buildable_expression, location(ctx));
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

    auto* statement = new LocalVariableDefinition(identifier, type, assigner, assigned, location(ctx));
    return static_cast<Statement*>(statement);
}

antlrcpp::Any SourceVisitor::visitLocalReferenceToValueDefinition(
    anceParser::LocalReferenceToValueDefinitionContext* ctx)
{
    ance::Type* type       = visit(ctx->type());
    std::string identifier = ctx->IDENTIFIER()->getText();

    Expression* value = visit(ctx->expression());

    return static_cast<Statement*>(
        LocalReferenceVariableDefinition::defineReferring(identifier, type, value, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitLocalReferenceToPointerDefinition(
    anceParser::LocalReferenceToPointerDefinitionContext* ctx)
{
    ance::Type* type       = visit(ctx->type());
    std::string identifier = ctx->IDENTIFIER()->getText();

    Expression* address = visit(ctx->expression());

    return static_cast<Statement*>(
        LocalReferenceVariableDefinition::defineReferringTo(identifier, type, address, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitAssignment(anceParser::AssignmentContext* ctx)
{
    Expression* assignable = visit(ctx->assignable);
    Assigner    assigner   = visit(ctx->assigner());
    Expression* assigned   = visit(ctx->assigned);

    auto* statement = new AssignmentStatement(assignable, assigner, assigned, location(ctx));
    return static_cast<Statement*>(statement);
}

antlrcpp::Any SourceVisitor::visitDeleteStatement(anceParser::DeleteStatementContext* ctx)
{
    Expression* expression    = visit(ctx->expression());
    bool        delete_buffer = ctx->BUFFER();

    return static_cast<Statement*>(new DeleteStatement(expression, delete_buffer, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitReturnStatement(anceParser::ReturnStatementContext* ctx)
{
    Expression* return_value = nullptr;

    if (ctx->expression() != nullptr) { return_value = visit(ctx->expression()); }

    auto* statement = new ReturnStatement(return_value, location(ctx));
    return static_cast<Statement*>(statement);
}

antlrcpp::Any SourceVisitor::visitFunctionCall(anceParser::FunctionCallContext* ctx)
{
    std::string              identifier = ctx->IDENTIFIER()->getText();
    std::vector<Expression*> arguments  = visit(ctx->arguments());

    // Call to highest scope intentional, as actual scope of called function is not known.
    application_.globalScope()->addFunctionName(identifier);

    return static_cast<Expression*>(new FunctionCall(identifier, arguments, location(ctx)));
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
    Expression* expression = new VariableAccess(identifier, location(ctx));
    return expression;
}

antlrcpp::Any SourceVisitor::visitAllocation(anceParser::AllocationContext* ctx)
{
    Runtime::Allocator allocator = visit(ctx->allocator());
    ance::Type*        type      = visit(ctx->type());
    Expression*        count     = nullptr;

    if (ctx->expression()) { count = visit(ctx->expression()); }

    return static_cast<Expression*>(new Allocation(allocator, type, count, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitRoughCast(anceParser::RoughCastContext* ctx)
{
    ance::Type* type = visit(ctx->type());
    Expression* expr = visit(ctx->expression());

    return static_cast<Expression*>(new RoughCast(type, expr, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitAddressof(anceParser::AddressofContext* ctx)
{
    Expression* arg = visit(ctx->expression());

    return static_cast<Expression*>(new Addressof(arg, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitBindReference(anceParser::BindReferenceContext* ctx)
{
    Expression* value = visit(ctx->expression());

    return static_cast<Expression*>(BindRef::refer(value, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx)
{
    Expression* address = visit(ctx->expression());

    return static_cast<Expression*>(BindRef::referTo(address, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSizeofType(anceParser::SizeofTypeContext* ctx)
{
    ance::Type* type = visit(ctx->type());

    return static_cast<Expression*>(new SizeofType(type, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSizeofExpression(anceParser::SizeofExpressionContext* ctx)
{
    Expression* expr = visit(ctx->expression());

    return static_cast<Expression*>(new SizeofExpression(expr, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSubscript(anceParser::SubscriptContext* ctx)
{
    Expression* indexed = visit(ctx->indexed);
    Expression* index   = visit(ctx->index);

    return static_cast<Expression*>(new Subscript(indexed, index, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitStringLiteral(anceParser::StringLiteralContext* ctx)
{
    std::string prefix;

    if (ctx->prefix) { prefix = ctx->prefix->getText(); }

    std::string str = ance::StringConstant::parse(ctx->STRING()->getText());

    ance::Constant* string = new ance::StringConstant(prefix, str, application_);
    return static_cast<Expression*>(new ConstantLiteral(string, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitByteLiteral(anceParser::ByteLiteralContext* ctx)
{
    uint8_t b = ance::ByteConstant::parse(ctx->BYTE()->getText());

    ance::Constant* byte = new ance::ByteConstant(b, application_);
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

    auto* flt = new ance::FloatConstant(number, type);
    return static_cast<Expression*>(new ConstantLiteral(flt, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitTrue(anceParser::TrueContext* ctx)
{
    ance::Constant* constant = ance::BooleanConstant::createTrue(application_);
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitFalse(anceParser::FalseContext* ctx)
{
    ance::Constant* constant = ance::BooleanConstant::createFalse(application_);
    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitSizeLiteral(anceParser::SizeLiteralContext* ctx)
{
    std::string     value    = ctx->INTEGER()->getText();
    ance::Constant* constant = new ance::SizeConstant(value);

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitDiffLiteral(anceParser::DiffLiteralContext* ctx)
{
    std::string     value    = ctx->SIGNED_INTEGER()->getText();
    ance::Constant* constant = new ance::DiffConstant(value);

    return static_cast<Expression*>(new ConstantLiteral(constant, location(ctx)));
}

antlrcpp::Any SourceVisitor::visitUnsignedInteger(anceParser::UnsignedIntegerContext* ctx)
{
    uint64_t size = std::stoi(ctx->width->getText());

    const llvm::APInt integer(size, ctx->value->getText(), 10);
    auto*             integer_constant = new ance::IntegerConstant(integer, false, application_);
    Expression*       expression       = new ConstantLiteral(integer_constant, location(ctx));
    return expression;
}

antlrcpp::Any SourceVisitor::visitSignedInteger(anceParser::SignedIntegerContext* ctx)
{
    uint64_t size = std::stoi(ctx->width->getText());

    const llvm::APInt integer(size, ctx->value->getText(), 10);
    auto*             integer_constant = new ance::IntegerConstant(integer, true, application_);
    Expression*       expression       = new ConstantLiteral(integer_constant, location(ctx));
    return expression;
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

    const llvm::APInt integer(size, integer_str, radix);
    auto*             integer_constant = new ance::IntegerConstant(integer, false, application_);
    Expression*       expression       = new ConstantLiteral(integer_constant, location(ctx));
    return expression;
}

antlrcpp::Any SourceVisitor::visitIntegerType(anceParser::IntegerTypeContext* ctx)
{
    ance::Type* type;

    std::string integer_type_str = ctx->NATIVE_INTEGER_TYPE()->getText();

    bool     is_unsigned = integer_type_str[0] == 'u';
    uint64_t size        = std::stoi(integer_type_str.substr(1 + integer_type_str.find('i')));

    type = ance::IntegerType::get(application_, size, !is_unsigned);

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
    ance::Type* type = application_.globalScope()->getType(ctx->getText());
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
