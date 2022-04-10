#ifndef ANCE_SRC_COMPILER_CODEPRINTER_H_
#define ANCE_SRC_COMPILER_CODEPRINTER_H_

#include "lang/ApplicationVisitor.h"

namespace util
{
    std::ostream& operator<<(std::ostream& os, const std::any& any);
}

class CodePrinter : public lang::ApplicationVisitor
{
  public:
    using lang::ApplicationVisitor::visit;

    explicit CodePrinter(std::ostream& out);

    std::any visit(Addressof& addressof) override;
    std::any visit(Allocation& allocation) override;
    std::any visit(BinaryOperation& binary_operation) override;
    std::any visit(BindRef& bind_ref) override;
    std::any visit(ConstantLiteral& constant_literal) override;
    std::any visit(DefaultValue& default_value) override;
    std::any visit(FunctionCall& function_call) override;
    std::any visit(Parenthesis& parenthesis) override;
    std::any visit(SizeofExpression& sizeof_expression) override;
    std::any visit(SizeofType& sizeof_type) override;
    std::any visit(Subscript& subscript) override;
    std::any visit(VariableAccess& variable_access) override;

    std::any visit(Assertion& assertion) override;
    std::any visit(Assignment& assignment_statement) override;
    std::any visit(Delete& delete_statement) override;
    std::any visit(ExpressionStatement& expression_statement) override;
    std::any visit(LocalReferenceVariableDefinition& local_reference_variable_definition) override;
    std::any visit(LocalVariableDefinition& local_variable_definition) override;
    std::any visit(Return& return_statement) override;

  private:
    std::ostream& out_;
};

#endif
