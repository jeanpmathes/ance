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

		llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

		llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

		bool isIndexerDefined(Indexer indexer) override;

		ance::Type* getIndexerReturnType() override;

		ance::Value* buildGetIndexer(
			ance::Value* indexed,
			ance::Value* index,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		void buildSetIndexer(
			ance::Value* indexed,
			ance::Value* index,
			ance::Value* value,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		static llvm::Value* buildGetElementPointer(
			ance::Value* indexed,
			ance::Value* index,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);

	public:

		~PointerType() override = default;

	private:
		ance::Type* element_type_;

	public:
		static ance::Type* get(Application& app, ance::Type* element_type);

		static bool isPointerType(ance::Type* type);
};
}

#endif
