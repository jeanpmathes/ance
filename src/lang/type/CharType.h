#ifndef ANCE_SRC_LANG_TYPE_CHARTYPE_H_
#define ANCE_SRC_LANG_TYPE_CHARTYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * The char type. Stores unicode code points.
     */
    class CharType : public lang::TypeDefinition
    {
      public:
        static constexpr size_t SIZE_IN_BITS = 32;

        CharType();
        ~CharType() override = default;

        [[nodiscard]] StateCount getStateCount() const override;
        bool                     isCharType() const override;

        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) override;

      public:
        /**
         * Get the char type.
         * @return The char type.
         */
        static lang::ResolvingHandle<lang::Type> get();
    };
}

#endif
