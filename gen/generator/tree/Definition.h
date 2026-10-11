#ifndef TREE_DEFINITION_H
#define TREE_DEFINITION_H

#include "../Definition.h"

#include <filesystem>
#include <functional>
#include <source_location>
#include <string>
#include <variant>
#include <vector>

namespace tree
{
    /// Defines a node tree.
    class Definition : public ::Definition
    {
      public:
        struct CategoryBuilder;
        struct NodeBuilder;

        struct
            TreeBuilder // todo: maybe there is a nicer way to write the builder and design the API
        {
            std::source_location location;

            std::vector<CategoryBuilder> categories = {};
            std::vector<NodeBuilder>     nodes      = {};

            TreeBuilder& category(
                std::string const&                           category_name,
                std::string const&                           category_description,
                std::function<void(CategoryBuilder&)> const& builder
            );
            TreeBuilder& node(
                std::string const&                       node_name,
                std::string const&                       node_description,
                std::function<void(NodeBuilder&)> const& builder
            );
        };

        struct MethodDefinition
        {
            std::string signature;
            bool        is_pure_virtual = false;
        };

        struct CategoryBuilder
        {
            std::string name;
            std::string description;

            std::vector<NodeBuilder>      nodes   = {};
            std::vector<MethodDefinition> methods = {};

            CategoryBuilder& node(
                std::string const&                       node_name,
                std::string const&                       node_description,
                std::function<void(NodeBuilder&)> const& builder
            );
            CategoryBuilder& method(
                std::string const& signature,
                bool               is_pure_virtual = false
            );
        };

        enum class AttributeType
        {
            ACCESS_MODIFIER,
            EXECUTION_MODIFIER,
            IDENTIFIER,
            ASSIGNER,
            LOCATION,
            STRING,
            BOOL,
            SIZE,
            PRECISION,
            UNARY_OPERATOR,
            BINARY_OPERATOR,
            VARIABILITY_MODIFIER,
            INTRINSIC,
            OCCURRENCE
        };

        enum class Multiplicity
        {
            ONE,
            ZERO_OR_ONE,
            ZERO_OR_MORE
        };

        struct AttributeDefinition
        {
            AttributeType type;
            std::string   name;
        };

        struct OwnedMemberDefinition
        {
            std::string  type;
            std::string  name;
            Multiplicity multiplicity = Multiplicity::ONE;
            bool         shared       = false;
        };

        using ContainerMemberDefinition = OwnedMemberDefinition;

        struct ReferenceMemberDefinition
        {
            std::string  type;
            std::string  name;
            Multiplicity multiplicity = Multiplicity::ONE;
            bool         is_const     = true;
        };

        using MemberDefinition = std::variant<
            AttributeDefinition,
            OwnedMemberDefinition,
            ReferenceMemberDefinition>;

        struct NodeBuilder
        {
            std::string name;
            std::string description;

            std::vector<MemberDefinition> members = {};
            std::vector<MethodDefinition> methods = {};

            NodeBuilder& attribute(
                AttributeType      attribute_type,
                std::string const& attribute_name
            );
            NodeBuilder& owned(
                std::string const& owned_type,
                std::string const& owned_name,
                Multiplicity       multiplicity = Multiplicity::ONE,
                bool               shared       = false
            );
            NodeBuilder& container(
                std::string const& container_type,
                std::string const& container_name,
                Multiplicity       multiplicity = Multiplicity::ONE,
                bool               shared       = false
            );
            NodeBuilder& reference(
                std::string const& reference_type,
                std::string const& reference_name,
                Multiplicity       multiplicity = Multiplicity::ONE,
                bool               is_const     = true
            );
            NodeBuilder& method(std::string const& signature);
        };

        explicit(false) Definition(TreeBuilder const& builder);

        static TreeBuilder create(
            std::source_location const& location = std::source_location::current()
        );

        void generate(std::filesystem::path const& output_root) const override;

      private:
        std::string           name_;
        std::filesystem::path directory_;

        TreeBuilder builder_;
    };
}

#endif
