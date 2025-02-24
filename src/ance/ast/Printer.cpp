#include "Printer.h"

#include "ance/ast/Node.h"

struct ance::ast::Printer::Implementation
{
    class AST final : public Visitor
    {
      public:
        using Visitor::visit;

        explicit AST(std::ostream& out) : out_(out) {}
        ~AST() override = default;

        void indent() const { out_ << std::string(indent_ * 4, ' '); }

        void visit(ErrorStatement const&) override { out_ << "// error"; }

        void visit(Block const& block) override
        {
            out_ << "{" << std::endl;
            indent_++;

            for (auto& statement : block.statements)
            {
                indent();
                visit(*statement);
                out_ << std::endl;
            }

            indent_--;
            indent();
            out_ << "}";
        }

        void visit(Independent const& independent) override
        {
            visit(*independent.expression);
            out_ << ";";
        }

        void visit(ErrorExpression const&) override { out_ << "// error"; }

        void visit(Call const& call) override { out_ << call.identifier << "()"; }

      private:
        std::ostream& out_;

        size_t indent_ = 0;
    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void print(Statement const& statement) const
    {
        utility::Owned<AST> ast = utility::makeOwned<AST>(out_);

        ast->visit(statement);
    }

  private:
    std::ostream& out_;
};

ance::ast::Printer::Printer(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::ast::Printer::~Printer() = default;

void ance::ast::Printer::print(Statement const& statement) const
{
    implementation_->print(statement);
}
