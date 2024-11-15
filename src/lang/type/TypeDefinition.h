#ifndef ANCE_SRC_LANG_TYPE_TYPEDEFINITION_H_
#define ANCE_SRC_LANG_TYPE_TYPEDEFINITION_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "lang/Accessibility.h"
#include "lang/BinaryOperator.h"
#include "lang/UnaryOperator.h"
#include "lang/construct/Function.h"
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
    class AddressType;
    class VectorType;
    class ArrayType;
    class IntegerType;
    class Context;
}

class Execution;
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

        /**
         * Get whether all contained types are defined.
         * @return True if all contained types are defined.
         */
        [[nodiscard]] bool isFullyDefined() const;

        [[nodiscard]] Identifier const& name() const;
        std::string const&              getMangledName() const;
        [[nodiscard]] lang::Location    getDefinitionLocation() const;
        [[nodiscard]] virtual bool      isCustom() const;
        [[nodiscard]] virtual bool      isImported() const;
        [[nodiscard]] virtual bool      isCMP() const;

        [[nodiscard]] virtual StateCount getStateCount() const = 0;

        [[nodiscard]] virtual FixedWidthIntegerType const* isFixedWidthIntegerType() const;
        [[nodiscard]] virtual bool                     isFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const;
        [[nodiscard]] virtual bool                     isSigned() const;
        [[nodiscard]] virtual IntegerType const*       isIntegerType() const;
        [[nodiscard]] virtual bool                     isBooleanType() const;
        [[nodiscard]] virtual bool                     isCharType() const;
        [[nodiscard]] virtual bool                     isUnsignedIntegerPointerType() const;
        [[nodiscard]] virtual FloatingPointType const* isFloatingPointType() const;
        [[nodiscard]] virtual bool                     isFloatingPointType(size_t precision) const;
        [[nodiscard]] virtual bool                     isSizeType() const;
        [[nodiscard]] virtual bool                     isDiffType() const;
        [[nodiscard]] virtual bool                     isUnitType() const;
        [[nodiscard]] virtual bool                     isNullValueType() const;
        [[nodiscard]] virtual bool                         isPointerType() const;
        [[nodiscard]] virtual AddressType const*           isAddressType() const;
        [[nodiscard]] virtual bool                         isBufferType() const;
        [[nodiscard]] virtual bool                     isOpaquePointerType() const;
        [[nodiscard]] virtual bool                     isReferenceType() const;
        [[nodiscard]] virtual StructType*                  isStructType();
        [[nodiscard]] virtual StructType const*            isStructType() const;
        [[nodiscard]] virtual VectorizableType const*  isVectorizable() const;
        [[nodiscard]] virtual VectorizableType*        isVectorizable();
        [[nodiscard]] virtual VectorType const*        isVectorType() const;
        [[nodiscard]] virtual VectorType*              isVectorType();
        [[nodiscard]] virtual ArrayType const*             isArrayType() const;
        [[nodiscard]] virtual ArrayType*                   isArrayType();

        virtual lang::ResolvingHandle<lang::Type> getElementType();
        [[nodiscard]] virtual lang::Type const&   getElementType() const;

        [[nodiscard]] virtual lang::ResolvingHandle<lang::Type> getActualType();
        [[nodiscard]] virtual lang::Type const&                 getActualType() const;

        /**
         * Get a non-const handle to this type. This is only possible for non-custom types.
         * @return The handle to this type. The actual type is not cloned.
         */
        [[nodiscard]] virtual lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const;

        [[nodiscard]] virtual lang::Accessibility const& getAccessibility() const;

        void               setContainingScope(Scope* scope);
        [[nodiscard]] bool isContainingScopeSet() const;
        Scope&             scope();
        Scope const&       scope() const;

        void postResolve();
        bool requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters);

        virtual bool              isSubscriptDefined() const;
        virtual lang::Type const& getSubscriptReturnType() const;
        virtual bool              isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const;
        virtual bool              isOperatorDefined(lang::UnaryOperator op) const;
        virtual lang::Type const& getOperatorResultType(lang::BinaryOperator op, lang::Type const& other) const;
        virtual lang::Type const& getOperatorResultType(lang::UnaryOperator op) const;
        virtual bool              isImplicitlyConvertibleTo(lang::Type const& other) const;
        virtual bool              isCastingPossibleTo(lang::Type const& other) const;
        virtual bool              hasMember(lang::Identifier const& name) const;
        virtual Member&           getMember(lang::Identifier const&);
        virtual Member const&     getMember(lang::Identifier const&) const;
        virtual bool              definesIndirection() const;
        virtual lang::Type const& getIndirectionType() const;

        virtual bool validate(ValidationLogger& validation_logger, lang::Location location) const;
        virtual bool validateSubscript(lang::Location    indexed_location,
                                       lang::Type const& index_type,
                                       lang::Location    index_location,
                                       ValidationLogger& validation_logger) const;
        virtual bool validateOperator(lang::BinaryOperator op,
                                      lang::Type const&    other,
                                      lang::Location       left_location,
                                      lang::Location       right_location,
                                      ValidationLogger&    validation_logger) const;
        virtual bool validateOperator(lang::UnaryOperator op,
                                      lang::Location      location,
                                      ValidationLogger&   validation_logger) const;
        virtual bool validateImplicitConversion(lang::Type const& other,
                                                lang::Location    location,
                                                ValidationLogger& validation_logger) const;
        virtual bool validateCast(lang::Type const& other,
                                  lang::Location    location,
                                  ValidationLogger& validation_logger) const;
        virtual bool validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const;
        virtual bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const;

        virtual Shared<lang::Value> execSubscript(Shared<lang::Value> indexed,
                                                  Shared<lang::Value> index,
                                                   Execution&          exec) const;
        virtual Shared<lang::Value> execOperator(lang::BinaryOperator op,
                                                 Shared<lang::Value>  left,
                                                  Shared<lang::Value>  right,
                                                  Execution&           exec) const;
        virtual Shared<lang::Value> execOperator(lang::UnaryOperator op,
                                                 Shared<lang::Value> value,
                                                  Execution&          exec) const;
        virtual Shared<lang::Value> execImplicitConversion(lang::Type const&   other,
                                                           Shared<lang::Value> value,
                                                            Execution&          exec) const;
        virtual Shared<lang::Value> execCast(lang::Type const& other, Shared<lang::Value> value,
                                              Execution&          exec) const;
        virtual Shared<lang::Value> execMemberAccess(Shared<lang::Value>     value,
                                                     lang::Identifier const& name,
                                                      Execution&              exec) const;
        virtual Shared<lang::Value> execIndirection(Shared<lang::Value> value, Execution& exec) const;

        void         performDefaultInitializer(Shared<lang::Value> ptr, Execution& exec) const;
        virtual void performDefaultInitializer(Shared<lang::Value> ptr,
                                               Shared<lang::Value> count,
                                               Execution&          exec) const;
        virtual void performCopyInitializer(Shared<lang::Value> destination,
                                            Shared<lang::Value> source,
                                            Execution&          exec) const;
        void         performFinalizer(Shared<lang::Value> ptr, Execution& exec) const;
        virtual void performFinalizer(Shared<lang::Value> ptr,
                                      Shared<lang::Value> count, Execution& exec) const;

        virtual void registerExecutionType(Execution& exec) const = 0;

        virtual void registerDeclaration(Execution& exec) const;
        virtual void registerDefinition(Execution& exec) const;

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

        void defineDefaultInitializer(Execution& exec) const;
        void defineCopyInitializer(Execution& exec) const;
        void defineDefaultFinalizer(Execution& exec) const;

        void defineConstructors(Execution& exec) const;
        void registerConstructors(Execution& exec) const;

        /**
         * Build the part of the definition that default-initializes a single element of this type.
         */
        virtual void performSingleDefaultInitializerDefinition(Shared<lang::Value> ptr, Execution& exec) const;
        /**
         * Build the part of the definition that copies a single element of this type.
         */
        virtual void performSingleCopyInitializerDefinition(Shared<lang::Value> dst_ptr,
                                                            Shared<lang::Value> src_ptr,
                                                            Execution&          exec) const;
        /**
         * Build the part of the definition that default-finalizes a single element of this type.
         */
        virtual void performSingleDefaultFinalizerDefinition(Shared<lang::Value>, Execution&) const;

        virtual std::string createMangledName() const = 0;

        virtual std::vector<lang::ResolvingHandle<lang::Type>> getDeclarationDependencies();
        virtual std::vector<lang::ResolvingHandle<lang::Type>> getDefinitionDependencies();

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
        virtual bool acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters);

        /**
         * Build a function (constructor) overload that was accepted before.
         * @param parameters The parameters of the function overload.
         * @param function The already declared function which has to be built.
         * @param exec The current execution context.
         */
        virtual void execRequestedOverload(std::vector<std::reference_wrapper<lang::Type const>> parameters,
                                           lang::PredefinedFunction&                             function,
                                            Execution&                                            exec) const;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> self();
        [[nodiscard]] lang::Type const&                 self() const;

      private:
        lang::Identifier    name_;
        lang::Location      location_;
        mutable std::string mangled_name_ {};
        lang::Type*         type_ {nullptr};
        lang::Scope*        containing_scope_ {nullptr};

        lang::PredefinedFunction* default_constructor_ {nullptr};

        mutable Optional<bool> cyclic_dependency_ {};

        Optional<lang::ResolvingHandle<lang::Function>> default_initializer_ {};
        Optional<lang::ResolvingHandle<lang::Function>> copy_initializer_ {};
        Optional<lang::ResolvingHandle<lang::Function>> default_finalizer_ {};

        std::vector<std::pair<std::vector<std::reference_wrapper<lang::Type const>>, lang::PredefinedFunction*>>
            requested_constructors_;
    };
}

#endif
