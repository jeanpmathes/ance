#include "tree/Emitter.h"

#include "utility/Strings.h"

#include <sstream>
#include <vector>

namespace
{
    std::string formatNodeParameterName(std::string const& node_name)
    {
        return "node_" + utility::toSnakeCase(node_name);
    }

    void emitDocumentation(
        std::ostream&      stream,
        std::string const& description,
        std::string const& indent
    )
    {
        if (description.empty())
        {
            return;
        }

        std::istringstream lines(description);
        std::string        line;

        while (std::getline(lines, line))
        {
            stream << indent << "/// " << line << "\n";
        }
    }

    std::vector<std::string> getVisitorTemplateParameterNames(tree::Model const& model)
    {
        std::vector<std::string> names;

        for (tree::Category const& category : model.categories)
        {
            names.push_back(category.name + "Result");
        }

        for (std::size_t const index : model.top_level_node_indices)
        {
            names.push_back(model.nodes[index].name + "Result");
        }

        return names;
    }

    void emitHeaderIncludeGuardOpen(std::ostream& stream, std::string const& tree_name)
    {
        std::string const guard = "ANCE_" + utility::toUpperCase(tree_name) + "_NODE_H";

        stream << "#ifndef " << guard << "\n";
        stream << "#define " << guard << "\n\n";
    }

    void emitStandardIncludes(
        std::ostream&                stream,
        std::set<std::string> const& standard_includes
    )
    {
        for (std::string const& include : standard_includes)
        {
            stream << "#include " << include << "\n";
        }

        if (!standard_includes.empty())
        {
            stream << "\n";
        }
    }

    void emitProjectIncludes(
        std::ostream&                stream,
        std::set<std::string> const& project_includes
    )
    {
        for (std::string const& include : project_includes)
        {
            stream << "#include \"" << include << "\"\n";
        }

        if (!project_includes.empty())
        {
            stream << "\n";
        }
    }

    void emitVisitorForwardDeclaration(
        std::ostream&                   stream,
        std::vector<std::string> const& visitor_template_names
    )
    {
        if (!visitor_template_names.empty())
        {
            stream << "    template<\n";
            for (std::size_t index = 0; index < visitor_template_names.size(); ++index)
            {
                stream << "        typename " << visitor_template_names[index]
                       << " = void";
                if (index + 1 < visitor_template_names.size())
                {
                    stream << ",";
                }
                stream << "\n";
            }
            stream << "    >\n";
        }
        stream << "    class Visitor;\n\n";

        if (visitor_template_names.empty())
        {
            stream << "    using DefaultVisitor = Visitor;\n\n";
        }
        else
        {
            stream << "    using DefaultVisitor = Visitor<>;\n\n";
        }
    }

    void emitNodeForwardDeclarations(
        std::ostream&                  stream,
        std::vector<tree::Node> const& nodes,
        std::set<std::string> const&   external_forward_declarations
    )
    {
        for (std::string const& external_type : external_forward_declarations)
        {
            stream << "    class " << external_type << ";\n";
        }
        if (!external_forward_declarations.empty())
        {
            stream << "\n";
        }

        stream << "    struct Node;\n";
        for (std::size_t index = 1; index < nodes.size(); ++index)
        {
            stream << "    struct " << nodes[index].name << ";\n";
        }
        stream << "\n";
    }

    void emitRootNodeDeclaration(std::ostream& stream, tree::Node const& root_node)
    {
        emitDocumentation(stream, root_node.description, "    ");
        stream << "    struct Node\n";
        stream << "    {\n";
        stream << "        explicit Node(core::Location const& source_location);\n";
        stream << "        virtual ~Node() = default;\n\n";
        stream << "        core::Location location;\n\n";
        stream << "      protected:\n";
        stream << "        Node() : location(core::Location::nowhere()) {}\n";
        stream << "    };\n\n";
    }

    void emitNodeConstructorDeclaration(
        std::ostream&                    stream,
        std::string const&               node_name,
        std::vector<tree::Member> const& members
    )
    {
        if (members.empty())
        {
            stream << "        explicit " << node_name
                   << "(core::Location const& source_location);\n";
        }
        else
        {
            stream << "        " << node_name << "(\n";
            for (tree::Member const& member : members)
            {
                std::string const parameter_name = "initial_" + member.name;
                stream << "            "
                       << tree::formatParameter(
                              member.type,
                              parameter_name,
                              member.semantics
                          )
                       << ",\n";
            }
            stream << "            core::Location const& source_location\n";
            stream << "        );\n";
        }
    }

    void emitNodeMembersAndMethods(
        std::ostream&                    stream,
        std::vector<tree::Member> const& members,
        std::vector<tree::Method> const& methods
    )
    {
        if (!members.empty() || !methods.empty())
        {
            stream << "\n";
        }

        for (tree::Member const& member : members)
        {
            stream << "        "
                   << tree::formatDeclaration(member.type, member.name, member.semantics)
                   << "\n";
        }

        for (tree::Method const& method : methods)
        {
            stream << "        " << method.signature << ";\n";
        }
    }

    void emitTopLevelNodeDeclarations(std::ostream& stream, tree::Model const& model)
    {
        for (std::size_t const index : model.top_level_node_indices)
        {
            tree::Node const& node = model.nodes[index];

            emitDocumentation(stream, node.description, "    ");
            stream << "    struct " << node.name << " final : Node\n";
            stream << "    {\n";
            emitNodeConstructorDeclaration(stream, node.name, node.members);
            emitNodeMembersAndMethods(stream, node.members, node.methods);
            stream << "    };\n\n";
        }
    }

    void emitCategoryKindEnum(
        std::ostream&                  stream,
        tree::Category const&          category,
        std::vector<tree::Node> const& nodes
    )
    {
        stream << "        enum class Kind\n";
        stream << "        {\n";
        for (std::size_t child_index = 0;
             child_index < category.child_node_indices.size();
             ++child_index)
        {
            tree::Node const& child_node =
                nodes[category.child_node_indices[child_index]];
            stream << "            "
                   << utility::toUpperCase(utility::toSnakeCase(child_node.name));
            if (child_index + 1 < category.child_node_indices.size())
            {
                stream << ",";
            }
            stream << "\n";
        }
        stream << "        };\n\n";
    }

    void emitCategoryMethods(
        std::ostream&                    stream,
        std::vector<tree::Method> const& methods
    )
    {
        if (methods.empty())
        {
            return;
        }

        stream << "\n";
        for (tree::Method const& method : methods)
        {
            stream << "        " << method.signature;
            if (method.is_pure_virtual)
            {
                stream << " = 0";
            }
            stream << ";\n";
        }
    }

    void emitCategoryConstructor(std::ostream& stream, std::string const& category_name)
    {
        stream << "\n      protected:\n";
        stream << "        explicit " << category_name
               << "(Kind const kind) : kind_(kind) {}\n\n";
        stream << "      private:\n";
        stream << "        Kind kind_;\n";
    }

    void emitCategoryDeclaration(
        std::ostream&         stream,
        tree::Category const& category,
        tree::Model const&    model
    )
    {
        tree::Node const& category_node = model.nodes[category.category_node_index];

        emitDocumentation(stream, category_node.description, "    ");
        stream << "    struct " << category.name << " : virtual Node\n";
        stream << "    {\n";

        emitCategoryKindEnum(stream, category, model.nodes);
        stream << "        ~" << category.name << "() override = default;\n\n";
        stream << "        [[nodiscard]] Kind kind() const noexcept { return kind_; }\n";

        emitCategoryMethods(stream, category_node.methods);
        emitCategoryConstructor(stream, category.name);

        stream << "    };\n\n";
    }

    void emitCategoryChildNodeDeclaration(
        std::ostream&      stream,
        tree::Node const&  node,
        std::string const& category_name
    )
    {
        emitDocumentation(stream, node.description, "    ");
        stream << "    struct " << node.name << " final : " << category_name << "\n";
        stream << "    {\n";
        emitNodeConstructorDeclaration(stream, node.name, node.members);
        emitNodeMembersAndMethods(stream, node.members, node.methods);
        stream << "    };\n\n";
    }

    void emitCategoryDeclarations(std::ostream& stream, tree::Model const& model)
    {
        for (tree::Category const& category : model.categories)
        {
            emitCategoryDeclaration(stream, category, model);

            for (std::size_t const child_index : category.child_node_indices)
            {
                emitCategoryChildNodeDeclaration(
                    stream,
                    model.nodes[child_index],
                    category.name
                );
            }
        }
    }

    void emitVisitorCategoryPureVirtuals(std::ostream& stream, tree::Model const& model)
    {
        for (tree::Category const& category : model.categories)
        {
            std::string const result_type = category.name + "Result";

            for (std::size_t const child_index : category.child_node_indices)
            {
                tree::Node const& node           = model.nodes[child_index];
                std::string const parameter_name = formatNodeParameterName(node.name);

                stream << "        virtual " << result_type << " visit(" << node.name
                       << " const& " << parameter_name << ") = 0;\n";
            }

            stream << "\n";
        }
    }

    void emitVisitorTopLevelPureVirtuals(std::ostream& stream, tree::Model const& model)
    {
        for (std::size_t const index : model.top_level_node_indices)
        {
            tree::Node const& node           = model.nodes[index];
            std::string const result_type    = node.name + "Result";
            std::string const parameter_name = formatNodeParameterName(node.name);

            stream << "        virtual " << result_type << " visit(" << node.name
                   << " const& " << parameter_name << ") = 0;\n";
        }

        if (!model.top_level_node_indices.empty())
        {
            stream << "\n";
        }
    }

    void emitVisitorCategoryDispatch(
        std::ostream&         stream,
        tree::Category const& category,
        tree::Model const&    model
    )
    {
        std::string const result_type    = category.name + "Result";
        std::string const parameter_name = formatNodeParameterName(category.name);

        stream << "        virtual " << result_type << " visit(" << category.name
               << " const& " << parameter_name << ")\n";
        stream << "        {\n";
        stream << "            switch (" << parameter_name << ".kind())\n";
        stream << "            {\n";

        for (std::size_t const child_index : category.child_node_indices)
        {
            tree::Node const& child_node = model.nodes[child_index];
            stream << "                case " << category.name << "::Kind::"
                   << utility::toUpperCase(utility::toSnakeCase(child_node.name))
                   << ":\n";
            stream << "                    return visit(static_cast<" << child_node.name
                   << " const&>(" << parameter_name << "));\n";
        }

        stream << "            }\n";
        stream << "            std::unreachable();\n";
        stream << "        }\n\n";
    }

    void emitVisitorCategoryDispatches(std::ostream& stream, tree::Model const& model)
    {
        for (tree::Category const& category : model.categories)
        {
            emitVisitorCategoryDispatch(stream, category, model);
        }
    }

    void emitVisitorClass(
        std::ostream&                   stream,
        tree::Model const&              model,
        std::vector<std::string> const& visitor_template_names
    )
    {
        if (!visitor_template_names.empty())
        {
            stream << "    template<\n";
            for (std::size_t index = 0; index < visitor_template_names.size(); ++index)
            {
                stream << "        typename " << visitor_template_names[index];
                if (index + 1 < visitor_template_names.size())
                {
                    stream << ",";
                }
                stream << "\n";
            }
            stream << "    >\n";
        }

        stream << "    class Visitor\n";
        stream << "    {\n";
        stream << "      public:\n";
        stream << "        virtual ~Visitor() = default;\n\n";

        emitVisitorCategoryPureVirtuals(stream, model);
        emitVisitorTopLevelPureVirtuals(stream, model);
        emitVisitorCategoryDispatches(stream, model);

        stream << "    };\n";
    }

    void emitHeaderIncludeGuardClose(std::ostream& stream)
    {
        stream << "}\n\n";
        stream << "#endif\n";
    }

    void emitRootNodeConstructor(std::ostream& stream)
    {
        stream << "    Node::Node(core::Location const& source_location) : "
                  "location(source_location) {}\n\n";
    }

    void emitTopLevelNodeConstructors(std::ostream& stream, tree::Model const& model)
    {
        for (std::size_t const index : model.top_level_node_indices)
        {
            tree::Node const& node = model.nodes[index];

            if (node.members.empty())
            {
                stream << "    " << node.name << "::" << node.name
                       << "(core::Location const& source_location)\n";
                stream << "        : Node(source_location)\n";
                stream << "    {}\n\n";
            }
            else
            {
                stream << "    " << node.name << "::" << node.name << "(\n";
                for (tree::Member const& member : node.members)
                {
                    std::string const parameter_name = "initial_" + member.name;
                    stream << "        "
                           << tree::formatParameter(
                                  member.type,
                                  parameter_name,
                                  member.semantics
                              )
                           << ",\n";
                }
                stream << "        core::Location const& source_location\n";
                stream << "    )\n";
                stream << "        : Node(source_location)\n";
                for (tree::Member const& member : node.members)
                {
                    std::string const parameter_name = "initial_" + member.name;
                    stream << "        , "
                           << tree::formatInitializer(
                                  member.name,
                                  parameter_name,
                                  member.semantics
                              )
                           << "\n";
                }
                stream << "    {}\n\n";
            }
        }
    }

    void emitCategoryNodeConstructors(std::ostream& stream, tree::Model const& model)
    {
        for (tree::Category const& category : model.categories)
        {
            for (std::size_t const child_index : category.child_node_indices)
            {
                tree::Node const& node = model.nodes[child_index];

                std::string const kind_enumerator =
                    category.name
                    + "::Kind::" + utility::toUpperCase(utility::toSnakeCase(node.name));

                if (node.members.empty())
                {
                    stream << "    " << node.name << "::" << node.name
                           << "(core::Location const& source_location)\n";
                    stream << "        : Node(source_location)\n";
                    stream << "        , " << category.name << "(" << kind_enumerator
                           << ")\n";
                    stream << "    {}\n\n";
                }
                else
                {
                    stream << "    " << node.name << "::" << node.name << "(\n";
                    for (tree::Member const& member : node.members)
                    {
                        std::string const parameter_name = "initial_" + member.name;
                        stream << "        "
                               << tree::formatParameter(
                                      member.type,
                                      parameter_name,
                                      member.semantics
                                  )
                               << ",\n";
                    }
                    stream << "        core::Location const& source_location\n";
                    stream << "    )\n";
                    stream << "        : Node(source_location)\n";
                    stream << "        , " << category.name << "(" << kind_enumerator
                           << ")\n";
                    for (tree::Member const& member : node.members)
                    {
                        std::string const parameter_name = "initial_" + member.name;
                        stream << "        , "
                               << tree::formatInitializer(
                                      member.name,
                                      parameter_name,
                                      member.semantics
                                  )
                               << "\n";
                    }
                    stream << "    {}\n\n";
                }
            }
        }
    }

    void emitCustomInclusionHook(std::ostream& stream, std::string const& tree_name)
    {
        stream << "#if __has_include(\"ance/" << tree_name << "/Node.inc\")\n";
        stream << "#include \"ance/" << tree_name << "/Node.inc\"\n";
        stream << "#endif\n";
    }
}

namespace tree
{
    std::string generateHeader(Model const& model)
    {
        std::ostringstream stream;

        emitHeaderIncludeGuardOpen(stream, model.name);
        emitStandardIncludes(stream, model.standard_includes);
        emitProjectIncludes(stream, model.project_includes);

        stream << "namespace ance::" << model.name << "\n";
        stream << "{\n";

        std::vector<std::string> const visitor_template_names =
            getVisitorTemplateParameterNames(model);

        emitVisitorForwardDeclaration(stream, visitor_template_names);
        emitNodeForwardDeclarations(
            stream,
            model.nodes,
            model.external_forward_declarations
        );
        emitRootNodeDeclaration(stream, model.nodes[0]);
        emitTopLevelNodeDeclarations(stream, model);
        emitCategoryDeclarations(stream, model);
        emitVisitorClass(stream, model, visitor_template_names);

        emitHeaderIncludeGuardClose(stream);

        return stream.str();
    }

    std::string generateSource(Model const& model, std::string const& include_path)
    {
        std::ostringstream stream;

        stream << "#include \"" << include_path << "\"\n\n";
        stream << "namespace ance::" << model.name << "\n";
        stream << "{\n";

        emitRootNodeConstructor(stream);
        emitTopLevelNodeConstructors(stream, model);
        emitCategoryNodeConstructors(stream, model);

        stream << "}\n\n";

        emitCustomInclusionHook(stream, model.name);

        return stream.str();
    }
}
