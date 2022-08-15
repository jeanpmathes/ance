#include "Application.h"

#include <iostream>
#include <fstream>

#include "management/elements/Element.h"
#include "management/File.h"
#include "validation/ValidationLogger.h"
#include "compiler/Project.h"
#include "compiler/CodePrinter.h"

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
#include "lang/type/BooleanType.h"

Application::Application(Project& project) : Application(project, std::make_unique<lang::GlobalScope>())
{
    // Register keyword types

    global_scope_->registerDefinition(lang::HalfType::get());
    global_scope_->registerDefinition(lang::SingleType::get());
    global_scope_->registerDefinition(lang::DoubleType::get());
    global_scope_->registerDefinition(lang::QuadType::get());

    global_scope_->registerDefinition(lang::VoidType::get());
    global_scope_->registerDefinition(lang::BooleanType::get());
    global_scope_->registerDefinition(lang::SizeType::getSize());
    global_scope_->registerDefinition(lang::SizeType::getDiff());
    global_scope_->registerDefinition(lang::UnsignedIntegerPointerType::get());

    // Add type registries

    global_scope_->addTypeRegistry(lang::IntegerType::getRegistry());
    global_scope_->addTypeRegistry(lang::ArrayType::getRegistry());
    global_scope_->addTypeRegistry(lang::PointerType::getRegistry());
    global_scope_->addTypeRegistry(lang::ReferenceType::getRegistry());
}

Application::Application(Project& project, std::unique_ptr<lang::GlobalScope>&& scope)
    : project_(project)
    , global_scope_(std::move(scope))
{
    addChild(globalScope());
}

void Application::setPointerSize(unsigned size)
{
    pointer_size_ = size;
}

Project& Application::getProject() const
{
    return project_;
}

unsigned Application::getBitness() const
{
    return pointer_size_ * 8;
}

void Application::preValidate()
{
    global_scope_->resolve();
    global_scope_->postResolve();
}

void Application::validate(ValidationLogger& validation_logger) const
{
    global_scope_->validate(validation_logger);

    if (!global_scope_->hasEntry())
    {
        validation_logger.logError("Entry point 'ui32 main()' could not be found", lang::Location::global());
    }

    if (!global_scope_->hasExit())
    {
        validation_logger.logError("Exit point 'void exit(ui32)' could not be found", lang::Location::global());
    }
}

void Application::preBuild()
{
    global_scope_->expand();
    global_scope_->resolve();
    global_scope_->postResolve();
    global_scope_->determineFlow();
}

void Application::emitAsSource(std::filesystem::path out)
{
    std::ofstream of;
    of.open(out);

    std::ostream o(of.rdbuf());

    CodePrinter printer(o);
    printer.visit(*this);
}

void Application::validateFlow(ValidationLogger& validation_logger) const
{
    global_scope_->validateFlow(validation_logger);
}

lang::GlobalScope& Application::globalScope()
{
    return *global_scope_;
}
