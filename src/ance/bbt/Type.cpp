#include "Type.h"

#include <vector>

#include "ance/utility/Empty.h"

namespace ance::bbt
{
    template<typename OtherKey = utility::Empty>
    class TypeDictionary final
    {
        using TypeHandle = utility::Shared<Type>;
        using InnerTypes = std::vector<TypeHandle>;
        using Key        = std::pair<InnerTypes, OtherKey>;
        using Entry      = std::pair<Key, TypeHandle>;

      public:
        TypeDictionary() = default;

        TypeDictionary(TypeDictionary&&) noexcept            = default;
        TypeDictionary& operator=(TypeDictionary&&) noexcept = default;

        TypeDictionary(TypeDictionary const&)            = default;
        TypeDictionary& operator=(TypeDictionary const&) = default;

        template<typename Factory>
        TypeHandle getOrCreate(InnerTypes const& inner_types, OtherKey const& other_key, Factory factory)
        {
            // todo: find a way to optimize this lookup, e.g. a simple map
            // todo: make sure that it actually works hashing-wise with the shared owners

            for (auto& [current_key, current_type] : types_)
            {
                auto& [current_inner_types, current_other_key] = current_key;

                if (current_inner_types == inner_types && current_other_key == other_key)
                {
                    return current_type;
                }
            }

            TypeHandle new_type = factory();

            types_.emplace_back(std::make_pair(std::make_pair(inner_types, other_key), new_type));

            return new_type;
        }

        template<typename Factory>
        TypeHandle getOrCreate(InnerTypes const& inner_types, Factory factory)
        {
            return getOrCreate(inner_types, {}, factory);
        }

      private:
        std::vector<Entry> types_;
    };

    template<typename... Args>
    std::vector<utility::Shared<Type>> bundleTypes(Args... args)
    {
        std::vector<utility::Shared<Type>> types;
        (types.emplace_back(args), ...);
        return types;
    }

    Type::Type(core::Identifier const& identifier, TypeContext& type_context) : Value(std::nullopt, type_context), identifier_(identifier) {}

    Type::Type(core::Identifier const& identifier, utility::List<utility::Shared<Type>> constructor_type, TypeContext& type_context)
        : Value(std::nullopt, type_context)
        , identifier_(identifier)
        , constructor_types_(std::move(constructor_type))
    {}

    core::Identifier const& Type::name() const
    {
        return identifier_;
    }

    bool Type::operator==(Type const& other) const
    {
        return &other == this;
    }

    bool Type::operator!=(Type const& other) const
    {
        return !(*this == other);
    }

    bool Type::isLReference() const
    {
        return false;
    }

    size_t Type::getConstructorTypeCount() const
    {
        return constructor_types_.size();
    }

    utility::Shared<Type> Type::getConstructorType(size_t const index)
    {
        return constructor_types_.at(index);
    }

    Type const& Type::getConstructorType(size_t const index) const
    {
        return *constructor_types_.at(index);
    }

    std::string Type::toString() const
    {
        return std::string(identifier_.text());
    }

    LReferenceType::LReferenceType(utility::Shared<Type> referenced_type, TypeContext& type_context)
        : Type(core::Identifier::make("&" + std::string(referenced_type->name().text())), bundleTypes(referenced_type), type_context)
        , referenced_type_(referenced_type)
    {}

    bool LReferenceType::isLReference() const
    {
        return true;
    }

    struct TypeContext::Implementation
    {
        utility::Optional<utility::Shared<Type>> bool_type;
        utility::Optional<utility::Shared<Type>> unit_type;
        utility::Optional<utility::Shared<Type>> size_type;
        utility::Optional<utility::Shared<Type>> string_type;
        utility::Optional<utility::Shared<Type>> variable_ref_type;
        utility::Optional<utility::Shared<Type>> identifier_type;
        utility::Optional<utility::Shared<Type>> function_type;
        utility::Optional<utility::Shared<Type>> type_type;
        utility::Optional<utility::Shared<Type>> scope_ref_type;
        utility::Optional<utility::Shared<Type>> location_type;

        TypeDictionary<> lref_types;

        template<typename Factory>
        static utility::Shared<Type> getOrCreate(utility::Optional<utility::Shared<Type>>& type_slot, Factory factory)
        {
            if (!type_slot.hasValue())
            {
                type_slot = factory();
            }

            return type_slot.value();
        }
    };

    TypeContext::TypeContext() : implementation_(utility::makeOwned<Implementation>()) {}

    TypeContext::~TypeContext() = default;

    utility::Shared<Type> TypeContext::getBool()
    {
        return Implementation::getOrCreate(implementation_->bool_type, [&] { return utility::makeShared<Type>(core::Identifier::make("Bool"), *this); });
    }

    utility::Shared<Type> TypeContext::getUnit()
    {
        return Implementation::getOrCreate(implementation_->unit_type, [&] { return utility::makeShared<Type>(core::Identifier::make("Unit"), *this); });
    }

    utility::Shared<Type> TypeContext::getSize()
    {
        return Implementation::getOrCreate(implementation_->size_type, [&] { return utility::makeShared<Type>(core::Identifier::make("Size"), *this); });
    }

    utility::Shared<Type> TypeContext::getString()
    {
        return Implementation::getOrCreate(implementation_->string_type, [&] { return utility::makeShared<Type>(core::Identifier::make("String"), *this); });
    }

    utility::Shared<Type> TypeContext::getVariableRef()
    {
        return Implementation::getOrCreate(implementation_->variable_ref_type,
                                           [&] { return utility::makeShared<Type>(core::Identifier::make(".Variable"), *this); });
    }

    utility::Shared<Type> TypeContext::getLRef(utility::Shared<Type> referenced_type)
    {
        return implementation_->lref_types.getOrCreate(bundleTypes(referenced_type),
                                                       [&] { return utility::makeShared<LReferenceType>(referenced_type, *this); });
    }

    utility::Shared<Type> TypeContext::getIdentifier()
    {
        return Implementation::getOrCreate(implementation_->identifier_type,
                                           [&] { return utility::makeShared<Type>(core::Identifier::make("Identifier"), *this); });
    }

    utility::Shared<Type> TypeContext::getFunction()
    {
        return Implementation::getOrCreate(implementation_->function_type,
                                           [&] { return utility::makeShared<Type>(core::Identifier::make("Function"), *this); });
    }

    utility::Shared<Type> TypeContext::getType()
    {
        return Implementation::getOrCreate(implementation_->type_type, [&] { return utility::makeShared<Type>(core::Identifier::make("Type"), *this); });
    }

    utility::Shared<Type> TypeContext::getScopeRef()
    {
        return Implementation::getOrCreate(implementation_->scope_ref_type, [&] { return utility::makeShared<Type>(core::Identifier::make(".Scope"), *this); });
    }

    utility::Shared<Type> TypeContext::getLocation()
    {
        return Implementation::getOrCreate(implementation_->location_type,
                                           [&] { return utility::makeShared<Type>(core::Identifier::make("Location"), *this); });
    }
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Type const& type)
{
    return out << type.name();
}
