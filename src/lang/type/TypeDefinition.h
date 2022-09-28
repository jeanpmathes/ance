#ifndef ANCE_SRC_LANG_TYPE_TYPEDEFINITION_H_
#define ANCE_SRC_LANG_TYPE_TYPEDEFINITION_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "lang/AccessModifier.h"
#include "lang/BinaryOperator.h"
#include "lang/UnaryOperator.h"
#include "lang/type/StateCount.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Scope;
    class Value;
    class Type;
    class Function;
    class PredefinedFunction;
    class VectorizableType;
    class FloatingPointType;
    class FixedWidthIntegerType;
    class VectorType;
    class ArrayType;
    class IntegerType;
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
        explicit TypeDefinition(lang::Identifier name, lang::Location location = lang::Location::global());

      public:
        virtual ~TypeDefinition() = default;

        void setType(lang::Type* type);

        [[nodiscard]] const Identifier& name() const;
        const std::string&              getMangledName() const;
        [[nodiscard]] lang::Location    getDefinitionLocation() const;
        [[nodiscard]] bool              isCustom() const;

        [[nodiscard]] virtual StateCount getStateCount() const = 0;

        [[nodiscard]] virtual const FixedWidthIntegerType* isFixedWidthIntegerType() const;
        [[nodiscard]] virtual bool                     isFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const;
        [[nodiscard]] virtual bool                     isSigned() const;
        [[nodiscard]] virtual const IntegerType*       isIntegerType() const;
        [[nodiscard]] virtual bool                     isBooleanType() const;
        [[nodiscard]] virtual bool                     isUnsignedIntegerPointerType() const;
        [[nodiscard]] virtual const FloatingPointType* isFloatingPointType() const;
        [[nodiscard]] virtual bool                     isFloatingPointType(size_t precision) const;
        [[nodiscard]] virtual bool                     isSizeType() const;
        [[nodiscard]] virtual bool                     isDiffType() const;
        [[nodiscard]] virtual bool                     isVoidType() const;
        [[nodiscard]] virtual bool                     isPointerType() const;
        [[nodiscard]] virtual bool                     isAddressType() const;
        [[nodiscard]] virtual bool                     isBufferType() const;
        [[nodiscard]] virtual bool                     isOpaquePointerType() const;
        [[nodiscard]] virtual bool                     isReferenceType() const;
        [[nodiscard]] virtual bool                     isStructType() const;
        [[nodiscard]] virtual const VectorizableType*  isVectorizable() const;
        [[nodiscard]] virtual VectorizableType*        isVectorizable();
        [[nodiscard]] virtual const VectorType*        isVectorType() const;
        [[nodiscard]] virtual VectorType*              isVectorType();
        [[nodiscard]] virtual const ArrayType*         isArrayType() const;
        [[nodiscard]] virtual ArrayType*               isArrayType();

        [[nodiscard]] virtual lang::ResolvingHandle<lang::Type> getElementType() const;

        [[nodiscard]] virtual lang::ResolvingHandle<lang::Type> getActualType() const;
        [[nodiscard]] virtual lang::ResolvingHandle<lang::Type> getOriginalType() const;

        [[nodiscard]] virtual lang::AccessModifier getAccessModifier() const;

        void         setContainingScope(Scope* scope);
        virtual void onScope();
        Scope*       scope();

        void postResolve();
        bool requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters);

        virtual llvm::Constant* getDefaultContent(llvm::Module& m) = 0;

        llvm::Type*         getNativeType(llvm::LLVMContext& c) const;
        virtual llvm::Type* getContentType(llvm::LLVMContext& c) const = 0;
        llvm::DIType*       getDebugType(CompileContext& context);

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
                                                            CompileContext&        context);
        virtual std::shared_ptr<lang::Value> buildOperator(lang::BinaryOperator   op,
                                                           std::shared_ptr<Value> left,
                                                           std::shared_ptr<Value> right,
                                                           CompileContext&        context);
        virtual std::shared_ptr<lang::Value> buildOperator(lang::UnaryOperator    op,
                                                           std::shared_ptr<Value> value,
                                                           CompileContext&        context);
        virtual std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                     std::shared_ptr<Value>            value,
                                                                     CompileContext&                   context);
        virtual std::shared_ptr<lang::Value> buildMemberAccess(std::shared_ptr<Value>  value,
                                                               const lang::Identifier& name,
                                                               CompileContext&         context);
        virtual std::shared_ptr<lang::Value> buildIndirection(std::shared_ptr<Value> value, CompileContext& context);

        void         buildDefaultInitializer(llvm::Value* ptr, CompileContext& context);
        virtual void buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext& context);
        virtual void buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext& context);
        void         buildFinalizer(llvm::Value* ptr, CompileContext& context);
        virtual void buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext& context);

        virtual void buildNativeDeclaration(CompileContext& context);
        virtual void buildNativeDefinition(CompileContext& context);

        virtual void createConstructors();

        /**
         * Whether this type can be default-constructed by zeroing memory.
         */
        [[nodiscard]] virtual bool isTriviallyDefaultConstructible() const;
        /**
         * Whether this type can be copy-constructed by copying memory.
         */
        [[nodiscard]] virtual bool isTriviallyCopyConstructible() const;
        /**
         * Whether this type can be destructed by doing nothing.
         */
        [[nodiscard]] virtual bool isTriviallyDestructible() const;

        void defineDefaultInitializer(CompileContext& context);
        void defineCopyInitializer(CompileContext& context);
        void defineDefaultFinalizer(CompileContext& context);

        void defineConstructors(CompileContext& context);
        void buildConstructors(CompileContext& context);

        /**
         * Build the part of the definition that default-initializes a single element of this type.
         */
        virtual void buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext& context);
        /**
         * Build the part of the definition that copies a single element of this type.
         */
        virtual void buildSingleCopyInitializerDefinition(llvm::Value*    dts_ptr,
                                                          llvm::Value*    src_ptr,
                                                          CompileContext& context);
        /**
         * Build the part of the definition that default-finalizes a single element of this type.
         */
        virtual void buildSingleDefaultFinalizerDefinition(llvm::Value* ptr, CompileContext& context);

        virtual std::string createMangledName() const = 0;

        virtual llvm::DIType* createDebugType(CompileContext& context) = 0;

        /**
         * Check the dependencies of the type definition for cyclic dependencies.
         * @param validation_logger The validation logger to use.
         * @return True if the dependencies are valid.
         */
        bool checkDependencies(ValidationLogger& validation_logger) const;
        bool hasCyclicDependency() const;
        [[nodiscard]] virtual std::vector<lang::TypeDefinition*> getDependencies() const;

        /**
         * Create a constructor for this type. The function is added to the overload list.
         * @param parameter_types The parameter types of the function.
         * @return The function.
         */
        lang::PredefinedFunction& createConstructor(std::vector<lang::ResolvingHandle<lang::Type>> parameter_types);

        /**
         * Decide whether a function (constructor) overload that is requested exists for this type.
         * @param parameters The parameters of the function.
         * @return True if the function exists.
         */
        virtual bool acceptOverloadRequest(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters);

        /**
         * Build a function (constructor) overload that was accepted before.
         * @param parameters The parameters of the function overload.
         * @param function The already declared function which has to be built.
         * @param context The current compile context.
         */
        virtual void buildRequestedOverload(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
                                            lang::PredefinedFunction&                             function,
                                            CompileContext&                                       context);

        [[nodiscard]] lang::ResolvingHandle<lang::Type> self() const;

      protected:
        llvm::Function* default_initializer_ {nullptr};
        llvm::Function* copy_initializer_ {nullptr};
        llvm::Function* default_finalizer_ {nullptr};

      private:
        void buildPointerIteration(llvm::Function*                                    function,
                                   llvm::Value*                                       ptr,
                                   llvm::Value*                                       count,
                                   std::function<void(llvm::Value*, CompileContext&)> operation,
                                   CompileContext&                                    context);

      private:
        lang::Identifier    name_;
        lang::Location      location_;
        mutable std::string mangled_name_ {};
        lang::Type*         type_ {nullptr};
        lang::Scope*        containing_scope_ {nullptr};
        llvm::DIType*       debug_type_ {nullptr};

        lang::PredefinedFunction* default_constructor_ {nullptr};

        mutable std::optional<bool> cyclic_dependency_ {};

        std::vector<std::pair<std::vector<lang::ResolvingHandle<lang::Type>>, lang::PredefinedFunction*>>
            requested_constructors_;
    };
}

#endif
