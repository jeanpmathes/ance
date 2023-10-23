#ifndef ANCE_SRC_COMPILER_CODEPRINTER_H_
#define ANCE_SRC_COMPILER_CODEPRINTER_H_

#include "lang/ApplicationVisitor.h"

namespace util
{
    std::ostream& operator<<(std::ostream& os, std::any const& any);
}

class CodePrinter : public lang::ApplicationVisitorConst
{
  public:
    using lang::ApplicationVisitorConst::visit;

    explicit CodePrinter(std::ostream& out);

    [[nodiscard]] std::any visit(lang::VariableDescription const& variable_description) override;
    [[nodiscard]] std::any visit(lang::FunctionDescription const& function_description) override;
    [[nodiscard]] std::any visit(lang::StructDescription const& struct_description) override;
    [[nodiscard]] std::any visit(lang::AliasDescription const& alias_description) override;

    [[nodiscard]] std::any visit(lang::Member const& member) override;

    [[nodiscard]] std::any visit(Addressof const& addressof) override;
    [[nodiscard]] std::any visit(Allocation const& allocation) override;
    [[nodiscard]] std::any visit(And const& an_and) override;
    [[nodiscard]] std::any visit(ArrayDefinition const& array_definition) override;
    [[nodiscard]] std::any visit(BinaryOperation const& binary_operation) override;
    [[nodiscard]] std::any visit(BindRef const& bind_ref) override;
    [[nodiscard]] std::any visit(BindRefTo const& bind_ref_to) override;
    [[nodiscard]] std::any visit(Cast const& cast) override;
    [[nodiscard]] std::any visit(ConstantLiteral const& constant_literal) override;
    [[nodiscard]] std::any visit(FunctionCall const& function_call) override;
    [[nodiscard]] std::any visit(IfSelect const& if_select) override;
    [[nodiscard]] std::any visit(Indirection const& indirection) override;
    [[nodiscard]] std::any visit(MatchSelect const& match_select) override;
    [[nodiscard]] std::any visit(MemberAccess const& member_access) override;
    [[nodiscard]] std::any visit(Or const& an_or) override;
    [[nodiscard]] std::any visit(Parenthesis const& parenthesis) override;
    [[nodiscard]] std::any visit(SizeofExpression const& sizeof_expression) override;
    [[nodiscard]] std::any visit(SizeofType const& sizeof_type) override;
    [[nodiscard]] std::any visit(Subscript const& subscript) override;
    [[nodiscard]] std::any visit(UnaryOperation const& unary_operation) override;
    [[nodiscard]] std::any visit(VariableAccess const& variable_access) override;
    [[nodiscard]] std::any visit(VectorDefinition const& vector_definition) override;

    [[nodiscard]] std::any visit(lang::CodeBlock const& code_block) override;

    [[nodiscard]] std::any visit(Assertion const& assertion) override;
    [[nodiscard]] std::any visit(Assignment const& assignment_statement) override;
    [[nodiscard]] std::any visit(Break const& break_statement) override;
    [[nodiscard]] std::any visit(Continue const& continue_statement) override;
    [[nodiscard]] std::any visit(Delete const& delete_statement) override;
    [[nodiscard]] std::any visit(Erase const& erase_statement) override;
    [[nodiscard]] std::any visit(ExpressionStatement const& expression_statement) override;
    [[nodiscard]] std::any visit(If const& if_statement) override;
    [[nodiscard]] std::any visit(LocalReferenceVariableDefinition const& local_reference_variable_definition) override;
    [[nodiscard]] std::any visit(LocalVariableDefinition const& local_variable_definition) override;
    [[nodiscard]] std::any visit(Match const& match_statement) override;
    [[nodiscard]] std::any visit(Return const& return_statement) override;
    [[nodiscard]] std::any visit(While const& while_statement) override;
    [[nodiscard]] std::any visit(Loop const& loop_statement) override;

  protected:
    void postVisit(lang::Visitable<ANCE_CONSTRUCTS> const&) override;

  private:
    void indent();

    void consumeWhitespace();
    void emitWhitespace();

    void emitFunction(lang::Function const& function);

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
