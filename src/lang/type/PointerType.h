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
      private:
        explicit PointerType(lang::ResolvingHandle<lang::Type> element_type);

      public:
        StateCount getStateCount() const override;

        bool                              isPointerType() const override;
        lang::ResolvingHandle<lang::Type> getActualType() const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

      protected:
        llvm::Type*  getIndexedType(CompileContext& context) const override;
        llvm::Value* getIndexingPointer(std::shared_ptr<Value> indexed, CompileContext& context) override;
        llvm::SmallVector<llvm::Value*> getNativeIndices(llvm::Value* zero, llvm::Value* index) override;

      public:
        ~PointerType() override = default;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        std::string                        createMangledName() const override;
        llvm::DIType*                      createDebugType(CompileContext& context) override;
        std::vector<lang::TypeDefinition*> getDependencies() const override;

        std::optional<lang::ResolvingHandle<lang::Type>> getPointeeType() const override;

      private:
        static lang::TypeRegistry<>& getPointerTypes();

      public:
        static lang::TypeDefinitionRegistry* getRegistry();

        /**
         * Get a pointer type instance.
         * @param element_type The element type.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> get(lang::ResolvingHandle<lang::Type> element_type);
    };
}

#endif

