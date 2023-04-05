#include "Unit.h"

#include <fstream>
#include <future>

#include "compiler/CodePrinter.h"
#include "compiler/Packages.h"
#include "lang/type/SizeType.h"
#include "lang/type/UnsignedIntegerPointerType.h"
#include "lang/utility/Storage.h"
#include "validation/ValidationLogger.h"

Unit::Unit(Owned<lang::GlobalScope> global_scope) : global_scope_(std::move(global_scope))
{
    addChild(*global_scope_);
}

Unit::Unit(bool is_containing_runtime) : Unit(makeOwned<lang::GlobalScope>(is_containing_runtime))
{
}

void Unit::setTargetInfo(llvm::Triple const& triple, llvm::DataLayout const& data_layout)
{
    pointer_size_  = data_layout.getPointerSize();
    target_triple_ = triple;

    lang::SizeType::init(*this);
    lang::UnsignedIntegerPointerType::init(data_layout);
}

unsigned Unit::getBitness() const
{
    return pointer_size_ * 8;
}

llvm::Triple const& Unit::getTargetTriple() const
{
    return target_triple_;
}

bool Unit::preparePackageDependencies(Packages const&                     packages,
                                      std::function<BuildFunction> const& build,
                                      std::filesystem::path const&        dir,
                                      std::filesystem::path const&        bin_base,
                                      std::filesystem::path const&        bin_suffix,
                                      std::ostream&                       out)
{
    auto dependencies = getDependencies();
    bool valid        = true;

    std::vector<Packages::Package> packages_to_build;
    std::set<std::string>          package_names;

    std::filesystem::path const bld_dir = dir / "dep";
    std::filesystem::create_directories(bld_dir);

    for (auto const& dependency : dependencies)
    {
        if (package_names.contains(dependency))
        {
            out << "ance: packages: Package '" << dependency << "' is already a dependency, skipping" << std::endl;
            continue;
        }

        package_names.insert(dependency);

        auto package = packages.getPackage(dependency);
        if (!package.hasValue())
        {
            out << "ance: packages: Could not find package '" << dependency << "'" << std::endl;
            valid = false;
        }
        else { packages_to_build.push_back(package.value()); }
    }

    if (valid)
    {
        std::vector<std::future<bool>> futures;
        futures.reserve(packages_to_build.size());

        for (auto const& package : packages_to_build)
        {
            futures.emplace_back(
                std::async(std::launch::async,
                           [&packages, &package, &build, &bld_dir, &bin_base, &bin_suffix]() -> bool {
                               std::string const           log_file = package.name + ".txt";
                               std::filesystem::path const log_path = bld_dir / log_file;
                               std::ofstream               log(log_path);

                               Optional<std::filesystem::path> const destination = bld_dir / package.name;
                               std::filesystem::create_directories(destination.value());

                               bool const is_ok = not build(log, package.path, destination, packages).hasValue();

                               if (is_ok)
                               {
                                   std::filesystem::path const results = destination.value() / bin_suffix;
                                   std::filesystem::copy(results,
                                                         bin_base,
                                                         std::filesystem::copy_options::overwrite_existing
                                                             | std::filesystem::copy_options::recursive);
                               }

                               return is_ok;
                           }));
        }

        for (auto [future, package] : llvm::zip(futures, packages_to_build))
        {
            bool const is_ok = future.get();
            valid &= is_ok;

            out << "ance: packages: Building package '" << package.name << "'";
            if (is_ok) { out << " succeeded" << std::endl; }
            else { out << " failed" << std::endl; }

            importPackage(bin_base, package.name);
        }
    }

    return valid;
}

void Unit::exportPackage(std::filesystem::path const& dir)
{
    std::filesystem::create_directories(dir);

    std::filesystem::path const out = dir / (getName() + Packages::PACKAGE_EXTENSION);

    std::ofstream of(out);
    Writer        writer(of);

    Storage& storage = writer;
    storage.sync(*global_scope_);
}

void Unit::importPackage(std::filesystem::path const& path, std::string const& name)
{
    std::filesystem::path const out = path / (name + Packages::PACKAGE_EXTENSION);

    std::ifstream in(out);
    Reader        reader(in);

    Storage& storage = reader;
    storage.data_    = &global_scope_->context();
    storage.sync(*global_scope_);
}

void Unit::preValidate()
{
    global_scope_->resolve();
    global_scope_->postResolve();
}

void Unit::preBuild()
{
    clearChildren();
    global_scope_ = global_scope_->expand();
    addChild(*global_scope_);

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

    Unit const& self = *this;
    printer.visit(self);
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

std::vector<std::string> Unit::getExportedFunctions() const
{
    return global_scope_->getExportFunctions();
}
