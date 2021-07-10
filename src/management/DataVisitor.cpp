#include "DataVisitor.h"

#include "Element.h"
#include "DictionaryElement.h"
#include "ListElement.h"
#include "StringElement.h"
#include "BooleanElement.h"

antlrcpp::Any DataVisitor::visitDictionary(dataParser::DictionaryContext* ctx)
{
	auto* element = new data::DictionaryElement();

	for (auto entry : ctx->entry())
	{
		std::pair<std::string, data::Element*> p = visit(entry);

		std::string key;
		data::Element* value;
		std::tie(key, value) = p;

		element->put(key, std::unique_ptr<data::Element>(value));
	}

	return static_cast<data::Element*>(element);
}

antlrcpp::Any DataVisitor::visitEntry(dataParser::EntryContext* ctx)
{
	std::string key = ctx->KEY()->getText();
	data::Element* value = visit(ctx->element());

	return std::make_pair(key, value);
}

antlrcpp::Any DataVisitor::visitList(dataParser::ListContext* ctx)
{
	auto* element = new data::ListElement();

	for (auto e : ctx->element())
	{
		data::Element* entry = visit(e);
		element->put(std::unique_ptr<data::Element>(entry));
	}

	return static_cast<data::Element*>(element);
}

antlrcpp::Any DataVisitor::visitString(dataParser::StringContext* ctx)
{
	std::string str_with_quotes = ctx->getText();
	std::string str = str_with_quotes.substr(1, str_with_quotes.size() - 2);

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