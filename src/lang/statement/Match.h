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

    /**
     * Create a default case, using an expression.
     * @param expression The expression that provides the value.
     * @return The created case.
     */
    static Case* createDefault(std::unique_ptr<Expression> expression);

    /**
     * Create a case, using an expression.
     * @param conditions The conditions to match.
     * @param expression The expression that provides a value.
     * @return The created case.
     */
    static Case* createCase(std::vector<std::unique_ptr<ConstantExpression>> conditions,
                            std::unique_ptr<Expression>                      expression);

  private:
    Case(std::vector<std::unique_ptr<ConstantExpression>>                      conditions,
         std::variant<std::unique_ptr<Statement>, std::unique_ptr<Expression>> code);

  public:
    void setContainingScope(lang::Scope* scope);
    void walkDefinitions();

    std::vector<std::pair<ConstantExpression*, Statement*>> getConditions();

    bool validateConflicts(Case& other, ValidationLogger& validation_logger);
    bool validate(lang::ResolvingHandle<lang::Type> target_type, ValidationLogger& validation_logger);

    /**
     * Get the common type of the cases. The cases must be expression-based.
     * @param cases The cases to get the common type from.
     * @return The common type.
     */
    static lang::ResolvingHandle<lang::Type> getCommonType(const std::vector<std::unique_ptr<Case>>& cases);

    /**
     * Validate the return types of the case-expressions.
     * @param location The source location of the match entity.
     * @param cases The cases to validate. Must be expression-based.
     * @param validation_logger The validation logger to use.
     * @return True if the return types are valid, false otherwise.
     */
    static bool validateReturnTypes(lang::Location                            location,
                                    const std::vector<std::unique_ptr<Case>>& cases,
                                    ValidationLogger&                         validation_logger);

    /**
     * Expand the contents of this case. This is only valid for statement-based cases.
     * @return The expanded case.
     */
    [[nodiscard]] std::unique_ptr<Case> expand() const;

    /**
     * Expand the contents of this case. This is only valid for expression-based cases.
     * @param target The variable to assign the result of the expression to.
     * @return The expanded case.
     */
    [[nodiscard]] std::unique_ptr<Case> expand(lang::ResolvingHandle<lang::Variable> target) const;

    ssize_t getCoverageCount();

  private:
    std::vector<std::unique_ptr<ConstantExpression>>                      conditions_;
    std::variant<std::unique_ptr<Statement>, std::unique_ptr<Expression>> code_;
    ssize_t                                                               coverage_count_ {};
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

    /**
     * Validate the type matched by this match.
     * @param expression The expression providing the value to match.
     * @param validation_logger The validation logger to use.
     * @return True if the type can be matched, false otherwise.
     */
    static bool validateType(Expression& expression, ValidationLogger& validation_logger);

    /**
     * Validate the cases of the match statement.
     * @param location The location of the match.
     * @param expression The expression providing the value to match.
     * @param cases The cases to validate.
     * @param validation_logger The validation logger to use.
     * @return True if the cases are valid, false otherwise.
     */
    static bool validateCases(lang::Location                            location,
                              Expression&                               expression,
                              const std::vector<std::unique_ptr<Case>>& cases,
                              ValidationLogger&                         validation_logger);

    [[nodiscard]] Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression>        expression_;
    std::vector<std::unique_ptr<Case>> cases_;
};

#endif
