#include "Application.h"

#include <iostream>

#include "management/elements/Element.h"

#include "ance/scope/GlobalScope.h"

#include "ance/type/DoubleType.h"
#include "ance/type/HalfType.h"
#include "ance/type/QuadType.h"
#include "ance/type/SingleType.h"

#include "ance/type/SizeType.h"
#include "ance/type/UnsignedIntegerPointerType.h"
#include "ance/type/VoidType.h"

Application::Application(data::File& project) : project_(project), global_scope_(new ance::GlobalScope())
{
    // Register keyword types

    global_scope_->registerType(ance::HalfType::get());
    global_scope_->registerType(ance::SingleType::get());
    global_scope_->registerType(ance::DoubleType::get());
    global_scope_->registerType(ance::QuadType::get());

    global_scope_->registerType(ance::VoidType::get());
    global_scope_->registerType(ance::SizeType::getSize());
    global_scope_->registerType(ance::SizeType::getDiff());
    global_scope_->registerType(ance::UnsignedIntegerPointerType::get());

    addChild(*global_scope_);
}

ance::Location Application::location() const
{
    return ance::Location(0, 0, 0, 0);
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

    if (!src) return std::filesystem::path();

    for (auto src_file : src->get())
    {
        auto src_file_str = src_file.get().asString();

        if (!src_file_str) continue;

        std::filesystem::path path_to_src(src_file_str->get());
        std::filesystem::path path_to_project = getProjectFile();

        return path_to_project.replace_filename(path_to_src);
    }

    return std::filesystem::path();
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
        validation_logger.logError("Entry point 'ui32 main()' could not be found", ance::Location(0, 0, 0, 0));
    }

    if (!global_scope_->hasExit())
    {
        validation_logger.logError("Exit point 'void exit(ui32)' could not be found", ance::Location(0, 0, 0, 0));
    }
}

ance::GlobalScope* Application::globalScope()
{
    return global_scope_;
}

bool Application::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitApplication(*this);
}
