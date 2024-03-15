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
      public:
        UnsignedIntegerPointerType();

        /**
         * The minimum bit size of uiptr value.
         */
        static const size_t MINIMUM_BIT_SIZE = 64;

        bool isUnsignedIntegerPointerType() const override;

        bool acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters) override;
        void buildRequestedOverload(std::vector<std::reference_wrapper<lang::Type const>> parameters,
                                    lang::PredefinedFunction&                      function,
                                    CompileContext&                                context) const override;
        void buildRequestedOverload(lang::Type const& parameter_element,
                                    lang::Type const& return_type,
                                    lang::PredefinedFunction&         function,
                                    CompileContext&                   context) const override;

      private:
        inline static unsigned int size_ = 0;

      protected:
        std::string createMangledName() const override;

        Optional<size_t>      getBitSize() const override;
        size_t                getNativeBitSize() const override;
        bool                  isSigned() const override;
        size_t                getMinimumBitSize() const override;
        std::string           getSuffix() const override;

      public:
        /**
         * Initialize the type.
         * @param data_layout The data layout of the current build target.
         */
        static void init(llvm::DataLayout const& data_layout);

        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
