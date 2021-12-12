#ifndef ANCE_SRC_ANCE_TYPE_TYPEDEFINITION_H_
#define ANCE_SRC_ANCE_TYPE_TYPEDEFINITION_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "ance/utility/Location.h"
#include "ance/utility/ResolvingHandle.h"

namespace ance
{
    class Scope;
    class Value;
    class Type;
}

class CompileContext;
class ValidationLogger;

namespace ance
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
        explicit TypeDefinition(std::string name, ance::Location location = ance::Location(0, 0, 0, 0));

      public:
        virtual ~TypeDefinition() = default;

        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] ance::Location     getDefinitionLocation() const;
        [[nodiscard]] bool               isCustom() const;

        [[nodiscard]] virtual bool isIntegerType() const;
        [[nodiscard]] virtual bool isIntegerType(uint64_t bit_size, bool is_signed) const;
        [[nodiscard]] virtual bool isPointerType() const;

        void setType(ance::Type* type);

        virtual ance::ResolvingHandle<ance::Type> getActualType();
        virtual ance::ResolvingHandle<ance::Type> getOriginalType();

        void         setContainingScope(Scope* scope);
        virtual void onScope();
        Scope*       scope();

        virtual llvm::Constant* getDefaultContent(llvm::LLVMContext& c) = 0;

        llvm::Type*         getNativeType(llvm::LLVMContext& c);
        virtual llvm::Type* getContentType(llvm::LLVMContext& c) = 0;
        llvm::DIType*       getDebugType(CompileContext* context);

        llvm::TypeSize getNativeSize(llvm::Module* m);
        llvm::TypeSize getContentSize(llvm::Module* m);

        virtual bool isSubscriptDefined();

        virtual ance::ResolvingHandle<ance::Type> getSubscriptReturnType();

        virtual bool validateDefinition(ValidationLogger& validation_logger);
        virtual bool validate(ValidationLogger& validation_logger, ance::Location location);

        virtual bool validateSubscript(ance::Location                    indexed_location,
                                       ance::ResolvingHandle<ance::Type> index_type,
                                       ance::Location                    index_location,
                                       ValidationLogger&                 validation_logger);

        virtual std::shared_ptr<ance::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                            std::shared_ptr<Value> index,
                                                            CompileContext*        context);

        virtual bool                         isImplicitlyConvertibleTo(ance::ResolvingHandle<ance::Type> target);
        virtual std::shared_ptr<ance::Value> convertImplicitlyTo(ance::ResolvingHandle<ance::Type> target,
                                                                 std::shared_ptr<Value>            value,
                                                                 CompileContext*                   context);

        virtual bool                         isImplicitlyConvertibleFrom(ance::ResolvingHandle<ance::Type> source);
        virtual std::shared_ptr<ance::Value> convertImplicitlyFrom(std::shared_ptr<Value>            value,
                                                                   ance::ResolvingHandle<ance::Type> self,
                                                                   CompileContext*                   context);

      protected:
        virtual llvm::DIType* createDebugType(CompileContext* context) = 0;

        /**
         * Check the dependencies of the type definition for cyclic dependencies.
         * @param validation_logger The validation logger to use.
         * @return True if the dependencies are valid.
         */
        bool                                       checkDependencies(ValidationLogger& validation_logger);
        virtual std::vector<ance::TypeDefinition*> getDependencies();

        ance::ResolvingHandle<ance::Type> self();

      private:
        std::string    name_;
        ance::Location location_;
        ance::Type*    type_ {nullptr};
        ance::Scope*   containing_scope_ {nullptr};
        llvm::DIType*  debug_type_ {nullptr};
    };
}

#endif
