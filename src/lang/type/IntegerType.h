#ifndef ANCE_SRC_LANG_TYPE_INTEGERTYPE_H_
#define ANCE_SRC_LANG_TYPE_INTEGERTYPE_H_

#include "TypeDefinition.h"
#include "VectorizableType.h"

namespace lang
{
    /**
     * An abstract class for all integer types.
     */
    class IntegerType : public virtual lang::TypeDefinition
    {
      public:
        [[nodiscard]] StateCount getStateCount() const override;

        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        const IntegerType* isIntegerType() const override;

      protected:
        /**
         * Get the bit size of the integer type, if a fixed size is defined.
         * @return The size or none.
         */
        virtual std::optional<size_t> getBitSize() const = 0;

        /**
         * Get the size of the integer in bits as it is represented on the machine.
         * @return The native size of the integer.
         */
        virtual size_t getNativeBitSize() const = 0;

        /**
         * Get the minimum bit size of the type. No matter the target, the type will always be at least this big.
         * @return The minimum bit size.
         */
        virtual size_t getMinimumBitSize() const = 0;

        bool                         isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other) override;
        bool                         validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                lang::Location                    location,
                                                                ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                             std::shared_ptr<Value>            value,
                                                             CompileContext&                   context) override;

        bool acceptOverloadRequest(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters) override;
        void buildRequestedOverload(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
                                    lang::PredefinedFunction&                             function,
                                    CompileContext&                                       context) override;
        void buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                    lang::ResolvingHandle<lang::Type> return_type,
                                    lang::PredefinedFunction&         function,
                                    CompileContext&                   context);

        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        llvm::DIType* createDebugType(CompileContext& context) override;
    };
}

#endif
