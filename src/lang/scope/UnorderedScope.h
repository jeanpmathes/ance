#ifndef ANCE_SRC_LANG_SCOPE_UNORDEREDSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_UNORDEREDSCOPE_H_

#include "Scope.h"

#include <map>
#include <optional>
#include <ranges>
#include <vector>

#include "lang/utility/Identifier.h"

class ConstantExpression;
class Storage;

namespace lang
{
    class Description;
}

namespace lang
{
    /**
     * A scope in which the order of definitions does not matter.
     * Redefinitions of names are not allowed.
     */
    class UnorderedScope : public virtual Scope
    {
      public:
        [[nodiscard]] bool isNameConflicted(lang::Identifier const& name) const override;

        void addDescription(Owned<lang::Description> description) override;
        void addFunction(lang::OwningHandle<lang::Function> function) override;
        void addVariable(lang::OwningHandle<lang::Variable> variable) override;
        void addType(lang::OwningHandle<lang::Type> type) override;

        /**
         * Get a type defined in this scope by it's name.
         * @param string The name of the type.
         * @return The type, or nothing if no such type is defined.
         */
        Optional<lang::ResolvingHandle<lang::Type>> getType(Identifier string);

        /**
         * Validate the descriptions in this scope. In contrast to an ordered scope, the unordered scope owns the contained descriptions, which is why it validates them.
         * @param validation_logger The logger to log errors to.
         */
        void validate(ValidationLogger& validation_logger) const;

        void registerUsage(lang::ResolvingHandle<lang::Variable> variable) override;
        void registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        void registerUsage(lang::ResolvingHandle<lang::Type> type) override;

        void registerDefinition(lang::ResolvingHandle<lang::Type> type) override;

        void resolve() override;
        void postResolve() override;

        bool resolveDefinition(lang::ResolvingHandle<lang::Variable> variable) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::Type> type) override;

        /**
         * Build all initialization required by global entities.
         * @param context The current compile context.
         */
        void buildInitialization(CompileContext& context);
        void buildFinalization(CompileContext& context) override;

      protected:
        virtual void onResolve() {}
        virtual void onPostResolve() {}

        struct AssociatedDescription {
            Optional<std::string>    source;
            Owned<lang::Description> description;

            AssociatedDescription(Optional<std::string> new_source, Owned<lang::Description> new_description)
                : source(std::move(new_source))
                , description(std::move(new_description))
            {}
        };

        [[nodiscard]] std::map<lang::Identifier, std::vector<AssociatedDescription>>&       getCompatibleDescriptions();
        [[nodiscard]] std::map<lang::Identifier, std::vector<AssociatedDescription>> const& getCompatibleDescriptions()
            const;

        [[nodiscard]] auto getFunctionGroups() { return defined_function_groups_ | std::views::values; }
        [[nodiscard]] auto getFunctionGroups() const { return defined_function_groups_ | std::views::values; }

        [[nodiscard]] auto getVariables() { return global_defined_variables_ | std::views::values; }
        [[nodiscard]] auto getVariables() const { return global_defined_variables_ | std::views::values; }

        [[nodiscard]] auto getTypes() { return defined_types_ | std::views::values; }
        [[nodiscard]] auto getTypes() const { return defined_types_ | std::views::values; }

      private:
        lang::ResolvingHandle<lang::FunctionGroup> prepareDefinedFunctionGroup(Identifier name);

      private:
        std::map<lang::Identifier, std::vector<AssociatedDescription>> compatible_descriptions_;
        std::map<lang::Identifier, std::vector<AssociatedDescription>> incompatible_descriptions_;

        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> undefined_function_groups_;
        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> defined_function_groups_;

        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>> global_undefined_variables_;
        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>> global_defined_variables_;

        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> undefined_types_;
        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> defined_types_;

        std::set<lang::Identifier> defined_names_;
    };
}

#endif
