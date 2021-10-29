#ifndef ANCE_SRC_ANCE_STATEMENT_DELETESTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_DELETESTATEMENT_H_

#include "Statement.h"

class Expression;

/**
 * A statement performing a delete operation.
 */
class DeleteStatement : public Statement
{
  public:
    /**
     * Create a new delete statement.
     * @param to_delete An expression producing a value with the pointer to delete.
     * @param delete_buffer Whether to delete a single element or a buffer.
     * @param location The source location.
     */
    DeleteStatement(std::unique_ptr<Expression> to_delete, bool delete_buffer, ance::Location location);

    void setFunction(ance::Function* function) override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression> to_delete_;
    bool                        delete_buffer_;
};

#endif
