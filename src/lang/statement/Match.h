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
    static Case* createDefault(Owned<Statement> code);

    /**
         * Create a case.
         * @param conditions The conditions to match.
         * @param code The code to execute.
         * @return The created case.
         */
    static Case* createCase(std::vector<Owned<ConstantExpression>> conditions, Owned<Statement> code);

    /**
     * Create a default case, using an expression.
     * @param expression The expression that provides the value.
     * @return The created case.
     */
    static Case* createDefault(Owned<Expression> expression);

    /**
     * Create a case, using an expression.
     * @param conditions The conditions to match.
     * @param expression The expression that provides a value.
     * @return The created case.
     */
    static Case* createCase(std::vector<Owned<ConstantExpression>> conditions, Owned<Expression> expression);

  private:
    Case(std::vector<Owned<ConstantExpression>> conditions, std::variant<Owned<Statement>, Owned<Expression>> code);

  public:
    [[nodiscard]] std::vector<std::reference_wrapper<ConstantExpression const>>  conditions() const;
    [[nodiscard]] std::reference_wrapper<lang::Visitable<ANCE_CONSTRUCTS> const> code() const;

    void setContainingScope(lang::Scope& scope);
    void walkDefinitions();
    void postResolve();

    std::vector<std::pair<ConstantExpression*, Statement*>> getConditions();

    bool validateConflicts(Case const& other, ValidationLogger& validation_logger) const;
    bool validate(lang::Type const& target_type, ssize_t* coverage_count, ValidationLogger& validation_logger) const;

    /**
     * Validate the return types of the case-expressions.
     * @param location The source location of the match entity.
     * @param cases The cases to validate. Must be expression-based.
     * @param validation_logger The validation logger to use.
     * @return True if the return types are valid, false otherwise.
     */
    static bool validateReturnTypes(lang::Location                  location,
                                    std::vector<Owned<Case>> const& cases,
                                    ValidationLogger&               validation_logger);

    static std::vector<lang::ResolvingHandle<lang::Type>> getCommonType(std::vector<Owned<Case>>& cases);

    /**
     * Expand the contents of this case. This is only valid for statement-based cases.
     * @return The expanded case.
     */
    [[nodiscard]] Owned<Case> expand() const;

    /**
     * Expand the contents of this case. This is only valid for expression-based cases.
     * @param target The variable to assign the result of the expression to.
     * @return The expanded case.
     */
    [[nodiscard]] Owned<Case> expand(lang::ResolvingHandle<lang::Variable> target) const;

  private:
    std::vector<Owned<ConstantExpression>>            conditions_;
    std::variant<Owned<Statement>, Owned<Expression>> code_;
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
    Match(std::vector<Owned<Case>> cases, Owned<Expression> expression, lang::Location location);

    Expression&                                                   expression();
    [[nodiscard]] Expression const&                               expression() const;
    [[nodiscard]] std::vector<std::reference_wrapper<Case const>> cases() const;

    std::vector<Owned<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry, lang::Function& function) override;

    void setScope(lang::Scope& scope) override;
    void walkDefinitions() override;
    void postResolve() override;

    void validate(ValidationLogger& validation_logger) const override;

    /**
     * Validate the type matched by this match.
     * @param expression The expression providing the value to match.
     * @param validation_logger The validation logger to use.
     * @return True if the type can be matched, false otherwise.
     */
    static bool validateType(Expression const& expression, ValidationLogger& validation_logger);

    /**
     * Validate the cases of the match statement.
     * @param location The location of the match.
     * @param expression The expression providing the value to match.
     * @param cases The cases to validate.
     * @param validation_logger The validation logger to use.
     * @return True if the cases are valid, false otherwise.
     */
    static bool validateCases(lang::Location                  location,
                              Expression const&               expression,
                              std::vector<Owned<Case>> const& cases,
                              ValidationLogger&               validation_logger);

    [[nodiscard]] Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  protected:
    void doBuild(CompileContext& context) override;

  private:
    Owned<Expression>        expression_;
    std::vector<Owned<Case>> cases_;
};

#endif
