#ifndef ANCE_SRC_COMPILER_SOURCEVISITOR_H_
#define ANCE_SRC_COMPILER_SOURCEVISITOR_H_

#include "anceBaseVisitor.h"

#include "compiler/FileContext.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/Location.h"
#include "lang/utility/Optional.h"

class Unit;

namespace lang
{
    class Context;
}

/**
 * The ance syntax visitor creating the application. Base class is generated.
 */
class SourceVisitor : public anceBaseVisitor
{
  public:
    /**
     * Create a new visitor.
     * @param unit The application to create.
     */
    explicit SourceVisitor(Unit& unit);

    /**
     * Set the current file context;
     * @param file_context The file context.
     */
    void setFileContext(FileContext& file_context);

    std::any visitProjectFile(anceParser::ProjectFileContext* ctx) override;
    std::any visitGlobal(anceParser::GlobalContext* ctx) override;

    // Descriptions

    std::any visitVariableDescription(anceParser::VariableDescriptionContext* ctx) override;
    std::any visitStructDescription(anceParser::StructDescriptionContext* ctx) override;
    std::any visitMember(anceParser::MemberContext* ctx) override;
    std::any visitFunctionDescription(anceParser::FunctionDescriptionContext* ctx) override;
    std::any visitParameters(anceParser::ParametersContext* ctx) override;
    std::any visitParameter(anceParser::ParameterContext* ctx) override;
    std::any visitAliasDescription(anceParser::AliasDescriptionContext* ctx) override;

    // Statements

    std::any visitBlock(anceParser::BlockContext* ctx) override;

    std::any visitExpressionStatement(anceParser::ExpressionStatementContext* ctx) override;
    std::any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx) override;
    std::any visitLocalReferenceDefinition(anceParser::LocalReferenceDefinitionContext* ctx) override;
    std::any visitEraseStatement(anceParser::EraseStatementContext* ctx) override;
    std::any visitAssignment(anceParser::AssignmentContext* ctx) override;
    std::any visitDeleteStatement(anceParser::DeleteStatementContext* ctx) override;
    std::any visitBreakStatement(anceParser::BreakStatementContext* ctx) override;
    std::any visitContinueStatement(anceParser::ContinueStatementContext* ctx) override;
    std::any visitReturnStatement(anceParser::ReturnStatementContext* ctx) override;
    std::any visitAssertStatement(anceParser::AssertStatementContext* ctx) override;
    std::any visitIfStatement(anceParser::IfStatementContext* ctx) override;
    std::any visitWhileStatement(anceParser::WhileStatementContext* ctx) override;
    std::any visitLoopStatement(anceParser::LoopStatementContext* ctx) override;
    std::any visitMatchStatement(anceParser::MatchStatementContext* ctx) override;
    std::any visitLiteralCase(anceParser::LiteralCaseContext* ctx) override;
    std::any visitDefaultCase(anceParser::DefaultCaseContext* ctx) override;

    // Expressions

    std::any visitMemberAccess(anceParser::MemberAccessContext* ctx) override;
    std::any visitFunctionCall(anceParser::FunctionCallContext* ctx) override;
    std::any visitArguments(anceParser::ArgumentsContext* ctx) override;
    std::any visitVariableAccess(anceParser::VariableAccessContext* ctx) override;
    std::any visitAllocation(anceParser::AllocationContext* ctx) override;
    std::any visitAddressof(anceParser::AddressofContext* ctx) override;
    std::any visitBindReference(anceParser::BindReferenceContext* ctx) override;
    std::any visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx) override;
    std::any visitCast(anceParser::CastContext* ctx) override;
    std::any visitSizeofType(anceParser::SizeofTypeContext* ctx) override;
    std::any visitSizeofExpression(anceParser::SizeofExpressionContext* ctx) override;
    std::any visitSubscript(anceParser::SubscriptContext* ctx) override;
    std::any visitUnaryOperation(anceParser::UnaryOperationContext* ctx) override;
    std::any visitBinaryOperation(anceParser::BinaryOperationContext* ctx) override;
    std::any visitParenthesis(anceParser::ParenthesisContext* ctx) override;
    std::any visitLogicalAnd(anceParser::LogicalAndContext* ctx) override;
    std::any visitLogicalOr(anceParser::LogicalOrContext* ctx) override;
    std::any visitIfExpression(anceParser::IfExpressionContext* ctx) override;
    std::any visitDefaultExpressionCase(anceParser::DefaultExpressionCaseContext* ctx) override;
    std::any visitLiteralExpressionCase(anceParser::LiteralExpressionCaseContext* ctx) override;
    std::any visitMatchExpression(anceParser::MatchExpressionContext* ctx) override;
    std::any visitIndirection(anceParser::IndirectionContext* ctx) override;
    std::any visitVectorDefinition(anceParser::VectorDefinitionContext* ctx) override;
    std::any visitArrayDefinition(anceParser::ArrayDefinitionContext* ctx) override;

    // Literals and Types

    std::any visitStringLiteral(anceParser::StringLiteralContext* ctx) override;
    std::any visitCharLiteral(anceParser::CharLiteralContext* ctx) override;
    std::any visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx) override;
    std::any visitTrue(anceParser::TrueContext* ctx) override;
    std::any visitFalse(anceParser::FalseContext* ctx) override;
    std::any visitNull(anceParser::NullContext* ctx) override;
    std::any visitSizeLiteral(anceParser::SizeLiteralContext* ctx) override;
    std::any visitDiffLiteral(anceParser::DiffLiteralContext* ctx) override;
    std::any visitUiptrLiteral(anceParser::UiptrLiteralContext* ctx) override;
    std::any visitNormalInteger(anceParser::NormalIntegerContext* ctx) override;
    std::any visitSpecialInteger(anceParser::SpecialIntegerContext* ctx) override;
    std::any visitUnitLiteral(anceParser::UnitLiteralContext* ctx) override;
    std::any visitIntegerType(anceParser::IntegerTypeContext* ctx) override;
    std::any visitBooleanType(anceParser::BooleanTypeContext* ctx) override;
    std::any visitArrayType(anceParser::ArrayTypeContext* ctx) override;
    std::any visitVectorType(anceParser::VectorTypeContext* ctx) override;
    std::any visitKeywordType(anceParser::KeywordTypeContext* ctx) override;
    std::any visitPointer(anceParser::PointerContext* ctx) override;
    std::any visitBuffer(anceParser::BufferContext* ctx) override;
    std::any visitReference(anceParser::ReferenceContext* ctx) override;
    std::any visitCustom(anceParser::CustomContext* ctx) override;

    // Other

    std::any visitPublic(anceParser::PublicContext* ctx) override;
    std::any visitPrivate(anceParser::PrivateContext* ctx) override;
    std::any visitExtern(anceParser::ExternContext* ctx) override;

    std::any visitAutomatic(anceParser::AutomaticContext* ctx) override;
    std::any visitDynamic(anceParser::DynamicContext* ctx) override;

    std::any visitCopyAssignment(anceParser::CopyAssignmentContext* ctx) override;
    std::any visitMoveAssignment(anceParser::MoveAssignmentContext* ctx) override;
    std::any visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext* ctx) override;

    std::any visitBitwiseNot(anceParser::BitwiseNotContext* ctx) override;
    std::any visitNot(anceParser::NotContext* ctx) override;
    std::any visitNegation(anceParser::NegationContext* ctx) override;

    std::any visitAddition(anceParser::AdditionContext* ctx) override;
    std::any visitSubtraction(anceParser::SubtractionContext* ctx) override;
    std::any visitMultiplication(anceParser::MultiplicationContext* ctx) override;
    std::any visitDivision(anceParser::DivisionContext* ctx) override;
    std::any visitRemainder(anceParser::RemainderContext* ctx) override;
    std::any visitLessThan(anceParser::LessThanContext* ctx) override;
    std::any visitLessThanOrEqual(anceParser::LessThanOrEqualContext* ctx) override;
    std::any visitGreaterThan(anceParser::GreaterThanContext* ctx) override;
    std::any visitGreaterThanOrEqual(anceParser::GreaterThanOrEqualContext* ctx) override;
    std::any visitEqual(anceParser::EqualContext* ctx) override;
    std::any visitNotEqual(anceParser::NotEqualContext* ctx) override;
    std::any visitBitwiseAnd(anceParser::BitwiseAndContext* ctx) override;
    std::any visitBitwiseOr(anceParser::BitwiseOrContext* ctx) override;
    std::any visitBitwiseXor(anceParser::BitwiseXorContext* ctx) override;
    std::any visitLeftShift(anceParser::LeftShiftContext* ctx) override;
    std::any visitRightShift(anceParser::RightShiftContext* ctx) override;

  protected:
    lang::Location          location(antlr4::ParserRuleContext* ctx);
    lang::Identifier        ident(antlr4::tree::TerminalNode* i);
    static lang::Identifier createIdentifier(std::string const& text, lang::Location location);

    static uint64_t parseIntegerTypeSize(std::string const& str);
    static uint64_t parseCompoundTypeSize(std::string const& str);

    static uint64_t parseInRange(std::string const& str, uint64_t max);

    lang::Context& context();

  private:
    FileContext* file_context_;
    Unit&        unit_;

  private:
    /**
     * Dirty fix to allow passing value to any that has no non-const copy constructor.
     * @tparam T The type of the value.
     */
    template<Copyable T>
    struct Erased {
        alignas(T) std::array<std::byte, sizeof(T)> mutable data;

        explicit Erased(T value) : data() { new (data.data()) T(value); }
        Erased(Erased const& other) : data() { new (data.data()) T(other.get()); }
        Erased(Erased&& other) noexcept : data() { new (data.data()) T(other.get()); }
        Erased& operator=(Erased const& other)
        {
            get() = other.get();
            return *this;
        }
        Erased& operator=(Erased&& other) noexcept
        {
            get() = other.get();
            return *this;
        }

        T& get() const { return *reinterpret_cast<T*>(data.data()); }

        ~Erased() { std::destroy_at(std::launder(reinterpret_cast<T*>(data.data()))); }
    };

    template<Copyable T>
    static T erasedCast(std::any any)
    {
        Erased<T> value = std::any_cast<Erased<T>>(any);
        return value.get();
    }

    template<Copyable T>
    static Erased<T> erase(T value)
    {
        Erased<T> any(value);
        return any;
    }
};

#endif
