#ifndef ANCE_SRC_LANG_TYPE_STRUCTTYPE_H_
#define ANCE_SRC_LANG_TYPE_STRUCTTYPE_H_

#include "CustomType.h"

#include <map>

#include "lang/construct/Member.h"
#include "lang/utility/Identifier.h"

namespace lang
{
    /**
 * The type of a struct.
 */
    class StructType : public lang::CustomType
    {
      public:
        StructType(lang::AccessModifier                              access_modifier,
                   lang::Identifier                                  name,
                   std::vector<std::reference_wrapper<lang::Member>> members,
                   lang::Location                                    location);

        [[nodiscard]] StateCount getStateCount() const override;
        bool                     isStructType() const override;

        llvm::Constant*   getDefaultContent(llvm::Module& m) const override;
        llvm::StructType* getContentType(llvm::LLVMContext& c) const override;

        [[nodiscard]] lang::AccessModifier getAccessModifier() const override;

        bool                              hasMember(lang::Identifier const& name) const override;
        lang::ResolvingHandle<lang::Type> getMemberType(lang::Identifier const& name) override;
        bool validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildMemberAccess(Shared<Value>           value,
                                              lang::Identifier const& name,
                                              CompileContext&         context) override;

      protected:
        void buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext& context) override;
        void buildSingleCopyInitializerDefinition(llvm::Value*    dts_ptr,
                                                  llvm::Value*    src_ptr,
                                                  CompileContext& context) override;
        void buildSingleDefaultFinalizerDefinition(llvm::Value* ptr, CompileContext& context) override;

        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) const override;

      public:
        std::vector<std::reference_wrapper<const lang::Type>> getContained() const override;

      private:
        llvm::Value* buildGetElementPointer(llvm::Value* struct_ptr, int32_t member_index, CompileContext& context);

      private:
        [[maybe_unused]] lang::AccessModifier access_;

        std::vector<std::reference_wrapper<lang::Member>>                members_;
        std::map<lang::Identifier, std::reference_wrapper<lang::Member>> member_map_ {};
        std::map<lang::Identifier, int32_t>                              member_indices_ {};

        mutable llvm::StructType* native_type_ {nullptr};
    };
}

#endif
