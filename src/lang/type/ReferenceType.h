#ifndef ANCE_SRC_LANG_TYPE_REFERENCETYPE_H_
#define ANCE_SRC_LANG_TYPE_REFERENCETYPE_H_

#include "TypeDefinition.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/utility/TypeRegistry.h"

class Application;

namespace lang
{
    /**
     * A reference refers to another stored value.
     */
    class ReferenceType : public lang::TypeDefinition
    {
      private:
        explicit ReferenceType(lang::ResolvingHandle<lang::Type> element_type);

      public:
        [[nodiscard]] StateCount getStateCount() const override;

        [[nodiscard]] bool                              isReferenceType() const override;
        [[nodiscard]] lang::ResolvingHandle<lang::Type> getElementType() const override;
        [[nodiscard]] lang::ResolvingHandle<lang::Type> getActualType() const override;

        llvm::Constant*    getDefaultContent(llvm::Module& m) override;
        llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

        bool isSubscriptDefined() override;

        lang::ResolvingHandle<lang::Type> getSubscriptReturnType() override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        bool                         validateSubscript(lang::Location                    indexed_location,
                                                       lang::ResolvingHandle<lang::Type> index_type,
                                                       lang::Location                    index_location,
                                                       ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

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
                                                        CompileContext*        context) override;

        bool                              isOperatorDefined(lang::UnaryOperator op) override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::UnaryOperator op) override;
        bool                              validateOperator(lang::UnaryOperator op,
                                                           lang::Location      location,
                                                           ValidationLogger&   validation_logger) const override;
        std::shared_ptr<lang::Value>      buildOperator(lang::UnaryOperator    op,
                                                        std::shared_ptr<Value> value,
                                                        CompileContext*        context) override;

        bool                              hasMember(const lang::Identifier& name) override;
        lang::ResolvingHandle<lang::Type> getMemberType(const lang::Identifier& name) override;
        bool validateMemberAccess(const lang::Identifier& name, ValidationLogger& validation_logger) const override;
        std::shared_ptr<lang::Value> buildMemberAccess(std::shared_ptr<Value>  value,
                                                       const lang::Identifier& name,
                                                       CompileContext*         context) override;

        bool                              definesIndirection() override;
        lang::ResolvingHandle<lang::Type> getIndirectionType() override;
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const override;
        std::shared_ptr<lang::Value> buildIndirection(std::shared_ptr<Value> value, CompileContext* context) override;

        void buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext* context) override;
        void buildNativeDeclaration(CompileContext* context) override;
        void buildNativeDefinition(CompileContext* context) override;

        ~ReferenceType() override = default;

      private:
        lang::ResolvingHandle<lang::Type> element_type_;

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static lang::TypeRegistry<>& getReferenceTypes();

      public:
        static lang::TypeDefinitionRegistry* getRegistry();

        /**
         * Get the referenced backing value.
         * @param value A native value for a reference-type variable.
         * @param context The current compile context.
         * @return A native value for the referenced value.
         */
        llvm::Value* getReferenced(llvm::Value* value, CompileContext* context);

        /**
         * Get the referenced value.
         * @param value A value of reference type.
         * @param context The current compile context.
         * @return The referenced value.
         */
        std::shared_ptr<lang::Value> getReferenced(const std::shared_ptr<lang::Value>& value, CompileContext* context);

        /**
         * Get a reference type instance.
         * @param element_type The element type.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> get(lang::ResolvingHandle<lang::Type> element_type);
    };
}

#endif
