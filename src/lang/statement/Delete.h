#ifndef ANCE_SRC_LANG_STATEMENT_DELETE_H_
#define ANCE_SRC_LANG_STATEMENT_DELETE_H_

#include "Statement.h"

#include "lang/Element.h"

class Expression;

/**
 * A statement performing a delete operation.
 */
class Delete
    : public Statement
    , public lang::Element<Delete, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new delete statement.
     * @param to_delete An expression producing a value with the pointer to delete.
     * @param delete_buffer Whether to delete a single element or a buffer.
     * @param location The source location.
     */
    Delete(std::unique_ptr<Expression> to_delete, bool delete_buffer, lang::Location location);

    [[nodiscard]] Expression& toDelete() const;
    [[nodiscard]] bool        isBufferDelete() const;

    void setScope(lang::Scope* scope) override;
    void walkDefinitions() override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression> to_delete_;
    bool                        delete_buffer_;
};

#endif
