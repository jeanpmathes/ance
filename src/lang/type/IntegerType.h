#ifndef ANCE_SRC_LANG_TYPE_INTEGERTYPE_H_
#define ANCE_SRC_LANG_TYPE_INTEGERTYPE_H_

#include "VectorizableType.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/utility/TypeRegistry.h"

class Application;

namespace lang
{
    /**
     * Represents an integer type. Integers can have any precision and can be signed or unsigned.
     */
    class IntegerType : public lang::VectorizableType
    {
      private:
        IntegerType(uint64_t bit_size, bool is_signed);

      public:
        static const int64_t MAX_INTEGER_SIZE = 1ll << 16;

        StateCount getStateCount() const override;

        [[nodiscard]] bool isIntegerType() const override;
        [[nodiscard]] bool isIntegerType(uint64_t bit_size, bool is_signed) const override;
        [[nodiscard]] bool isSigned() const override;

        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        bool                         isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other) override;
        bool                         validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                lang::Location                    location,
                                                                ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                             std::shared_ptr<Value>            value,
                                                             CompileContext&                   context) override;
        std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                             lang::ResolvingHandle<lang::Type> other_element,
                                                             std::shared_ptr<Value>            value,
                                                             CompileContext&                   context) override;

        bool isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other) override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::BinaryOperator              op,
                                                                lang::ResolvingHandle<lang::Type> other) override;
        bool                              validateOperator(lang::BinaryOperator              op,
                                                           lang::ResolvingHandle<lang::Type> other,
                                                           lang::Location                    left_location,
                                                           lang::Location                    right_location,
                                                           ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value>      buildOperator(lang::BinaryOperator   op,
                                                        std::shared_ptr<Value> left,
                                                        std::shared_ptr<Value> right,
                                                        CompileContext&        context) override;
        std::shared_ptr<Value> buildOperator(lang::BinaryOperator              op,
                                             std::shared_ptr<Value>            left,
                                             std::shared_ptr<Value>            right,
                                             lang::ResolvingHandle<lang::Type> return_type,
                                             CompileContext&                   context) override;

        bool acceptOverloadRequest(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters) override;
        void buildRequestedOverload(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
                                    lang::PredefinedFunction&                             function,
                                    CompileContext&                                       context) override;

      private:
        uint64_t bit_size_;
        bool     is_signed_;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) override;

      private:
        static lang::TypeRegistry<std::pair<uint64_t, bool>>& getIntegerTypes();

      public:
        static lang::TypeDefinitionRegistry* getRegistry();

        /**
         * Get an integer type instance.
         * @param bit_size The size of the integer.
         * @param is_signed Whether the integer should be signed.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> get(uint64_t bit_size, bool is_signed);
    };
}

#endif