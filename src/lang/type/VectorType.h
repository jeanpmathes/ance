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

        lang::ResolvingHandle<lang::Type> getActualType() override;
        [[nodiscard]] lang::Type const&   getActualType() const override;

        llvm::Constant* getDefaultContent(llvm::Module& m) const override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        bool                isImplicitlyConvertibleTo(lang::Type const& other) const override;
        bool                validateImplicitConversion(lang::Type const& other,
                                                       lang::Location    location,
                                                       ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                    Shared<Value>                     value,
                                                    CompileContext&                   context) override;

        bool                              isOperatorDefined(lang::UnaryOperator op) const override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::UnaryOperator op) override;
        bool                              validateOperator(lang::UnaryOperator op,
                                                           lang::Location      location,
                                                           ValidationLogger&   validation_logger) const override;
        Shared<lang::Value>               buildOperator(lang::UnaryOperator op,
                                                        Shared<Value>       value,
                                                        CompileContext&     context) override;

        bool isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::BinaryOperator              op,
                                                                lang::ResolvingHandle<lang::Type> other) override;
        bool                              validateOperator(lang::BinaryOperator op,
                                                           lang::Type const&    other,
                                                           lang::Location       left_location,
                                                           lang::Location       right_location,
                                                           ValidationLogger&    validation_logger) const override;
        Shared<lang::Value>               buildOperator(lang::BinaryOperator op,
                                                        Shared<Value>        left,
                                                        Shared<Value>        right,
                                                        CompileContext&      context) override;

        bool acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters) override;
        void buildRequestedOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters,
                                    lang::PredefinedFunction&                      function,
                                    CompileContext&                                context) override;

      public:
        ~VectorType() override = default;

      protected:
        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) const override;

      private:
        static lang::TypeRegistry<uint64_t>& getVectorTypes();

        Optional<lang::ResolvingHandle<lang::Type>> actual_type_ {};

      public:
        static lang::TypeDefinitionRegistry* getRegistry();

        /**
         * Get an vector type instance.
         * @param element_type The element type of the vector.
         * @param size The size of the vector. Must be greater than zero.
         * @return The vector type instance.
         */
        static lang::ResolvingHandle<lang::Type> get(lang::ResolvingHandle<lang::Type> element_type, uint64_t size);

        ResolvingHandle<lang::Type> clone() const override;
    };
}

#endif
