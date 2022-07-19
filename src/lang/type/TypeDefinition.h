#ifndef ANCE_SRC_LANG_TYPE_TYPEDEFINITION_H_
#define ANCE_SRC_LANG_TYPE_TYPEDEFINITION_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "lang/BinaryOperator.h"
#include "lang/UnaryOperator.h"
#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/type/StateCount.h"
#include "lang/utility/Identifier.h"
#include "lang/AccessModifier.h"

namespace lang
{
    class Scope;
    class Value;
    class Type;
}

class CompileContext;
class ValidationLogger;

namespace lang
{
    /**
     * Represents the definition of a type.
     */
    class TypeDefinition
    {
      protected:
        /**
         * Create a type definition.
         * @param name The name of the defined type.
         * @param location The location of the defined type. Use a non-global location for custom types.
         */
        explicit TypeDefinition(lang::Identifier name, lang::Location location = lang::Location(0, 0, 0, 0));

      public:
        virtual ~TypeDefinition() = default;

        void setType(lang::Type* type);

        [[nodiscard]] const Identifier&  name() const;
        const std::string&               getMangledName();
        [[nodiscard]] lang::Location     getDefinitionLocation() const;
        [[nodiscard]] bool               isCustom() const;

        [[nodiscard]] virtual StateCount getStateCount() const = 0;

        [[nodiscard]] virtual bool isIntegerType() const;
        [[nodiscard]] virtual bool isIntegerType(uint64_t bit_size, bool is_signed) const;
        [[nodiscard]] virtual bool isBooleanType() const;
        [[nodiscard]] virtual bool isFloatingPointType() const;
        [[nodiscard]] virtual bool isFloatingPointType(size_t precision) const;
        [[nodiscard]] virtual bool isSizeType() const;
        [[nodiscard]] virtual bool isDiffType() const;
        [[nodiscard]] virtual bool isVoidType() const;
        [[nodiscard]] virtual bool isPointerType() const;
        [[nodiscard]] virtual bool isReferenceType() const;

        [[nodiscard]] virtual lang::ResolvingHandle<lang::Type> getElementType() const;

        [[nodiscard]] virtual lang::ResolvingHandle<lang::Type> getActualType() const;
        [[nodiscard]] virtual lang::ResolvingHandle<lang::Type> getOriginalType() const;

        [[nodiscard]] virtual lang::AccessModifier getAccessModifier() const;

        void         setContainingScope(Scope* scope);
        virtual void onScope();
        Scope*       scope();

        virtual llvm::Constant* getDefaultContent(llvm::Module& m) = 0;

        llvm::Type*         getNativeType(llvm::LLVMContext& c);
        virtual llvm::Type* getContentType(llvm::LLVMContext& c) = 0;
        llvm::DIType*       getDebugType(CompileContext* context);

        llvm::TypeSize getNativeSize(llvm::Module* m);
        llvm::TypeSize getContentSize(llvm::Module* m);

        virtual bool                              isSubscriptDefined();
        virtual lang::ResolvingHandle<lang::Type> getSubscriptReturnType();
        virtual bool isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other);
        virtual bool isOperatorDefined(lang::UnaryOperator op);
        virtual lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::BinaryOperator              op,
                                                                        lang::ResolvingHandle<lang::Type> other);
        virtual lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::UnaryOperator op);
        virtual bool                              isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other);
        virtual bool                              hasMember(const lang::Identifier& name);
        virtual lang::ResolvingHandle<lang::Type> getMemberType(const lang::Identifier& name);
        virtual bool                              definesIndirection();
        virtual lang::ResolvingHandle<lang::Type> getIndirectionType();

        virtual bool validateDefinition(ValidationLogger& validation_logger) const;
        virtual bool validate(ValidationLogger& validation_logger, lang::Location location) const;
        virtual bool validateSubscript(lang::Location                    indexed_location,
                                       lang::ResolvingHandle<lang::Type> index_type,
                                       lang::Location                    index_location,
                                       ValidationLogger&                 validation_logger) const;
        virtual bool validateOperator(lang::BinaryOperator              op,
                                      lang::ResolvingHandle<lang::Type> other,
                                      lang::Location                    left_location,
                                      lang::Location                    right_location,
                                      ValidationLogger&                 validation_logger) const;
        virtual bool validateOperator(lang::UnaryOperator op,
                                      lang::Location      location,
                                      ValidationLogger&   validation_logger) const;
        virtual bool validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                lang::Location                    location,
                                                ValidationLogger&                 validation_logger) const;
        virtual bool validateMemberAccess(const lang::Identifier& name, ValidationLogger& validation_logger) const;
        virtual bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const;

        virtual std::shared_ptr<lang::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                            std::shared_ptr<Value> index,
                                                            CompileContext*        context);
        virtual std::shared_ptr<lang::Value> buildOperator(lang::BinaryOperator   op,
                                                           std::shared_ptr<Value> left,
                                                           std::shared_ptr<Value> right,
                                                           CompileContext*        context);
        virtual std::shared_ptr<lang::Value> buildOperator(lang::UnaryOperator    op,
                                                           std::shared_ptr<Value> value,
                                                           CompileContext*        context);
        virtual std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                     std::shared_ptr<Value>            value,
                                                                     CompileContext*                   context);
        virtual std::shared_ptr<lang::Value> buildMemberAccess(std::shared_ptr<Value>  value,
                                                               const lang::Identifier& name,
                                                               CompileContext*         context);
        virtual std::shared_ptr<lang::Value> buildIndirection(std::shared_ptr<Value> value, CompileContext* context);

        void         buildDefaultInitializer(llvm::Value* ptr, CompileContext* context);
        virtual void buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext* context);
        virtual void buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext* context);
        virtual void buildNativeDeclaration(CompileContext* context);
        virtual void buildNativeDefinition(CompileContext* context);

      protected:
        void defineDefaultInitializer(CompileContext* context);
        void defineCopyInitializer(CompileContext* context);

        /**
         * Build the part of the definition that default-initializes a single element of this type.
         */
        virtual void buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext* context);

        virtual std::string createMangledName() = 0;

        virtual llvm::DIType* createDebugType(CompileContext* context) = 0;

        /**
         * Check the dependencies of the type definition for cyclic dependencies.
         * @param validation_logger The validation logger to use.
         * @return True if the dependencies are valid.
         */
        bool                                       checkDependencies(ValidationLogger& validation_logger) const;
        virtual std::vector<lang::TypeDefinition*> getDependencies() const;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> self() const;

      protected:
        llvm::Function* default_initializer_ {nullptr};
        llvm::Function* copy_initializer_ {nullptr};

      private:
        lang::Identifier name_;
        lang::Location   location_;
        std::string      mangled_name_ {};
        lang::Type*      type_ {nullptr};
        lang::Scope*     containing_scope_ {nullptr};
        llvm::DIType*    debug_type_ {nullptr};
    };
}

#endif
