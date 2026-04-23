#include "Type.h"

#include <format>
#include <map>
#include <vector>

#include "ance/core/BinaryOperator.h"
#include "ance/core/Constants.h"
#include "ance/core/Identifier.h"
#include "ance/core/Location.h"
#include "ance/core/Precision.h"
#include "ance/core/UnaryOperator.h"

#include "ance/utility/Empty.h"

#include "ance/cet/Runner.h"

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

    struct Type::Implementation
    {
        explicit Implementation(core::Identifier const& identifier) : identifier_(identifier) {}

        Implementation(core::Identifier const& identifier, utility::List<utility::Shared<Type>> constructing_types)
            : identifier_(identifier)
            , constructing_types_(std::move(constructing_types))
        {}

        [[nodiscard]] core::Identifier const& identifier() const
        {
            return identifier_;
        }

        [[nodiscard]] size_t getConstructingTypeCount() const
        {
            return constructing_types_.size();
        }

        utility::Shared<Type> getConstructingType(size_t const index)
        {
            return constructing_types_.at(index);
        }

        [[nodiscard]] Type const& getConstructingType(size_t const index) const
        {
            return *constructing_types_.at(index);
        }

        void addUnaryOperatorFunction(core::UnaryOperator const unary_operator, utility::Shared<Value> function)
        {
            unary_operator_map_.emplace(unary_operator, function);
        }

        void addBinaryOperatorFunction(core::BinaryOperator const binary_operator, Type const& rhs_type, utility::Shared<Value> function)
        {
            auto const key = std::make_pair(binary_operator, &rhs_type);
            binary_operator_map_.emplace(key, function);
        }

        [[nodiscard]] bool isUnaryOperatorDefined(core::UnaryOperator const unary_operator) const
        {
            return unary_operator_map_.contains(unary_operator);
        }

        utility::Optional<utility::Shared<Value>> getUnaryOperatorFunction(core::UnaryOperator const unary_operator)
        {
            auto const iterator = unary_operator_map_.find(unary_operator);

            if (iterator == unary_operator_map_.end())
            {
                return std::nullopt;
            }

            return iterator->second;
        }

        [[nodiscard]] bool isBinaryOperatorDefined(core::BinaryOperator const binary_operator, Type const& rhs_type) const
        {
            auto const key = std::make_pair(binary_operator, &rhs_type);
            return binary_operator_map_.contains(key);
        }

        utility::Optional<utility::Shared<Value>> getBinaryOperatorFunction(core::BinaryOperator const binary_operator, Type const& rhs_type)
        {
            auto const key      = std::make_pair(binary_operator, &rhs_type);
            auto const iterator = binary_operator_map_.find(key);

            if (iterator == binary_operator_map_.end())
            {
                return std::nullopt;
            }

            return iterator->second;
        }

      private:
        core::Identifier                                                               identifier_;
        utility::List<utility::Shared<Type>>                                           constructing_types_  = {};
        std::map<core::UnaryOperator, utility::Shared<Value>>                          unary_operator_map_  = {};
        std::map<std::pair<core::BinaryOperator, Type const*>, utility::Shared<Value>> binary_operator_map_ = {};
    };

    Type::Type(core::Identifier const& identifier, TypeContext& type_context)
        : ValueBase(std::nullopt, type_context)
        , implementation_(utility::makeOwned<Implementation>(identifier))
    {}

    Type::Type(core::Identifier const& identifier, utility::List<utility::Shared<Type>> constructing_types, TypeContext& type_context)
        : ValueBase(std::nullopt, type_context)
        , implementation_(utility::makeOwned<Implementation>(identifier, std::move(constructing_types)))
    {}

    core::Identifier const& Type::name() const
    {
        return implementation_->identifier();
    }

    std::string Type::annotated() const
    {
        return std::format("'{}'", implementation_->identifier().text());
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

    size_t Type::getConstructingTypeCount() const
    {
        return implementation_->getConstructingTypeCount();
    }

    utility::Shared<Type> Type::getConstructingType(size_t const index)
    {
        return implementation_->getConstructingType(index);
    }

    Type const& Type::getConstructingType(size_t const index) const
    {
        return implementation_->getConstructingType(index);
    }

    std::string Type::toString() const
    {
        return std::string(implementation_->identifier().text());
    }

    bool Type::equals(Type const& other) const
    {
        return other == *this;
    }

    bool Type::isUnaryOperatorDefined(core::UnaryOperator const unary_operator) const
    {
        return implementation_->isUnaryOperatorDefined(unary_operator);
    }

    utility::Optional<utility::Shared<Value>> Type::getUnaryOperatorFunction(core::UnaryOperator const unary_operator)
    {
        return implementation_->getUnaryOperatorFunction(unary_operator);
    }

    bool Type::isBinaryOperatorDefined(core::BinaryOperator const binary_operator, Type const& rhs_type) const
    {
        return implementation_->isBinaryOperatorDefined(binary_operator, rhs_type);
    }

    utility::Optional<utility::Shared<Value>> Type::getBinaryOperatorFunction(core::BinaryOperator const binary_operator, Type const& rhs_type)
    {
        return implementation_->getBinaryOperatorFunction(binary_operator, rhs_type);
    }

    LReferenceType::LReferenceType(utility::Shared<Type> referenced_type, TypeContext& type_context)
        : Type(core::Identifier::make("&" + std::string(referenced_type->name().text()), core::Location::core()), bundleTypes(referenced_type), type_context)
        , referenced_type_(referenced_type)
    {}

    bool LReferenceType::isLReference() const
    {
        return true;
    }

    struct TypeContext::Implementation
    {
        explicit Implementation(cet::Runner& runner) : runner_(runner) {}

        cet::Runner& runner_;

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

        utility::Optional<utility::Shared<Type>> float_half_type;
        utility::Optional<utility::Shared<Type>> float_single_type;
        utility::Optional<utility::Shared<Type>> float_double_type;
        utility::Optional<utility::Shared<Type>> float_quad_type;

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

        template<typename Factory, typename Initializer>
        static utility::Shared<Type> getOrCreate(utility::Optional<utility::Shared<Type>>& type_slot, Factory factory, Initializer initializer)
        {
            if (!type_slot.hasValue())
            {
                type_slot = factory();
                initializer(*type_slot);
            }

            return type_slot.value();
        }

        [[nodiscard]] utility::Shared<Value> declareBinaryOperatorFunction(std::string const&         type_name,
                                                                           std::string const&         type_prefix,
                                                                           core::BinaryOperator const binary_operator) const
        {
            std::string const short_name     = binary_operator.toShortName();
            std::string const function_name  = std::format("__core_{}_op_{}", type_name, short_name);
            std::string const intrinsic_name = std::format("{}_{}", type_prefix, short_name);

            std::string const code = std::format("public {} (lhs: {}, rhs: {}) : {}\n"
                                                 "{{\n"
                                                 "    return intrinsic \"{}\" (lhs, rhs);\n"
                                                 "}}\n",
                                                 function_name,
                                                 type_name,
                                                 type_name,
                                                 type_name,
                                                 intrinsic_name);

            runner_.declareCore(code, function_name);

            return runner_.getCoreVariableValue(core::Identifier::make(function_name, core::Location::core()));
        }

        [[nodiscard]] utility::Shared<Value> declareUnaryOperatorFunction(std::string const&        type_name,
                                                                          std::string const&        type_prefix,
                                                                          core::UnaryOperator const unary_operator) const
        {
            std::string const short_name     = unary_operator.toShortName();
            std::string const function_name  = std::format("__core_{}_op_{}", type_name, short_name);
            std::string const intrinsic_name = std::format("{}_{}", type_prefix, short_name);

            std::string const code = std::format("public {} (operand: {}) : {}\n"
                                                 "{{\n"
                                                 "    return intrinsic \"{}\" (operand);\n"
                                                 "}}\n",
                                                 function_name,
                                                 type_name,
                                                 type_name,
                                                 intrinsic_name);

            runner_.declareCore(code, function_name);

            return runner_.getCoreVariableValue(core::Identifier::make(function_name, core::Location::core()));
        }

        void addBinaryOperator(Type& type, std::string const& type_prefix, core::BinaryOperator const binary_operator) const
        {
            type.implementation_->addBinaryOperatorFunction(binary_operator,
                                                            type,
                                                            declareBinaryOperatorFunction(type.toString(), type_prefix, binary_operator));
        }

        void addArithmeticOperators(Type& type, std::string const& type_prefix) const
        {
            for (auto const op : {core::BinaryOperator::ADDITION,
                                  core::BinaryOperator::SUBTRACTION,
                                  core::BinaryOperator::MULTIPLICATION,
                                  core::BinaryOperator::DIVISION,
                                  core::BinaryOperator::REMAINDER})
            {
                addBinaryOperator(type, type_prefix, op);
            }
        }

        void addUnaryOperator(Type& type, std::string const& type_prefix, core::UnaryOperator const unary_operator) const
        {
            type.implementation_->addUnaryOperatorFunction(unary_operator, declareUnaryOperatorFunction(type.toString(), type_prefix, unary_operator));
        }

        void ensureReadiness(utility::Shared<Type> type) const
        {
            // todo: that this function is necessary is really ugly, it should be removed at some point
            // todo: ideally, we can define the core types entirely using source code, we build that and we pass it to the runner like we do with all other parts of the language core
            // todo: it would then do everything and we simply query once to get the type
            // todo: when that is the case, we can also remove that the runner check for core declarations that they do not already exists (and skips when they do), instead it could throw

            runner_.declareCoreVariable(type->name(), type);
        }
    };

    TypeContext::TypeContext(cet::Runner& runner) : implementation_(utility::makeOwned<Implementation>(runner)) {}

    TypeContext::~TypeContext() = default;

    utility::Shared<Type> TypeContext::getBool()
    {
        return Implementation::getOrCreate(
            implementation_->bool_type,
            [&] { return utility::makeShared<Type>(core::Identifier::make(core::BOOL_TYPE_NAME, core::Location::core()), *this); },
            [&](utility::Shared<Type> type) {
                implementation_->ensureReadiness(type);
                implementation_->ensureReadiness(getFunction());

                implementation_->addUnaryOperator(*type, "b", core::UnaryOperator::NOT);
            });
    }

    utility::Shared<Type> TypeContext::getUnit()
    {
        return Implementation::getOrCreate(implementation_->unit_type, [&] {
            return utility::makeShared<Type>(core::Identifier::make(core::UNIT_TYPE_NAME, core::Location::core()), *this);
        });
    }

    utility::Shared<Type> TypeContext::getSize()
    {
        return Implementation::getOrCreate(
            implementation_->size_type,
            [&] { return utility::makeShared<Type>(core::Identifier::make("Size", core::Location::core()), *this); },
            [&](utility::Shared<Type> type) {
                implementation_->ensureReadiness(type);
                implementation_->ensureReadiness(getFunction());

                implementation_->addArithmeticOperators(*type, "s");
            });
    }

    utility::Shared<Type> TypeContext::getFloat(core::Precision const precision)
    {
        auto getOrCreateFloatType = [&](utility::Optional<utility::Shared<Type>>& slot, std::string const& type_name, std::string const& type_prefix) {
            return Implementation::getOrCreate(
                slot,
                [&] { return utility::makeShared<Type>(core::Identifier::make(type_name, core::Location::core()), *this); },
                [&](utility::Shared<Type> type) {
                    implementation_->ensureReadiness(type);
                    implementation_->ensureReadiness(getFunction());

                    implementation_->addArithmeticOperators(*type, type_prefix);
                });
        };

        switch (precision)
        {
            case core::Precision::HALF:
                return getOrCreateFloatType(implementation_->float_half_type, "Half", "fh");

            case core::Precision::SINGLE:
                return getOrCreateFloatType(implementation_->float_single_type, "Single", "fs");

            case core::Precision::DOUBLE:
                return getOrCreateFloatType(implementation_->float_double_type, "Double", "fd");

            case core::Precision::QUAD:
                return getOrCreateFloatType(implementation_->float_quad_type, "Quad", "fq");
        }

        throw std::logic_error("Invalid precision");
    }

    utility::Shared<Type> TypeContext::getString()
    {
        return Implementation::getOrCreate(implementation_->string_type,
                                           [&] { return utility::makeShared<Type>(core::Identifier::make("String", core::Location::core()), *this); });
    }

    utility::Shared<Type> TypeContext::getVariableRef()
    {
        return Implementation::getOrCreate(implementation_->variable_ref_type,
                                           [&] { return utility::makeShared<Type>(core::Identifier::make(".Variable", core::Location::core()), *this); });
    }

    utility::Shared<Type> TypeContext::getLRef(utility::Shared<Type> referenced_type)
    {
        return implementation_->lref_types.getOrCreate(bundleTypes(referenced_type),
                                                       [&] { return utility::makeShared<LReferenceType>(referenced_type, *this); });
    }

    utility::Shared<Type> TypeContext::getIdentifier()
    {
        return Implementation::getOrCreate(implementation_->identifier_type,
                                           [&] { return utility::makeShared<Type>(core::Identifier::make("Identifier", core::Location::core()), *this); });
    }

    utility::Shared<Type> TypeContext::getFunction()
    {
        return Implementation::getOrCreate(implementation_->function_type, [&] {
            return utility::makeShared<Type>(core::Identifier::make(core::FUNCTION_TYPE_NAME, core::Location::core()), *this);
        });
    }

    utility::Shared<Type> TypeContext::getType()
    {
        return Implementation::getOrCreate(implementation_->type_type,
                                           [&] { return utility::makeShared<Type>(core::Identifier::make("Type", core::Location::core()), *this); });
    }

    utility::Shared<Type> TypeContext::getScopeRef()
    {
        return Implementation::getOrCreate(implementation_->scope_ref_type,
                                           [&] { return utility::makeShared<Type>(core::Identifier::make(".Scope", core::Location::core()), *this); });
    }

    utility::Shared<Type> TypeContext::getLocation()
    {
        return Implementation::getOrCreate(implementation_->location_type,
                                           [&] { return utility::makeShared<Type>(core::Identifier::make("Location", core::Location::core()), *this); });
    }
}
