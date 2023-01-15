#include "Unit.h"

#include <fstream>

#include "compiler/CodePrinter.h"
#include "compiler/Project.h"
#include "validation/ValidationLogger.h"

#include "lang/type/DoubleType.h"
#include "lang/type/HalfType.h"
#include "lang/type/QuadType.h"
#include "lang/type/SingleType.h"

#include "lang/type/ArrayType.h"
#include "lang/type/BufferType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/PointerType.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/VectorType.h"

#include "lang/type/BooleanType.h"
#include "lang/type/CharType.h"
#include "lang/type/NullPointerType.h"
#include "lang/type/OpaquePointerType.h"
#include "lang/type/SizeType.h"
#include "lang/type/UnsignedIntegerPointerType.h"
#include "lang/type/VoidType.h"

Unit::Unit(Owned<lang::GlobalScope> global_scope) : global_scope_(std::move(global_scope))
{
    addChild(*global_scope_);
}

Unit::Unit() : Unit(makeOwned<lang::GlobalScope>())
{
    // Register keyword types

    global_scope_->registerDefinition(lang::HalfType::get());
    global_scope_->registerDefinition(lang::SingleType::get());
    global_scope_->registerDefinition(lang::DoubleType::get());
    global_scope_->registerDefinition(lang::QuadType::get());

    global_scope_->registerDefinition(lang::VoidType::get());
    global_scope_->registerDefinition(lang::BooleanType::get());
    global_scope_->registerDefinition(lang::CharType::get());
    global_scope_->registerDefinition(lang::SizeType::getSize());
    global_scope_->registerDefinition(lang::SizeType::getDiff());
    global_scope_->registerDefinition(lang::UnsignedIntegerPointerType::get());
    global_scope_->registerDefinition(lang::OpaquePointerType::get());
    global_scope_->registerDefinition(lang::NullPointerType::get());
    // Add type registries

    global_scope_->addTypeRegistry(lang::FixedWidthIntegerType::getRegistry());
    global_scope_->addTypeRegistry(lang::ArrayType::getRegistry());
    global_scope_->addTypeRegistry(lang::VectorType::getRegistry());
    global_scope_->addTypeRegistry(lang::PointerType::getRegistry());
    global_scope_->addTypeRegistry(lang::BufferType::getRegistry());
    global_scope_->addTypeRegistry(lang::ReferenceType::getRegistry());
}

void Unit::setPointerSize(unsigned int size)
{
    pointer_size_ = size;
}

unsigned Unit::getBitness() const
{
    return pointer_size_ * 8;
}

void Unit::preValidate()
{
    global_scope_->resolve();
    global_scope_->postResolve();
}

void Unit::preBuild()
{
    global_scope_->expand();
    global_scope_->resolve();
    global_scope_->postResolve();
    global_scope_->determineFlow();
}

void Unit::emitAsSource(std::filesystem::path const& out)
{
    std::ofstream of;
    of.open(out);

    std::ostream o(of.rdbuf());

    CodePrinter printer(o);
    printer.visit(*this);
}

void Unit::validateFlow(ValidationLogger& validation_logger)
{
    global_scope_->validateFlow(validation_logger);
}

lang::GlobalScope& Unit::globalScope()
{
    return *global_scope_;
}

lang::GlobalScope const& Unit::globalScope() const
{
    return *global_scope_;
}
