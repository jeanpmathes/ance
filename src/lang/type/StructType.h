#ifndef ANCE_SRC_LANG_TYPE_STRUCTTYPE_H_
#define ANCE_SRC_LANG_TYPE_STRUCTTYPE_H_

#include "TypeDefinition.h"
#include "lang/construct/Member.h"
#include "lang/utility/Identifier.h"

namespace lang
{
    /**
 * The type of a struct.
 */
    class StructType : public lang::TypeDefinition
    {
      public:
        StructType(lang::AccessModifier                       access_modifier,
                   lang::Identifier                           name,
                   std::vector<std::unique_ptr<lang::Member>> members,
                   lang::Scope*                               scope,
                   lang::Location                             location);

        StateCount getStateCount() const override;

        llvm::Constant*   getDefaultContent(llvm::LLVMContext& c) override;
        llvm::StructType* getContentType(llvm::LLVMContext& c) override;

        void onScope() override;

        bool validateDefinition(ValidationLogger& validation_logger) override;

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

        std::vector<lang::TypeDefinition*> getDependencies() override;

      private:
        [[maybe_unused]] lang::AccessModifier access_;

        std::vector<std::unique_ptr<lang::Member>> members_;
        lang::Scope*                               scope_;

        llvm::StructType* native_type_ {nullptr};
    };
}

#endif
