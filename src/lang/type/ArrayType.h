#ifndef ANCE_SRC_LANG_TYPE_ARRAYTYPE_H_
#define ANCE_SRC_LANG_TYPE_ARRAYTYPE_H_

#include "SequenceType.h"

#include <llvm/IR/DerivedTypes.h>

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/utility/TypeRegistry.h"

namespace lang
{
    class Scope;
}

class Application;

namespace lang
{
    /**
     * Represents array types. Array types have an element type and a length.
     */
    class ArrayType : public lang::SequenceType
    {
      public:
        ArrayType(lang::ResolvingHandle<lang::Type> element_type, uint64_t size);

        static const uint64_t MAX_ARRAY_TYPE_SIZE = 1ll << 32;

        ArrayType const* isArrayType() const override;
        ArrayType*       isArrayType() override;

        lang::ResolvingHandle<lang::Type> getActualType() override;
        [[nodiscard]] lang::Type const&   getActualType() const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

      public:
        ~ArrayType() override = default;

      protected:
        std::string   createMangledName() const override;
        Execution::Type         createExecutionType(CompileContext& context) const override;
        Execution::IndexingMode getIndexingMode() const override;

      private:
        Optional<lang::ResolvingHandle<lang::Type>> actual_type_ {};

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
