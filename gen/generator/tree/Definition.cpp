#include "tree/Definition.h"

#include "tree/Emitter.h"
#include "tree/Model.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <utility>

namespace
{
    void writeIfDifferent(
        std::filesystem::path const& file_path,
        std::string const&           content
    )
    {
        std::ifstream input_file(file_path);
        if (input_file.is_open())
        {
            std::string const existing_content(
                (std::istreambuf_iterator(input_file)),
                std::istreambuf_iterator<char>()
            );

            if (existing_content == content)
            {
                return;
            }
        }

        std::ofstream output_file(file_path, std::ios::trunc);
        if (!output_file.is_open())
        {
            throw std::runtime_error(
                "Could not open file for writing: " + file_path.string()
            );
        }

        output_file << content;
    }
}

namespace tree
{
    Definition::TreeBuilder& Definition::TreeBuilder::category(
        std::string const&                           category_name,
        std::string const&                           category_description,
        std::function<void(CategoryBuilder&)> const& builder
    )
    {
        CategoryBuilder category_builder {
            .name        = category_name,
            .description = category_description
        };

        builder(category_builder);

        categories.emplace_back(std::move(category_builder));

        return *this;
    }

    Definition::TreeBuilder& Definition::TreeBuilder::node(
        std::string const&                       node_name,
        std::string const&                       node_description,
        std::function<void(NodeBuilder&)> const& builder
    )
    {
        NodeBuilder node_builder {.name = node_name, .description = node_description};

        builder(node_builder);

        nodes.emplace_back(std::move(node_builder));

        return *this;
    }

    Definition::CategoryBuilder& Definition::CategoryBuilder::node(
        std::string const&                       node_name,
        std::string const&                       node_description,
        std::function<void(NodeBuilder&)> const& builder
    )
    {
        NodeBuilder node_builder {.name = node_name, .description = node_description};

        builder(node_builder);

        nodes.emplace_back(std::move(node_builder));

        return *this;
    }

    Definition::CategoryBuilder& Definition::CategoryBuilder::method(
        std::string const& signature,
        bool const         is_pure_virtual
    )
    {
        methods.push_back({.signature = signature, .is_pure_virtual = is_pure_virtual});

        return *this;
    }

    Definition::NodeBuilder& Definition::NodeBuilder::attribute(
        AttributeType const attribute_type,
        std::string const&  attribute_name
    )
    {
        members.emplace_back(
            AttributeDefinition {.type = attribute_type, .name = attribute_name}
        );

        return *this;
    }

    Definition::NodeBuilder& Definition::NodeBuilder::owned(
        std::string const& owned_type,
        std::string const& owned_name,
        Multiplicity const multiplicity,
        bool const         shared
    )
    {
        members.emplace_back(
            OwnedMemberDefinition {
                .type         = owned_type,
                .name         = owned_name,
                .multiplicity = multiplicity,
                .shared       = shared
            }
        );

        return *this;
    }

    Definition::NodeBuilder& Definition::NodeBuilder::container(
        std::string const& container_type,
        std::string const& container_name,
        Multiplicity const multiplicity,
        bool const         shared
    )
    {
        return owned(container_type, container_name, multiplicity, shared);
    }

    Definition::NodeBuilder& Definition::NodeBuilder::reference(
        std::string const& reference_type,
        std::string const& reference_name,
        Multiplicity const multiplicity,
        bool const         is_const
    )
    {
        members.emplace_back(
            ReferenceMemberDefinition {
                .type         = reference_type,
                .name         = reference_name,
                .multiplicity = multiplicity,
                .is_const     = is_const
            }
        );

        return *this;
    }

    Definition::NodeBuilder& Definition::NodeBuilder::method(std::string const& signature)
    {
        methods.push_back({.signature = signature, .is_pure_virtual = false});

        return *this;
    }

    Definition::Definition(TreeBuilder const& builder) : builder_(builder)
    {
        std::filesystem::path const source_file = builder.location.file_name();

        name_      = source_file.stem().string();
        directory_ = std::filesystem::path("ance") / name_;
    }

    Definition::TreeBuilder Definition::create(std::source_location const& location)
    {
        return {.location = location};
    }

    void Definition::generate(std::filesystem::path const& output_root) const
    {
        Model const model = buildModel(builder_, name_);

        std::filesystem::path const output_directory = output_root / directory_;
        std::filesystem::create_directories(output_directory);

        std::filesystem::path const header_path = output_directory / "Node.h";
        writeIfDifferent(header_path, generateHeader(model));

        std::string const header_include = (directory_ / "Node.h").generic_string();
        std::filesystem::path const source_path = output_directory / "Node.generated.cpp";
        writeIfDifferent(source_path, generateSource(model, header_include));
    }
}
