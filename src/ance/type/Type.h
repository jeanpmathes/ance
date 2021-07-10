#ifndef ANCE_SRC_ANCE_TYPE_TYPE_H_
#define ANCE_SRC_ANCE_TYPE_TYPE_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "Indexer.h"

class CompileContext;

#include "InternalStorage.h"

namespace llvm
{
    class LLVMContext;

    class Type;

    class DIBuilder;
}// namespace llvm

namespace ance
{
    class Value;

    class Type
    {
      protected:
        Type() = default;

        virtual ~Type() = default;

      public:
        Type(const Type&) = delete;

        Type(Type&&) = delete;

        virtual std::string getName() = 0;

        virtual llvm::Constant* getDefaultContent(llvm::LLVMContext& c) = 0;

        llvm::Type* getNativeType(llvm::LLVMContext& c);

        virtual llvm::Type* getContentType(llvm::LLVMContext& c) = 0;

        llvm::TypeSize getNativeSize(llvm::Module* m);

        llvm::TypeSize getContentSize(llvm::Module* m);

        virtual InternalStorage storage();

        virtual bool isIndexerDefined(Indexer indexer);

        virtual ance::Type* getIndexerReturnType();

        virtual ance::Value* buildGetIndexer(ance::Value* indexed, ance::Value* index, CompileContext* context);

        virtual void buildSetIndexer(
            ance::Value*    indexed,
            ance::Value*    index,
            ance::Value*    value,
            CompileContext* context);
    };
}
#endif