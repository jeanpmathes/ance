#include "Unit.h"

#include <fstream>

#include "compiler/CodePrinter.h"
#include "compiler/Project.h"
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

bool Unit::preparePackageDependencies(Packages const&              packages,
                                      PrepareFunction const&       prepare,
                                      std::filesystem::path const& dir,
                                      std::ostream&                out)
{
    assert(dependencies_.empty());

    auto dependencies = getDependencies();
    bool valid        = true;

    std::set<std::string>          package_names;
    std::vector<Packages::Package> packages_to_build;

    std::filesystem::path const bld_dir = dir / "dep";
    std::filesystem::create_directories(bld_dir);

    for (auto const& dependency : dependencies)
    {
        if (dependency == getName())
        {
            out << "ance: packages: Package '" << dependency << "' depends on itself" << std::endl;
            valid = false;
            continue;
        }

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
        for (auto const& package : packages_to_build)
        {
            std::string const           log_file = package.name + ".txt";
            std::filesystem::path const log_path = bld_dir / log_file;
            std::ofstream               log(log_path);

            Optional<std::filesystem::path> const destination = bld_dir / package.name;
            std::filesystem::create_directories(destination.value());

            open_logs_.emplace_back(std::move(log));
            std::ofstream& log_ref = open_logs_.back();

            auto potential_description = prepare(package.path, destination, log_ref, packages);

            if (potential_description.hasValue())
            {
                auto& application = (**potential_description).getApplication();
                if (application.getType() != UnitResult::PACKAGE)
                {
                    out << "ance: packages: Package '" << package.name << "' is not a package" << std::endl;
                    potential_description = std::nullopt;
                }
            }

            dependencies_.emplace_back(std::move(potential_description), package);
        }

        for (auto& [project, package] : dependencies_)
        {
            bool const is_ok = project.hasValue();
            valid &= is_ok;

            out << "ance: packages: Preparing package '" << package.name << "'";
            if (is_ok) { out << " succeeded" << std::endl; }
            else { out << " failed" << std::endl; }
        }
    }

    return valid;
}

bool Unit::buildPackageDependencies(Packages const&              packages,
                                    BuildFunction const&         build,
                                    std::filesystem::path const& dir,
                                    std::filesystem::path const& bin_base,
                                    std::filesystem::path const& bin_suffix,
                                    std::ostream&                out,
                                    std::set<std::string> const  included_packages,
                                    std::ostream&                root_out)
{
    bool              valid = true;
    std::vector<bool> status_codes;

    std::filesystem::path const bld_dir = dir / "dep";
    std::filesystem::create_directories(bld_dir);

    for (auto& [project, package] : dependencies_)
    {
        if (included_packages.contains(package.name))
        {
            root_out << "ance: packages: Package '" << package.name << "', required by '" << getName()
                     << "', is part of a circular dependency" << std::endl;
            valid = false;
            continue;
        }

        std::set<std::string> new_included_packages = included_packages;
        new_included_packages.insert(package.name);

        Optional<std::filesystem::path> const destination = bld_dir / package.name;
        std::filesystem::create_directories(destination.value());

        bool const is_ok = build(**project, packages, new_included_packages, root_out);

        if (is_ok)
        {
            std::filesystem::path const results = destination.value() / bin_suffix;
            std::filesystem::copy(results,
                                  bin_base,
                                  std::filesystem::copy_options::overwrite_existing
                                      | std::filesystem::copy_options::recursive);
        }

        status_codes.push_back(is_ok);
    }

    for (auto [is_ok, dependency] : llvm::zip(status_codes, dependencies_))
    {
        auto const& [project, package] = dependency;
        valid &= is_ok;

        out << "ance: packages: Building package '" << package.name << "'";
        if (is_ok) { out << " succeeded" << std::endl; }
        else { out << " failed" << std::endl; }

        importPackage(bin_base, package.name);
    }

    open_logs_.clear();

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

    global_scope_->setCurrentDescriptionSource(name);

    Storage& storage = reader;
    storage.data_    = &global_scope_->context();
    storage.sync(*global_scope_);

    global_scope_->setCurrentDescriptionSource(std::nullopt);
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

Unit::~Unit() = default;
