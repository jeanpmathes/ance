#ifndef ANCE_SRC_ANCE_TYPE_INTEGERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_INTEGERTYPE_H_

#include "TypeDefinition.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"
#include "ance/utility/TypeRegistry.h"

class Application;

namespace ance
{
    /**
     * Represents an integer type. Integers can have any precision and can be signed or unsigned.
     */
    class IntegerType : public ance::TypeDefinition
    {
      private:
        IntegerType(uint64_t bit_size, bool is_signed);

      public:
        static const int64_t MAX_INTEGER_SIZE = 1ll << 16;

        [[nodiscard]] bool isIntegerType() const override;
        [[nodiscard]] bool isIntegerType(uint64_t bit_size, bool is_signed) const override;

        [[nodiscard]] bool isBooleanType() const override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        bool isOperatorDefined(BinaryOperator op, ance::ResolvingHandle<ance::Type> other) override;
        ance::ResolvingHandle<ance::Type> getOperatorResultType(BinaryOperator                    op,
                                                                ance::ResolvingHandle<ance::Type> other) override;
        bool                              validateOperator(BinaryOperator                    op,
                                                           ance::ResolvingHandle<ance::Type> other,
                                                           ance::Location                    left_location,
                                                           ance::Location                    right_location,
                                                           ValidationLogger&                 validation_logger) override;
        std::shared_ptr<ance::Value>      buildOperator(BinaryOperator         op,
                                                        std::shared_ptr<Value> left,
                                                        std::shared_ptr<Value> right,
                                                        CompileContext*        context) override;

      private:
        uint64_t    bit_size_;
        bool        is_signed_;
        llvm::Type* type_ {nullptr};

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static ance::TypeRegistry<std::pair<uint64_t, bool>>& getIntegerTypes();

      public:
        static ance::TypeDefinitionRegistry* getRegistry();

        /**
         * Get an integer type instance.
         * @param bit_size The size of the integer.
         * @param is_signed Whether the integer should be signed.
         * @return The instance.
         */
        static ance::ResolvingHandle<ance::Type> get(uint64_t bit_size, bool is_signed);

        /**
         * Get the boolean type. This is an integer type with size 1.
         * @return The boolean type.
         */
        static ance::ResolvingHandle<ance::Type> getBooleanType();
    };
}

#endif