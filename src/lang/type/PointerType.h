#ifndef ANCE_SRC_LANG_TYPE_POINTERTYPE_H_
#define ANCE_SRC_LANG_TYPE_POINTERTYPE_H_

#include "AddressType.h"
#include "IndirectType.h"
#include "SequenceType.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/utility/TypeRegistry.h"

class Application;

namespace lang
{
    /**
     * Represents a pointer type. A pointer type has an element type, which is the type of the value pointed too.
     */
    class PointerType
        : public lang::SequenceType
        , public lang::IndirectType
        , public lang::AddressType
    {
      public:
        explicit PointerType(lang::ResolvingHandle<lang::Type> element_type);

        StateCount getStateCount() const override;

        bool isPointerType() const override;

        ResolvingHandle<lang::Type> getActualType() override;
        Type const&                 getActualType() const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

      public:
        ~PointerType() override = default;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        std::string             createMangledName() const override;
        void                    registerExecutionType(Execution& exec) const override;
        Execution::IndexingMode getIndexingMode() const override;

      public:
        std::vector<lang::ResolvingHandle<lang::Type>> getDeclarationDependencies() override;
        std::vector<lang::ResolvingHandle<lang::Type>> getDefinitionDependencies() override;

      protected:
        Optional<lang::ResolvingHandle<lang::Type>> getPointeeType() override;
        Type const*                                 getPointeeType() const override;

      private:
        Optional<lang::ResolvingHandle<lang::Type>> actual_type_ {};

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
