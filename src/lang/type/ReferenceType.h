#ifndef ANCE_SRC_LANG_TYPE_REFERENCETYPE_H_
#define ANCE_SRC_LANG_TYPE_REFERENCETYPE_H_

#include "TypeDefinition.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/utility/TypeRegistry.h"

class Application;

namespace lang
{
    /**
     * A reference refers to another stored value.
     */
    class ReferenceType : public lang::TypeDefinition
    {
      public:
        explicit ReferenceType(lang::ResolvingHandle<lang::Type> element_type);

        [[nodiscard]] StateCount getStateCount() const override;

        [[nodiscard]] bool isReferenceType() const override;

        lang::ResolvingHandle<lang::Type> getElementType() override;
        lang::Type const&                 getElementType() const override;

        lang::ResolvingHandle<lang::Type> getActualType() override;
        lang::Type const&                 getActualType() const override;

        bool isSubscriptDefined() const override;

        lang::Type const& getSubscriptReturnType() const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        bool                validateSubscript(lang::Location    indexed_location,
                                              lang::Type const& index_type,
                                              lang::Location    index_location,
                                              ValidationLogger& validation_logger) const override;
        Shared<lang::Value> execSubscript(Shared<lang::Value> indexed,
                                          Shared<lang::Value> index,
                                           Execution&          exec) const override;

        bool                isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const override;
        lang::Type const&   getOperatorResultType(lang::BinaryOperator op, lang::Type const& other) const override;
        bool                validateOperator(lang::BinaryOperator op,
                                             lang::Type const&    other,
                                             lang::Location       left_location,
                                             lang::Location       right_location,
                                             ValidationLogger&    validation_logger) const override;
        Shared<lang::Value> execOperator(lang::BinaryOperator op,
                                         Shared<lang::Value>  left,
                                          Shared<lang::Value>  right,
                                          Execution&           exec) const override;

        bool                isOperatorDefined(lang::UnaryOperator op) const override;
        lang::Type const&   getOperatorResultType(lang::UnaryOperator op) const override;
        bool                validateOperator(lang::UnaryOperator op,
                                             lang::Location      location,
                                             ValidationLogger&   validation_logger) const override;
        Shared<lang::Value> execOperator(lang::UnaryOperator op,
                                         Shared<lang::Value> value,
                                          Execution&          exec) const override;

        bool          hasMember(lang::Identifier const& name) const override;
        Member&       getMember(lang::Identifier const& name) override;
        Member const& getMember(lang::Identifier const& name) const override;
        bool validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const override;
        Shared<lang::Value> execMemberAccess(Shared<lang::Value>     value,
                                             lang::Identifier const& name,
                                              Execution&              exec) const override;

        bool                definesIndirection() const override;
        lang::Type const& getIndirectionType() const override;
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const override;
        Shared<lang::Value> execIndirection(Shared<lang::Value> value, Execution& exec) const override;

        bool isTriviallyDefaultConstructible() const override;
        bool isTriviallyCopyConstructible() const override;
        bool isTriviallyDestructible() const override;

        void createConstructors() override;
        void registerDeclaration(Execution& exec) const override;
        void registerDefinition(Execution& exec) const override;

        std::vector<lang::ResolvingHandle<lang::Type>> getDeclarationDependencies() override;
        std::vector<lang::ResolvingHandle<lang::Type>> getDefinitionDependencies() override;

        ~ReferenceType() override = default;

      private:
        lang::ResolvingHandle<lang::Type>           element_type_;
        Optional<lang::ResolvingHandle<lang::Type>> actual_type_ {};

      protected:
        std::string createMangledName() const override;
        void        registerExecutionType(Execution& exec) const override;

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
