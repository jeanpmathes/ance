#ifndef ANCE_SRC_LANG_TYPE_VECTORTYPE_H_
#define ANCE_SRC_LANG_TYPE_VECTORTYPE_H_

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
     * Represents a vector type.
     */
    class VectorType : public lang::SequenceType
    {
      private:
        VectorType(lang::ResolvingHandle<lang::Type> element_type, uint64_t size);

      public:
        static const uint64_t MAX_VECTOR_TYPE_SIZE = 1ll << 32;

        VectorType const* isVectorType() const override;
        VectorType*       isVectorType() override;

        bool isSigned() const override;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> getActualType() const override;

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

        bool                              isOperatorDefined(lang::UnaryOperator op) override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::UnaryOperator op) override;
        bool                              validateOperator(lang::UnaryOperator op,
                                                           lang::Location      location,
                                                           ValidationLogger&   validation_logger) const override;
        std::shared_ptr<lang::Value>      buildOperator(lang::UnaryOperator    op,
                                                        std::shared_ptr<Value> value,
                                                        CompileContext&        context) override;

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

        bool acceptOverloadRequest(std::vector<lang::ResolvingHandle<lang::Type>> const& parameters) override;
        void buildRequestedOverload(std::vector<lang::ResolvingHandle<lang::Type>> const& parameters,
                                    lang::PredefinedFunction&                             function,
                                    CompileContext&                                       context) override;

      public:
        ~VectorType() override = default;

        /**
         * Create a value of this type.
         * @param values The elements of the vector.
         * @param context The compile context.
         * @return The value.
         */
        std::shared_ptr<lang::Value> createValue(std::vector<std::shared_ptr<lang::Value>> values,
                                                 CompileContext&                           context);

      protected:
        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) override;

      private:
        static lang::TypeRegistry<uint64_t>& getVectorTypes();

      public:
        static lang::TypeDefinitionRegistry* getRegistry();

        /**
         * Get an vector type instance.
         * @param element_type The element type of the vector.
         * @param size The size of the vector. Must be greater than zero.
         * @return The vector type instance.
         */
        static lang::ResolvingHandle<lang::Type> get(lang::ResolvingHandle<lang::Type> element_type, uint64_t size);
    };
}

#endif
