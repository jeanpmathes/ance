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
        explicit TypeDefinition(std::string name);

      public:
        virtual ~TypeDefinition() = default;

        [[nodiscard]] const std::string& getName() const;

        virtual llvm::Constant* getDefaultContent(llvm::LLVMContext& c) = 0;

        llvm::Type*         getNativeType(llvm::LLVMContext& c);
        virtual llvm::Type* getContentType(llvm::LLVMContext& c) = 0;
        llvm::DIType*       getDebugType(CompileContext* context);

        llvm::TypeSize getNativeSize(llvm::Module* m);
        llvm::TypeSize getContentSize(llvm::Module* m);

        virtual bool isSubscriptDefined();

        virtual ance::ResolvingHandle<ance::Type> getSubscriptReturnType();

        virtual bool validate(ValidationLogger& validation_logger, ance::Location location);

        virtual bool validateSubscript(ance::Location                    indexed_location,
                                       ance::ResolvingHandle<ance::Type> index_type,
                                       ance::Location                    index_location,
                                       ValidationLogger&                 validation_logger);

        virtual std::shared_ptr<ance::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                            std::shared_ptr<Value> index,
                                                            CompileContext*        context);

      protected:
        virtual llvm::DIType* createDebugType(CompileContext* context) = 0;

      private:
        std::string   name_;
        llvm::DIType* debug_type_ {nullptr};
    };
}

#endif
