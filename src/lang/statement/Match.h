#ifndef ANCE_SRC_LANG_STATEMENT_MATCH_H_
#define ANCE_SRC_LANG_STATEMENT_MATCH_H_

#include "Statement.h"

#include "lang/Element.h"
#include "lang/expression/ConstantExpression.h"

class Expression;

/**
 * A match control-flow statement. It matches an expression against a list of cases.
 */
class Match
    : public Statement
    , public lang::Element<Match, ANCE_CONSTRUCTS>
{
  public:
    class Case
    {
      public:
        /**
         * Create a default case.
         * @param code The code to execute.
         * @return The created case.
         */
        static Case* createDefault(std::unique_ptr<lang::CodeBlock> code);

        /**
         * Create a case.
         * @param conditions The conditions to match.
         * @param code The code to execute.
         * @return The created case.
         */
        static Case* createCase(std::vector<std::unique_ptr<ConstantExpression>> conditions,
                                std::unique_ptr<lang::CodeBlock>                 code);

      private:
        Case(std::vector<std::unique_ptr<ConstantExpression>> conditions, std::unique_ptr<lang::CodeBlock> code);

      public:
        void setContainingScope(lang::Scope* scope);
        void walkDefinitions();

        std::vector<std::pair<ConstantExpression*, lang::CodeBlock*>> getConditions();

      private:
        std::vector<std::unique_ptr<ConstantExpression>> conditions_;
        std::unique_ptr<lang::CodeBlock>                 code_;
    };

  public:
    /**
     * Create a new match statement.
     * @param cases The cases to match against.
     * @param expression The expression to match.
     * @param location The source location of the statement.
     */
    Match(std::vector<std::unique_ptr<Match::Case>> cases,
          std::unique_ptr<Expression>               expression,
          lang::Location                            location);

    [[nodiscard]] Expression& expression();

    std::vector<std::unique_ptr<lang::BasicBlock>> createBlocks(lang::BasicBlock& entry,
                                                                lang::Function*   function) override;

    void setScope(lang::Scope* scope) override;
    void walkDefinitions() override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression>        expression_;
    std::vector<std::unique_ptr<Case>> cases_;
};

#endif
