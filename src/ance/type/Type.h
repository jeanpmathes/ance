#ifndef ANCE_SRC_ANCE_TYPE_TYPE_H_
#define ANCE_SRC_ANCE_TYPE_TYPE_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

#include "Indexer.h"

class CompileState;

#include "InternalStorage.h"

namespace llvm
{
class LLVMContext;

class Type;

class DIBuilder;
}

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

		virtual llvm::Constant* getDefault(llvm::LLVMContext& c) = 0;

		llvm::Type* getNativeType(llvm::LLVMContext& c);

		virtual llvm::Type* getContentType(llvm::LLVMContext& c) = 0;

		llvm::TypeSize getSize(llvm::Module* m);

		virtual InternalStorage storage();

		virtual bool isIndexerDefined(Indexer indexer);

		virtual ance::Type* getIndexerReturnType();

		virtual llvm::Value* buildGetIndexer(
			ance::Value* indexed,
			ance::Value* index,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);

};
}
#endif