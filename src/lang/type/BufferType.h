#ifndef ANCE_SRC_LANG_TYPE_BUFFERTYPE_H_
#define ANCE_SRC_LANG_TYPE_BUFFERTYPE_H_

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
     * Represents a buffer type. It points to a sequence of values.
     */
    class BufferType
        : public lang::SequenceType
        , public lang::IndirectType
        , public lang::AddressType
    {
      public:
        explicit BufferType(lang::ResolvingHandle<lang::Type> element_type);

        StateCount getStateCount() const override;

        bool isBufferType() const override;

        ResolvingHandle<lang::Type> getActualType() override;
        [[nodiscard]] Type const&   getActualType() const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

      public:
        ~BufferType() override = default;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        std::string   createMangledName() const override;
        void                    registerExecutionType(CompileContext& context) const override;
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
