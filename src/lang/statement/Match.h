#ifndef ANCE_SRC_LANG_STATEMENT_MATCH_H_
#define ANCE_SRC_LANG_STATEMENT_MATCH_H_

#include "Statement.h"

#include "lang/Element.h"
#include "lang/expression/ConstantExpression.h"

class Expression;

class Case : public lang::Element<Case, ANCE_CONSTRUCTS>
{
  public:
    /**
         * Create a default case.
         * @param code The code to execute.
         * @return The created case.
         */
    static Case* createDefault(std::unique_ptr<Statement> code);

    /**
         * Create a case.
         * @param conditions The conditions to match.
         * @param code The code to execute.
         * @return The created case.
         */
    static Case* createCase(std::vector<std::unique_ptr<ConstantExpression>> conditions,
                            std::unique_ptr<Statement>                       code);

  private:
    Case(std::vector<std::unique_ptr<ConstantExpression>> conditions, std::unique_ptr<Statement> code);

  public:
    void setContainingScope(lang::Scope* scope);
    void walkDefinitions();

    std::vector<std::pair<ConstantExpression*, Statement*>> getConditions();

    bool validateConflicts(Case* other, ValidationLogger& validation_logger);
    bool validate(lang::ResolvingHandle<lang::Type> target_type, ValidationLogger& validation_logger);

    std::unique_ptr<Case> expand() const;

    ssize_t getCoverageCount();

  private:
    std::vector<std::unique_ptr<ConstantExpression>> conditions_;
    std::unique_ptr<Statement>                       code_;
    ssize_t                                          coverage_count_ {};
};

/**
 * A match control-flow statement. It matches an expression against a list of cases.
 */
class Match
    : public Statement
    , public lang::Element<Match, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new match statement.
     * @param cases The cases to match against.
     * @param expression The expression to match.
     * @param location The source location of the statement.
     */
    Match(std::vector<std::unique_ptr<Case>> cases, std::unique_ptr<Expression> expression, lang::Location location);

    [[nodiscard]] Expression& expression();

    std::vector<std::unique_ptr<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry,
                                                                     lang::Function*   function) override;

    void setScope(lang::Scope* scope) override;
    void walkDefinitions() override;

    void validate(ValidationLogger& validation_logger) override;

    Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  private:
    /**
     * Validate the cases of the match statement.
     * @param validation_logger The validation logger to use.
     * @return True if the cases are valid, false otherwise.
     */
    bool validateCases(ValidationLogger& validation_logger);

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression>        expression_;
    std::vector<std::unique_ptr<Case>> cases_;
};

#endif
