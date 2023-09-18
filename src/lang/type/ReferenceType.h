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
      public:
        explicit ReferenceType(lang::ResolvingHandle<lang::Type> element_type);

        [[nodiscard]] StateCount getStateCount() const override;

        [[nodiscard]] bool isReferenceType() const override;

        lang::ResolvingHandle<lang::Type> getElementType() override;
        lang::Type const&                 getElementType() const override;

        lang::ResolvingHandle<lang::Type> getActualType() override;
        lang::Type const&                 getActualType() const override;

        llvm::Constant*    getDefaultContent(llvm::Module& m) const override;
        llvm::PointerType* getContentType(llvm::LLVMContext& c) const override;

        bool isSubscriptDefined() const override;

        lang::ResolvingHandle<lang::Type> getSubscriptReturnType() override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        bool                validateSubscript(lang::Location    indexed_location,
                                              lang::Type const& index_type,
                                              lang::Location    index_location,
                                              ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildSubscript(Shared<Value>   indexed,
                                           Shared<Value>   index,
                                           CompileContext& context) override;

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

        bool                              isOperatorDefined(lang::UnaryOperator op) const override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::UnaryOperator op) override;
        bool                              validateOperator(lang::UnaryOperator op,
                                                           lang::Location      location,
                                                           ValidationLogger&   validation_logger) const override;
        Shared<lang::Value>               buildOperator(lang::UnaryOperator op,
                                                        Shared<Value>       value,
                                                        CompileContext&     context) override;

        bool                              hasMember(lang::Identifier const& name) const override;
        lang::ResolvingHandle<lang::Type> getMemberType(lang::Identifier const& name) override;
        bool validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildMemberAccess(Shared<Value>           value,
                                              lang::Identifier const& name,
                                              CompileContext&         context) override;

        bool                              definesIndirection() const override;
        lang::ResolvingHandle<lang::Type> getIndirectionType() override;
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildIndirection(Shared<Value> value, CompileContext& context) override;

        void buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext& context) override;
        void buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext& context) override;
        void buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext& context) override;

        void createConstructors() override;
        void buildNativeDeclaration(CompileContext& context) override;
        void buildNativeDefinition(CompileContext& context) override;

        std::vector<lang::ResolvingHandle<lang::Type>> getDeclarationDependencies() override;
        std::vector<lang::ResolvingHandle<lang::Type>> getDefinitionDependencies() override;

        ~ReferenceType() override = default;

      private:
        lang::ResolvingHandle<lang::Type>           element_type_;
        Optional<lang::ResolvingHandle<lang::Type>> actual_type_ {};

      protected:
        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) const override;

      public:
        /**
         * Get the referenced backing value.
         * @param value A native value for a reference-type variable.
         * @param context The current compile context.
         * @return A native value for the referenced value.
         */
        llvm::Value* getReferenced(llvm::Value* value, CompileContext& context) const;

        /**
         * Get the referenced value.
         * @param value A value of reference type.
         * @param context The current compile context.
         * @return The referenced value.
         */
        Shared<lang::Value> getReferenced(Shared<lang::Value> value, CompileContext& context);

        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
