#ifndef ANCE_SRC_COMPILER_BUILDER_H_
#define ANCE_SRC_COMPILER_BUILDER_H_

#include "lang/ApplicationVisitor.h"

/**
 * Base class for the building visitor.
 */
class Builder : public lang::ApplicationVisitorConst
{
  public:
    using lang::ApplicationVisitorConst::visit;

    std::any visit(lang::GlobalScope const& global_scope) override;

    std::any visit(lang::FunctionDescription const& function) override;
    std::any visit(lang::VariableDescription const& variable_description) override;
    std::any visit(lang::StructDescription const& struct_description) override;
    std::any visit(lang::AliasDescription const& alias_description) override;

    std::any visit(lang::Member const& member) override;

    std::any visit(lang::Function const& function) override;

    std::any visit(Addressof const& addressof) override;
    std::any visit(Allocation const& allocation) override;
    std::any visit(And const& an_and) override;
    std::any visit(ArrayDefinition const& array_definition) override;
    std::any visit(BinaryOperation const& binary_operation) override;
    std::any visit(BindRef const& bind_ref) override;
    std::any visit(BindRefTo const& bind_ref_to) override;
    std::any visit(Cast const& cast) override;
    std::any visit(LiteralExpression const& constant_literal) override;
    std::any visit(FunctionCall const& function_call) override;
    std::any visit(IfSelect const& if_select) override;
    std::any visit(Indirection const& indirection) override;
    std::any visit(MatchSelect const& match_select) override;
    std::any visit(MemberAccess const& member_access) override;
    std::any visit(Or const& an_or) override;
    std::any visit(Parenthesis const& parenthesis) override;
    std::any visit(SizeofExpression const& sizeof_expression) override;
    std::any visit(SizeofType const& sizeof_type) override;
    std::any visit(Subscript const& subscript) override;
    std::any visit(UnaryOperation const& unary_operation) override;
    std::any visit(VariableAccess const& variable_access) override;
    std::any visit(VectorDefinition const& vector_definition) override;

    std::any visit(lang::CodeBlock const& code_block) override;

    std::any visit(Assertion const& assertion) override;
    std::any visit(Assignment const& assignment_statement) override;
    std::any visit(Break const& break_statement) override;
    std::any visit(Continue const& continue_statement) override;
    std::any visit(Delete const& delete_statement) override;
    std::any visit(Erase const& erase_statement) override;
    std::any visit(ExpressionStatement const& expression_statement) override;
    std::any visit(If const& if_statement) override;
    std::any visit(LocalReferenceVariableDefinition const& local_reference_variable_definition) override;
    std::any visit(LocalVariableDefinition const& local_variable_definition) override;
    std::any visit(Match const& match_statement) override;
    std::any visit(Return const& return_statement) override;
    std::any visit(While const& while_statement) override;
    std::any visit(Loop const& loop_statement) override;

    Shared<lang::Constant> getC(Expression const& expression);
    Shared<lang::Value>    getV(Expression const& expression);

  protected:
    virtual Execution& exec() = 0;

    virtual void visitFunctionDefinition(lang::Function const& function) = 0;

  private:
    enum class GlobalPhase
    {
        INVALID,
        DECLARE,
        DEFINE,
    };
    GlobalPhase g_phase_ = GlobalPhase::INVALID;

    bool assign_ = false;
};

#endif
