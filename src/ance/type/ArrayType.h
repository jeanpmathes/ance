#ifndef ANCE_SRC_ANCE_TYPE_ARRAYTYPE_H_
#define ANCE_SRC_ANCE_TYPE_ARRAYTYPE_H_

#include "Type.h"
#include "Application.h"

namespace llvm
{
class ArrayType;
}

namespace ance
{
class Scope;

class ArrayType : public Type
{
	private:
		ArrayType(Type* element_type, uint64_t size);

	public:
		std::string getName() override;

		llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

		llvm::Type* getContentType(llvm::LLVMContext& c) override;

		InternalStorage storage() override;

		bool isIndexerDefined(Indexer indexer) override;

		ance::Type* getIndexerReturnType() override;

		ance::Value* buildGetIndexer(ance::Value* indexed, ance::Value* index, CompileContext* context) override;

		void buildSetIndexer(
			ance::Value* indexed,
			ance::Value* index,
			ance::Value* value,
			CompileContext* context
		) override;

	private:
		llvm::Value* buildGetElementPointer(
			ance::Value* indexed,
			ance::Value* index,
			CompileContext* context
		) const;

	public:

		~ArrayType() override = default;

	private:
		uint64_t size_;
		ance::Type* element_type_;
		llvm::ArrayType* type_{nullptr};

	public:
		static ance::Type* get(Application& app, Type* element_type, uint64_t size);
};
}

#endif
