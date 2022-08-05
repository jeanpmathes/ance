#ifndef ANCE_SRC_LANG_TYPE_STRUCTTYPE_H_
#define ANCE_SRC_LANG_TYPE_STRUCTTYPE_H_

#include "TypeDefinition.h"

#include <map>

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

        [[nodiscard]] StateCount getStateCount() const override;

        llvm::Constant*   getDefaultContent(llvm::Module& m) override;
        llvm::StructType* getContentType(llvm::LLVMContext& c) const override;

        [[nodiscard]] lang::AccessModifier getAccessModifier() const override;

        void onScope() override;

        bool validateDefinition(ValidationLogger& validation_logger) const override;

        bool                              hasMember(const lang::Identifier& name) override;
        lang::ResolvingHandle<lang::Type> getMemberType(const lang::Identifier& name) override;
        bool validateMemberAccess(const lang::Identifier& name, ValidationLogger& validation_logger) const override;
        std::shared_ptr<lang::Value> buildMemberAccess(std::shared_ptr<Value>  value,
                                                       const lang::Identifier& name,
                                                       CompileContext*         context) override;

      protected:
        void buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext* context) override;
        void buildSingleCopyInitializerDefinition(llvm::Value*    dts_ptr,
                                                  llvm::Value*    src_ptr,
                                                  CompileContext* context) override;
        void buildSingleDefaultFinalizerDefinition(llvm::Value* ptr, CompileContext* context) override;

        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext* context) override;

        [[nodiscard]] std::vector<lang::TypeDefinition*> getDependencies() const override;

      private:
        llvm::Value* buildGetElementPointer(llvm::Value* struct_ptr, int32_t member_index, CompileContext* context);

      private:
        [[maybe_unused]] lang::AccessModifier access_;

        std::vector<std::unique_ptr<lang::Member>>                       members_;
        std::map<lang::Identifier, std::reference_wrapper<lang::Member>> member_map_ {};
        std::map<lang::Identifier, int32_t>                              member_indices_ {};
        lang::Scope*                                                     scope_;

        mutable llvm::StructType* native_type_ {nullptr};
    };
}

#endif
