#ifndef TREE_MODEL_H
#define TREE_MODEL_H

#include "tree/Definition.h"

#include <optional>
#include <set>
#include <string>
#include <vector>

namespace tree
{
    enum class MemberSemantics
    {
        VALUE_COPY,
        VALUE_MOVE,
        CONST_REFERENCE,
        MUTABLE_REFERENCE,
        CONST_POINTER,
        MUTABLE_POINTER
    };

    std::string formatParameter(
        std::string const& type,
        std::string const& name,
        MemberSemantics    semantics
    );
    std::string formatInitializer(
        std::string const& member_name,
        std::string const& parameter_name,
        MemberSemantics    semantics
    );
    std::string formatDeclaration(
        std::string const& type,
        std::string const& name,
        MemberSemantics    semantics
    );

    struct Member
    {
        std::string     name;
        std::string     type;
        MemberSemantics semantics;
    };

    struct Method
    {
        std::string signature;
        bool        is_pure_virtual = false;
    };

    struct Node
    {
        std::string                name;
        std::string                description;
        bool                       is_abstract = false;
        std::optional<std::size_t> base_node_index;
        std::vector<Member>        members;
        std::vector<Method>        methods;
    };

    struct Category
    {
        std::string              name;
        std::string              description;
        std::size_t              category_node_index;
        std::vector<std::size_t> child_node_indices;
    };

    struct Model
    {
        std::string              name;
        std::vector<Node>        nodes;
        std::vector<Category>    categories;
        std::vector<std::size_t> top_level_node_indices;
        std::set<std::string>    standard_includes;
        std::set<std::string>    project_includes;
        std::set<std::string>    external_forward_declarations;
    };

    Model buildModel(
        Definition::TreeBuilder const& builder,
        std::string const&             tree_name
    );
}

#endif
