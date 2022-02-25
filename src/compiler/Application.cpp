#include "Application.h"

#include <iostream>

#include "management/elements/Element.h"

#include "lang/type/DoubleType.h"
#include "lang/type/HalfType.h"
#include "lang/type/QuadType.h"
#include "lang/type/SingleType.h"

#include "lang/type/ArrayType.h"
#include "lang/type/IntegerType.h"
#include "lang/type/PointerType.h"
#include "lang/type/ReferenceType.h"

#include "lang/type/SizeType.h"
#include "lang/type/UnsignedIntegerPointerType.h"
#include "lang/type/VoidType.h"
#include "management/File.h"
#include "validation/ValidationLogger.h"

Application::Application(data::File& project) : project_(project), global_scope_(std::make_unique<lang::GlobalScope>())
{
    // Register keyword types

    global_scope_->registerDefinition(lang::HalfType::get());
    global_scope_->registerDefinition(lang::SingleType::get());
    global_scope_->registerDefinition(lang::DoubleType::get());
    global_scope_->registerDefinition(lang::QuadType::get());

    global_scope_->registerDefinition(lang::VoidType::get());
    global_scope_->registerDefinition(lang::SizeType::getSize());
    global_scope_->registerDefinition(lang::SizeType::getDiff());
    global_scope_->registerDefinition(lang::UnsignedIntegerPointerType::get());

    // Add type registries

    global_scope_->addTypeRegistry(lang::IntegerType::getRegistry());
    global_scope_->addTypeRegistry(lang::ArrayType::getRegistry());
    global_scope_->addTypeRegistry(lang::PointerType::getRegistry());
    global_scope_->addTypeRegistry(lang::ReferenceType::getRegistry());

    // Add children

    addChild(globalScope());
}

void Application::setPointerSize(unsigned size)
{
    pointer_size_ = size;
}

std::string Application::getName() const
{
    auto name = project_.root()["name"];

    if (name)
    {
        auto str = name->get().asString();

        if (str) { return str->get(); }
    }

    return "unnamed";
}

std::filesystem::path Application::getProjectFile() const
{
    return project_.path();
}

std::filesystem::path Application::getSourceFile() const
{
    auto src = project_.root()["src"];

    if (!src) return {};

    for (auto src_file : src->get())
    {
        auto src_file_str = src_file.get().asString();

        if (!src_file_str) continue;

        std::filesystem::path path_to_src(src_file_str->get());
        std::filesystem::path path_to_project = getProjectFile();

        return path_to_project.replace_filename(path_to_src);
    }

    return {};
}

unsigned Application::getBitness() const
{
    return pointer_size_ * 8;
}

void Application::validate(ValidationLogger& validation_logger)
{
    global_scope_->validate(validation_logger);

    if (!global_scope_->hasEntry())
    {
        validation_logger.logError("Entry point 'ui32 main()' could not be found", lang::Location(0, 0, 0, 0));
    }

    if (!global_scope_->hasExit())
    {
        validation_logger.logError("Exit point 'void exit(ui32)' could not be found", lang::Location(0, 0, 0, 0));
    }
}

lang::GlobalScope& Application::globalScope()
{
    return *global_scope_;
}
