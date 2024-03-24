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
        StructType(lang::Accessibility                               accessibility,
                   lang::Identifier                                  name,
                   std::vector<std::reference_wrapper<lang::Member>> members,
                   lang::Location                                    location);

        [[nodiscard]] StateCount getStateCount() const override;
        bool                     isStructType() const override;

        bool          hasMember(lang::Identifier const& name) const override;
        Member&       getMember(lang::Identifier const& name) override;
        Member const& getMember(lang::Identifier const& name) const override;

        bool validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildMemberAccess(Shared<lang::Value>     value,
                                              lang::Identifier const& name,
                                              Execution&              exec) const override;

      protected:
        void performSingleDefaultInitializerDefinition(Shared<lang::Value> ptr, Execution& exec) const override;
        void performSingleCopyInitializerDefinition(Shared<lang::Value> dts_ptr,
                                                    Shared<lang::Value> src_ptr,
                                                    Execution&          exec) const override;
        void performSingleDefaultFinalizerDefinition(Shared<lang::Value> ptr, Execution& exec) const override;

        std::string createMangledName() const override;
        void        registerExecutionType(Execution& exec) const override;

      public:
        std::vector<lang::ResolvingHandle<lang::Type>> getDeclarationDependencies() override;
        std::vector<lang::ResolvingHandle<lang::Type>> getDefinitionDependencies() override;

        bool isTriviallyDefaultConstructible() const override;
        bool isTriviallyCopyConstructible() const override;
        bool isTriviallyDestructible() const override;

      private:
        std::vector<std::reference_wrapper<lang::Member>>                members_;
        std::map<lang::Identifier, std::reference_wrapper<lang::Member>> member_map_ {};
    };
}

#endif
