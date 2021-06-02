#ifndef ANCE_SRC_ANCE_TYPE_POINTERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_POINTERTYPE_H_

#include "Type.h"

class Application;

namespace ance
{
class PointerType : public Type
{
	private:
		explicit PointerType(Type* element_type);

	public:
		std::string getName() override;

		llvm::Constant* getDefault(llvm::LLVMContext& c) override;

		llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

		bool isIndexerDefined(Indexer indexer) override;

		ance::Type* getIndexerReturnType() override;

		llvm::Value* buildGetIndexer(
			ance::Value* indexed,
			ance::Value* index,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~PointerType() override = default;

	private:
		ance::Type* element_type_;

	public:
		static ance::Type* get(Application& app, Type* element_type);
};
}

#endif
