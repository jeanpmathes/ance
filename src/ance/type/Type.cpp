#include "Type.h"

#include "ance/construct/value/Value.h"
#include "ance/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

llvm::Type* ance::Type::getNativeType(llvm::LLVMContext& c)
{
    return llvm::PointerType::get(getContentType(c), 0);
}

llvm::DIType* ance::Type::getDebugType(CompileContext* context)
{
    if (!debug_type_) { debug_type_ = createDebugType(context); }

    return debug_type_;
}

llvm::TypeSize ance::Type::getNativeSize(llvm::Module* m)
{
    return m->getDataLayout().getTypeAllocSize(getNativeType(m->getContext()));
}

llvm::TypeSize ance::Type::getContentSize(llvm::Module* m)
{
    return m->getDataLayout().getTypeAllocSize(getContentType(m->getContext()));
}

bool ance::Type::isIndexerDefined(Indexer)
{
    return false;
}

ance::Type* ance::Type::getIndexerReturnType()
{
    return nullptr;
}

bool ance::Type::validateGetIndexer(ance::Value*, ance::Location, ance::Value*, ance::Location, ValidationLogger&)
{
    return false;
}
void ance::Type::validateSetIndexer(ance::Value*,
                                    ance::Location,
                                    ance::Value*,
                                    ance::Location,
                                    ance::Value*,
                                    ance::Location,
                                    ValidationLogger&)
{}

ance::Value* ance::Type::buildGetIndexer(ance::Value*, ance::Value*, CompileContext*)
{
    return nullptr;
}

void ance::Type::buildSetIndexer(ance::Value*, ance::Value*, ance::Value*, CompileContext*) {}

bool ance::Type::checkMismatch(ance::Type*       expected,
                               ance::Type*       actual,
                               ance::Location    location,
                               ValidationLogger& validation_logger)
{
    if (expected != actual)
    {
        if (ance::ReferenceType::getReferencedType(actual) == expected) return true;

        validation_logger.logError("Cannot implicitly convert '" + actual->getName() + "' to '" + expected->getName()
                                       + "'",
                                   location);

        return false;
    }

    return true;
}

ance::Value* ance::Type::makeMatching(ance::Type* expected, ance::Value* value, CompileContext* context)
{
    if (value->type() == expected) return value;

    if (ance::ReferenceType::getReferencedType(value->type()) == expected)
    {
        auto reference_type = dynamic_cast<ance::ReferenceType*>(value->type());
        return reference_type->getReferenced(value, context);
    }

    assert(false && "Cannot make the value matching, was isMismatch checked before?");
    return nullptr;
}
