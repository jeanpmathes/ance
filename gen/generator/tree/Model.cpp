#include "tree/Model.h"

#include "utility/Strings.h"

#include <stdexcept>
#include <utility>
#include <variant>

namespace
{
    tree::Member convertAttributeMember(
        tree::Definition::AttributeDefinition const& definition,
        tree::Model&                                 model
    )
    {
        switch (definition.type)
        {
            case tree::Definition::AttributeType::ACCESS_MODIFIER:
                model.project_includes.insert("ance/core/AccessModifier.h");
                return {
                    .name      = definition.name,
                    .type      = "core::AccessModifier",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::EXECUTION_MODIFIER:
                model.project_includes.insert("ance/core/ExecutionModifier.h");
                return {
                    .name      = definition.name,
                    .type      = "core::ExecutionModifier",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::IDENTIFIER:
                model.project_includes.insert("ance/core/Identifier.h");
                return {
                    .name      = definition.name,
                    .type      = "core::Identifier",
                    .semantics = tree::MemberSemantics::VALUE_MOVE
                };

            case tree::Definition::AttributeType::ASSIGNER:
                model.project_includes.insert("ance/core/Assigner.h");
                return {
                    .name      = definition.name,
                    .type      = "core::Assigner",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::LOCATION:
                model.project_includes.insert("ance/core/Location.h");
                return {
                    .name      = definition.name,
                    .type      = "core::Location",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::STRING:
                model.standard_includes.insert("<string>");
                return {
                    .name      = definition.name,
                    .type      = "std::string",
                    .semantics = tree::MemberSemantics::VALUE_MOVE
                };

            case tree::Definition::AttributeType::BOOL:
                return {
                    .name      = definition.name,
                    .type      = "bool",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::SIZE:
                model.standard_includes.insert("<cstddef>");
                return {
                    .name      = definition.name,
                    .type      = "std::size_t",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::PRECISION:
                model.project_includes.insert("ance/core/Precision.h");
                return {
                    .name      = definition.name,
                    .type      = "core::Precision",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::UNARY_OPERATOR:
                model.project_includes.insert("ance/core/UnaryOperator.h");
                return {
                    .name      = definition.name,
                    .type      = "core::UnaryOperator",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::BINARY_OPERATOR:
                model.project_includes.insert("ance/core/BinaryOperator.h");
                return {
                    .name      = definition.name,
                    .type      = "core::BinaryOperator",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::VARIABILITY_MODIFIER:
                model.project_includes.insert("ance/core/VariabilityModifier.h");
                return {
                    .name      = definition.name,
                    .type      = "core::VariabilityModifier",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::INTRINSIC:
                model.project_includes.insert("ance/core/Intrinsic.h");
                return {
                    .name      = definition.name,
                    .type      = "core::Intrinsic",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };

            case tree::Definition::AttributeType::OCCURRENCE:
                model.project_includes.insert("ance/core/Occurrence.h");
                return {
                    .name      = definition.name,
                    .type      = "core::Occurrence",
                    .semantics = tree::MemberSemantics::VALUE_COPY
                };
        }

        throw std::invalid_argument("Unknown attribute type");
    }

    tree::Member convertOwnedMember(
        tree::Definition::OwnedMemberDefinition const& definition,
        tree::Model&                                   model,
        std::set<std::string> const&                   all_node_names
    )
    {
        bool const is_child_node = all_node_names.contains(definition.type);
        if (!is_child_node)
        {
            model.external_forward_declarations.insert(definition.type);
        }

        model.project_includes.insert("ance/utility/Owners.h");
        std::string const owner =
            definition.shared ? "utility::Shared" : "utility::Owned";
        std::string full_type;

        switch (definition.multiplicity)
        {
            case tree::Definition::Multiplicity::ONE:
                full_type = owner + "<" + definition.type + ">";
                break;

            case tree::Definition::Multiplicity::ZERO_OR_ONE:
                model.project_includes.insert("ance/utility/Containers.h");
                full_type = "utility::Optional<" + owner + "<" + definition.type + ">>";
                break;

            case tree::Definition::Multiplicity::ZERO_OR_MORE:
                model.project_includes.insert("ance/utility/Containers.h");
                full_type = "utility::List<" + owner + "<" + definition.type + ">>";
                break;
        }

        return {
            .name                  = definition.name,
            .type                  = full_type,
            .semantics             = tree::MemberSemantics::VALUE_MOVE,
            .multiplicity          = definition.multiplicity,
            .is_owned_tree_element = is_child_node
        };
    }

    tree::Member convertReferenceMember(
        tree::Definition::ReferenceMemberDefinition const& definition,
        tree::Model&                                       model,
        std::set<std::string> const&                       all_node_names
    )
    {
        if (!all_node_names.contains(definition.type))
        {
            model.external_forward_declarations.insert(definition.type);
        }

        switch (definition.multiplicity)
        {
            case tree::Definition::Multiplicity::ONE:
                return {
                    .name         = definition.name,
                    .type         = definition.type,
                    .semantics    = definition.is_const
                                      ? tree::MemberSemantics::CONST_REFERENCE
                                      : tree::MemberSemantics::MUTABLE_REFERENCE,
                    .multiplicity = definition.multiplicity
                };

            case tree::Definition::Multiplicity::ZERO_OR_ONE:
                return {
                    .name         = definition.name,
                    .type         = definition.type,
                    .semantics    = definition.is_const
                                      ? tree::MemberSemantics::CONST_POINTER
                                      : tree::MemberSemantics::MUTABLE_POINTER,
                    .multiplicity = definition.multiplicity
                };

            case tree::Definition::Multiplicity::ZERO_OR_MORE:
                model.standard_includes.insert("<functional>");
                model.project_includes.insert("ance/utility/Containers.h");
                return {
                    .name = definition.name,
                    .type = "utility::List<std::reference_wrapper<" + definition.type
                          + (definition.is_const ? " const" : "") + ">>",
                    .semantics    = tree::MemberSemantics::VALUE_MOVE,
                    .multiplicity = definition.multiplicity
                };
        }

        throw std::invalid_argument("Unknown multiplicity");
    }

    std::vector<tree::Member> convertMembers(
        tree::Definition::NodeBuilder const& node_builder,
        tree::Model&                         model,
        std::set<std::string> const&         all_node_names
    )
    {
        std::vector<tree::Member> members;

        for (tree::Definition::MemberDefinition const& member_definition :
             node_builder.members)
        {
            std::visit(
                [&]<typename DefinitionType>(DefinitionType const& definition) {
                    using Type = std::decay_t<DefinitionType>;

                    if constexpr (std::is_same_v<
                                      Type,
                                      tree::Definition::AttributeDefinition>)
                    {
                        members.push_back(convertAttributeMember(definition, model));
                    }
                    else if constexpr (std::is_same_v<
                                           Type,
                                           tree::Definition::OwnedMemberDefinition>)
                    {
                        members.push_back(
                            convertOwnedMember(definition, model, all_node_names)
                        );
                    }
                    else if constexpr (std::is_same_v<
                                           Type,
                                           tree::Definition::ReferenceMemberDefinition>)
                    {
                        members.push_back(
                            convertReferenceMember(definition, model, all_node_names)
                        );
                    }
                },
                member_definition
            );
        }

        return members;
    }

    std::vector<tree::Method> convertMethods(
        std::vector<tree::Definition::MethodDefinition> const& method_definitions
    )
    {
        std::vector<tree::Method> methods;

        for (tree::Definition::MethodDefinition const& definition : method_definitions)
        {
            methods.push_back(
                {.signature       = definition.signature,
                 .is_pure_virtual = definition.is_pure_virtual}
            );
        }

        return methods;
    }
}

namespace tree
{
    std::string formatParameter(
        std::string const&    type,
        std::string const&    name,
        MemberSemantics const semantics
    )
    {
        switch (semantics)
        {
            case MemberSemantics::VALUE_COPY:
            case MemberSemantics::VALUE_MOVE:
                return type + " " + name;

            case MemberSemantics::CONST_REFERENCE:
                return type + " const& " + name;

            case MemberSemantics::MUTABLE_REFERENCE:
                return type + "& " + name;

            case MemberSemantics::CONST_POINTER:
                return type + " const* " + name;

            case MemberSemantics::MUTABLE_POINTER:
                return type + "* " + name;
        }

        return type + " " + name;
    }

    std::string formatInitializer(
        std::string const&    member_name,
        std::string const&    parameter_name,
        MemberSemantics const semantics
    )
    {
        if (semantics == MemberSemantics::VALUE_MOVE)
        {
            return member_name + "(std::move(" + parameter_name + "))";
        }

        return member_name + "(" + parameter_name + ")";
    }

    std::string formatDeclaration(
        std::string const&    type,
        std::string const&    name,
        MemberSemantics const semantics
    )
    {
        switch (semantics)
        {
            case MemberSemantics::VALUE_COPY:
            case MemberSemantics::VALUE_MOVE:
                return type + " " + name + ";";

            case MemberSemantics::CONST_REFERENCE:
                return type + " const& " + name + ";";

            case MemberSemantics::MUTABLE_REFERENCE:
                return type + "& " + name + ";";

            case MemberSemantics::CONST_POINTER:
                return type + " const* " + name + ";";

            case MemberSemantics::MUTABLE_POINTER:
                return type + "* " + name + ";";
        }

        return type + " " + name + ";";
    }

    Model buildModel(Definition::TreeBuilder const& builder, std::string const& tree_name)
    {
        Model model;
        model.name = tree_name;

        model.project_includes.insert("ance/core/Location.h");

        model.standard_includes.insert("<utility>");

        std::set<std::string> all_node_names = {"Node"};
        for (Definition::NodeBuilder const& node_builder : builder.nodes)
        {
            all_node_names.insert(node_builder.name);
        }
        for (Definition::CategoryBuilder const& category_builder : builder.categories)
        {
            all_node_names.insert(category_builder.name);
            for (Definition::NodeBuilder const& node_builder : category_builder.nodes)
            {
                all_node_names.insert(node_builder.name);
            }
        }

        model.nodes.push_back(
            {.name        = "Node",
             .description = "Base class for all nodes in the "
                          + utility::toUpperCase(tree_name) + " tree.",
             .is_abstract     = true,
             .base_node_index = std::nullopt,
             .members =
                 {{.name      = "location",
                   .type      = "core::Location",
                   .semantics = MemberSemantics::VALUE_COPY}},
             .methods = {}}
        );

        for (Definition::NodeBuilder const& node_builder : builder.nodes)
        {
            std::size_t const node_index = model.nodes.size();
            model.top_level_node_indices.push_back(node_index);

            model.nodes.push_back(
                {.name            = node_builder.name,
                 .description     = node_builder.description,
                 .is_abstract     = false,
                 .base_node_index = 0,
                 .members         = convertMembers(node_builder, model, all_node_names),
                 .methods         = convertMethods(node_builder.methods)}
            );
        }

        for (Definition::CategoryBuilder const& category_builder : builder.categories)
        {
            std::size_t const category_index = model.nodes.size();

            model.nodes.push_back(
                {.name            = category_builder.name,
                 .description     = category_builder.description,
                 .is_abstract     = true,
                 .base_node_index = 0,
                 .members         = {},
                 .methods         = convertMethods(category_builder.methods)}
            );

            std::vector<std::size_t> child_node_indices;

            for (Definition::NodeBuilder const& node_builder : category_builder.nodes)
            {
                std::size_t const child_index = model.nodes.size();
                child_node_indices.push_back(child_index);

                model.nodes.push_back(
                    {.name            = node_builder.name,
                     .description     = node_builder.description,
                     .is_abstract     = false,
                     .base_node_index = category_index,
                     .members = convertMembers(node_builder, model, all_node_names),
                     .methods = convertMethods(node_builder.methods)}
                );
            }

            model.categories.push_back(
                {.name                = category_builder.name,
                 .description         = category_builder.description,
                 .category_node_index = category_index,
                 .child_node_indices  = std::move(child_node_indices)}
            );
        }

        return model;
    }
}
