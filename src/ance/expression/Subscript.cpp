#include "Subscript.h"

#include "ance/ApplicationVisitor.h"
#include "ance/type/Type.h"
#include "validation/ValidationLogger.h"

Subscript::Subscript(Expression* indexed, Expression* index, ance::Location location)
    : Expression(location)
    , indexed_(indexed)
    , index_(index)
{
    addChild(*index);
    addChild(*indexed);
}

void Subscript::setScope(ance::Scope* scope)
{
    indexed_->setContainingScope(scope);
    index_->setContainingScope(scope);
}

ance::Type* Subscript::type()
{
    return indexed_->type()->getIndexerReturnType();
}

bool Subscript::validate(ValidationLogger& validation_logger)
{
    indexed_->validate(validation_logger);
    index_->validate(validation_logger);

    ance::Type* indexed_type = indexed_->type();

    if (indexed_type->isIndexerDefined())
    {
        return indexed_type->validateGetIndexer(indexed_->getValue(),
                                                indexed_->location(),
                                                index_->getValue(),
                                                index_->location(),
                                                validation_logger);
    }
    else
    {
        validation_logger.logError("Type '" + indexed_type->getName() + "' does not provide get indexer", location());

        return false;
    }
}

void Subscript::doBuild(CompileContext* context)
{
    ance::Value* return_value = indexed_->type()->buildGetIndexer(indexed_->getValue(), index_->getValue(), context);
    setValue(return_value);
}

bool Subscript::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitSubscript(*this);
}

Subscript::~Subscript() = default;
