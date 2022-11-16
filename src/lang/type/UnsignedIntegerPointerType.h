#ifndef ANCE_SRC_LANG_TYPE_UNSIGNEDINTEGERPOINTERTYPE_H_
#define ANCE_SRC_LANG_TYPE_UNSIGNEDINTEGERPOINTERTYPE_H_

#include "IntegerType.h"

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;
class CompileContext;

namespace lang
{
    /**
     * Represents the unsigned integer pointer type. It is capable of holding any pointer as an integer.
     */
    class UnsignedIntegerPointerType : public IntegerType
    {
      private:
        UnsignedIntegerPointerType();

      public:
        /**
         * The minimum bit size of uiptr value.
         */
        static const size_t MINIMUM_BIT_SIZE = 64;

        bool isUnsignedIntegerPointerType() const override;

        bool acceptOverloadRequest(std::vector<lang::ResolvingHandle<lang::Type>> const& parameters) override;
        void buildRequestedOverload(std::vector<lang::ResolvingHandle<lang::Type>> const& parameters,
                                    lang::PredefinedFunction&                             function,
                                    CompileContext&                                       context) override;
        void buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                    lang::ResolvingHandle<lang::Type> return_type,
                                    lang::PredefinedFunction&         function,
                                    CompileContext&                   context) override;

      private:
        inline static unsigned int size_ = 0;

      protected:
        std::string createMangledName() const override;

        std::optional<size_t> getBitSize() const override;
        size_t                getNativeBitSize() const override;
        bool                  isSigned() const override;
        size_t                getMinimumBitSize() const override;
        std::string           getSuffix() const override;

      public:
        /**
         * Initialize the type.
         * @param llvm_context The llvm context.
         * @param data_layout The data layout of the current build target.
         */
        static void init(llvm::LLVMContext& llvm_context, llvm::DataLayout& data_layout);

        /**
         * Get the bit size of the type.
         * @return The size of the type.
         */
        static unsigned int sizeInBits();

        /**
         * Get the uiptr type instance.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> get();
    };
}

#endif
