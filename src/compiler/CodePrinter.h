#ifndef ANCE_SRC_COMPILER_CODEPRINTER_H_
#define ANCE_SRC_COMPILER_CODEPRINTER_H_

#include "lang/ApplicationVisitor.h"

namespace util
{
    std::ostream& operator<<(std::ostream& os, std::any const& any);
}

class CodePrinter : public lang::ApplicationVisitor
{
  public:
    using lang::ApplicationVisitor::visit;

    explicit CodePrinter(std::ostream& out);

    std::any visit(lang::GlobalVariable& variable) override;

    std::any visit(lang::CustomFunction& function) override;
    std::any visit(lang::ExternFunction& function) override;

    std::any visit(Addressof& addressof) override;
    std::any visit(Allocation& allocation) override;
    std::any visit(And& an_and) override;
    std::any visit(ArrayDefinition& array_definition) override;
    std::any visit(BinaryOperation& binary_operation) override;
    std::any visit(BindRef& bind_ref) override;
    std::any visit(BindRefTo& bind_ref_to) override;
    std::any visit(ConstantLiteral& constant_literal) override;
    std::any visit(FunctionCall& function_call) override;
    std::any visit(IfSelect& if_select) override;
    std::any visit(Indirection& indirection) override;
    std::any visit(MatchSelect& match_select) override;
    std::any visit(MemberAccess& member_access) override;
    std::any visit(Or& an_or) override;
    std::any visit(Parenthesis& parenthesis) override;
    std::any visit(SizeofExpression& sizeof_expression) override;
    std::any visit(SizeofType& sizeof_type) override;
    std::any visit(Subscript& subscript) override;
    std::any visit(UnaryOperation& unary_operation) override;
    std::any visit(VariableAccess& variable_access) override;
    std::any visit(VectorDefinition& vector_definition) override;

    std::any visit(lang::CodeBlock& code_block) override;

    std::any visit(Assertion& assertion) override;
    std::any visit(Assignment& assignment_statement) override;
    std::any visit(Break& break_statement) override;
    std::any visit(Continue& continue_statement) override;
    std::any visit(Delete& delete_statement) override;
    std::any visit(Drop& drop_statement) override;
    std::any visit(ExpressionStatement& expression_statement) override;
    std::any visit(If& if_statement) override;
    std::any visit(LocalReferenceVariableDefinition& local_reference_variable_definition) override;
    std::any visit(LocalVariableDefinition& local_variable_definition) override;
    std::any visit(Match& match_statement) override;
    std::any visit(Return& return_statement) override;
    std::any visit(While& while_statement) override;

  protected:
    void postVisit(lang::Visitable<ANCE_CONSTRUCTS>&) override;

  private:
    void indent();

    void consumeWhitespace();
    void emitWhitespace();

    enum ConsumeWhitespace
    {
        CONSUME_WS_DISABLED,
        CONSUME_WS_ACTIVE,
        CONSUME_WS_ENABLED
    };

    ConsumeWhitespace consume_whitespace_ = CONSUME_WS_DISABLED;

    std::ostream& out_;
    size_t        indent_ = 0;
};

#endif
