#include "DataVisitor.h"

#include "management/elements/BooleanElement.h"
#include "management/elements/DictionaryElement.h"
#include "management/elements/ListElement.h"
#include "management/elements/StringElement.h"

antlrcpp::Any DataVisitor::visitDictionary(dataParser::DictionaryContext* ctx)
{
    auto* element = new data::DictionaryElement();

    for (auto entry : ctx->entry())
    {
        auto p = std::any_cast<std::pair<std::string, data::Element*>>(visit(entry));

        std::string    key;
        data::Element* value;
        std::tie(key, value) = p;

        element->put(key, std::unique_ptr<data::Element>(value));
    }

    return static_cast<data::Element*>(element);
}

antlrcpp::Any DataVisitor::visitEntry(dataParser::EntryContext* ctx)
{
    std::string key   = ctx->KEY()->getText();
    auto*       value = std::any_cast<data::Element*>(visit(ctx->element()));

    return std::make_pair(key, value);
}

antlrcpp::Any DataVisitor::visitList(dataParser::ListContext* ctx)
{
    auto* element = new data::ListElement();

    for (auto e : ctx->element())
    {
        auto* entry = any_cast<data::Element*>(visit(e));
        element->put(std::unique_ptr<data::Element>(entry));
    }

    return static_cast<data::Element*>(element);
}

antlrcpp::Any DataVisitor::visitString(dataParser::StringContext* ctx)
{
    std::string raw_string = ctx->getText();
    std::string str;

    bool escaped = false;

    for (size_t i = 1; i < raw_string.length() - 1; ++i)
    {
        char c = raw_string[i];

        if (!escaped && c == '\\') { escaped = true; }
        else
        {
            str.push_back(c);
            escaped = false;
        }
    }

    auto* element = new data::StringElement(str);
    return static_cast<data::Element*>(element);
}

antlrcpp::Any DataVisitor::visitTrue(dataParser::TrueContext*)
{
    return static_cast<data::Element*>(new data::BooleanElement(true));
}

antlrcpp::Any DataVisitor::visitFalse(dataParser::FalseContext*)
{
    return static_cast<data::Element*>(new data::BooleanElement(false));
}
