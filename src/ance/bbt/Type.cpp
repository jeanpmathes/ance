#include "Type.h"

#include <format>
#include <map>
#include <stdexcept>
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
        using InnerTypes = std::vector<utility::Shared<Type const>>;
        using Key        = std::pair<InnerTypes, OtherKey>;
        using Entry      = std::pair<Key, utility::Shared<Type>>;

      public:
        TypeDictionary() = default;

        TypeDictionary(TypeDictionary&&) noexcept            = default;
        TypeDictionary& operator=(TypeDictionary&&) noexcept = default;

        TypeDictionary(TypeDictionary const&)            = default;
        TypeDictionary& operator=(TypeDictionary const&) = default;

        template<typename Factory>
            requires(!std::same_as<OtherKey, utility::Empty>)
        utility::Shared<Type> getOrCreate(InnerTypes const& inner_types, OtherKey const& other_key, Factory factory)
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

            utility::Shared<Type> new_type = factory();

            types_.emplace_back(std::make_pair(std::make_pair(inner_types, other_key), new_type));

            return new_type;
        }

        template<typename Factory>
            requires std::same_as<OtherKey, utility::Empty>
        utility::Shared<Type> getOrCreate(InnerTypes const& inner_types, Factory factory)
        {
            return getOrCreate(inner_types, {}, factory);
        }

      private:
        std::vector<Entry> types_;
    };

    template<typename... Args>
    std::vector<utility::Shared<Type const>> bundleTypes(Args... args)
    {
        std::vector<utility::Shared<Type const>> types;
        (types.emplace_back(args), ...);
        return types;
    }

    struct Type::Implementation
    {
        explicit Implementation(core::Identifier const& identifier) : identifier_(identifier) {}

        Implementation(core::Identifier const& identifier, utility::List<utility::Shared<Type const>> constructing_types)
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

        [[nodiscard]] utility::Shared<Type const> getConstructingType(size_t const index) const
        {
            return constructing_types_.at(index);
        }

        void addUnaryOperatorFunction(core::UnaryOperator const unary_operator, core::Identifier function_identifier)
        {
            unary_operator_map_.emplace(unary_operator, function_identifier);
        }

        void addBinaryOperatorFunction(core::BinaryOperator const binary_operator, Type const& rhs_type, core::Identifier function_identifier)
        {
            binary_operator_map_.emplace(std::make_pair(binary_operator, &rhs_type), function_identifier);
        }

        [[nodiscard]] bool isUnaryOperatorDefined(core::UnaryOperator const unary_operator) const
        {
            return unary_operator_map_.contains(unary_operator);
        }

        [[nodiscard]] utility::Optional<core::Identifier> getUnaryOperatorFunctionIdentifier(core::UnaryOperator const unary_operator) const
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

        [[nodiscard]] utility::Optional<core::Identifier> getBinaryOperatorFunctionIdentifier(core::BinaryOperator const binary_operator,
                                                                                              Type const&                rhs_type) const
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
        utility::List<utility::Shared<Type const>>                                     constructing_types_  = {};
        std::map<core::UnaryOperator, core::Identifier>                                unary_operator_map_  = {};
        std::map<std::pair<core::BinaryOperator, Type const*>, core::Identifier>       binary_operator_map_ = {};
    };

    Type::Type(core::Identifier const& identifier) : implementation_(utility::makeOwned<Implementation>(identifier)) {}

    Type::Type(core::Identifier const& identifier, utility::List<utility::Shared<Type const>> constructing_types)
        : implementation_(utility::makeOwned<Implementation>(identifier, std::move(constructing_types)))
    {}

    core::Identifier const& Type::name() const
    {
        return implementation_->identifier();
    }

    std::string Type::annotated() const
    {
        return std::format("'{}'", implementation_->identifier().text());
    }

    bool Type::isReference() const
    {
        return false;
    }

    bool Type::isArray() const
    {
        return false;
    }

    core::VariabilityModifier Type::variability() const
    {
        return core::VariabilityModifier::CONSTANT;
    }

    size_t Type::getConstructingTypeCount() const
    {
        return implementation_->getConstructingTypeCount();
    }

    utility::Shared<Type const> Type::getConstructingType(size_t const index) const
    {
        return implementation_->getConstructingType(index);
    }

    std::string Type::toString() const
    {
        return std::string(implementation_->identifier().text());
    }

    bool Type::isUnaryOperatorDefined(core::UnaryOperator const unary_operator) const
    {
        return implementation_->isUnaryOperatorDefined(unary_operator);
    }

    utility::Optional<core::Identifier> Type::getUnaryOperatorFunctionIdentifier(core::UnaryOperator const unary_operator) const
    {
        return implementation_->getUnaryOperatorFunctionIdentifier(unary_operator);
    }

    bool Type::isBinaryOperatorDefined(core::BinaryOperator const binary_operator, Type const& rhs_type) const
    {
        return implementation_->isBinaryOperatorDefined(binary_operator, rhs_type);
    }

    utility::Optional<core::Identifier> Type::getBinaryOperatorFunctionIdentifier(core::BinaryOperator const binary_operator, Type const& rhs_type) const
    {
        return implementation_->getBinaryOperatorFunctionIdentifier(binary_operator, rhs_type);
    }

    bool Type::isSubscriptDefined() const
    {
        return false;
    }

    utility::Shared<Type const> Type::getSubscriptType() const
    {
        throw std::logic_error("Type does not support subscripting");
    }

    bool Type::isSubscriptInBounds(size_t) const
    {
        throw std::logic_error("Type does not support subscripting");
    }

    BasicType::BasicType(core::Identifier const& identifier, TypeContext& type_context) : Value(std::nullopt, type_context), ValueBase(), Type(identifier, {})
    {}

    bool BasicType::equals(BasicType const& other) const
    {
        return name().text() == other.name().text();
    }

    namespace
    {
        std::string createReferenceTypeName(utility::Shared<Type const> referenced_type, core::VariabilityModifier variability)
        {
            std::string const type_representation(referenced_type->name().text());
            std::string const variability_representation = variability.toString();

            if (variability_representation.empty()) return std::format("&{}", type_representation);

            return std::format("&{} {}", variability_representation, type_representation);
        }
    }

    ReferenceType::ReferenceType(utility::Shared<Type const> referenced_type, core::VariabilityModifier const variability, TypeContext& type_context)
        : Value(std::nullopt, type_context)
        , ValueBase()
        , Type(core::Identifier::make(createReferenceTypeName(referenced_type, variability), core::Location::core()), bundleTypes(referenced_type))
        , referenced_type_(referenced_type)
        , variability_(variability)
    {}

    bool ReferenceType::isReference() const
    {
        return true;
    }

    core::VariabilityModifier ReferenceType::variability() const
    {
        return variability_;
    }

    bool ReferenceType::equals(ReferenceType const& other) const
    {
        return referenced_type_->equals(*other.referenced_type_) && variability_ == other.variability_;
    }

    ArrayType::ArrayType(utility::Shared<Type const> element_type, size_t const length, TypeContext& type_context)
        : Value(std::nullopt, type_context)
        , ValueBase()
        , Type(core::Identifier::make(std::format("[{}; {}]", element_type->name().text(), length), core::Location::core()), bundleTypes(element_type))
        , element_type_(element_type)
        , length_(length)
    {}

    bool ArrayType::isArray() const
    {
        return true;
    }

    utility::Shared<Type const> ArrayType::elementType() const
    {
        return getConstructingType(0);
    }

    size_t ArrayType::length() const
    {
        return length_;
    }

    bool ArrayType::isSubscriptDefined() const
    {
        return true;
    }

    utility::Shared<Type const> ArrayType::getSubscriptType() const
    {
        return element_type_;
    }

    bool ArrayType::isSubscriptInBounds(size_t const index) const
    {
        return index < length_;
    }

    bool ArrayType::equals(ArrayType const& other) const
    {
        return element_type_->equals(*other.element_type_) && length_ == other.length_;
    }

    struct TypeContext::Implementation
    {
        explicit Implementation(cet::Runner& runner) : runner_(runner) {}

        cet::Runner& runner_;

        utility::Optional<utility::Shared<T>> bool_type;
        utility::Optional<utility::Shared<T>> unit_type;
        utility::Optional<utility::Shared<T>> size_type;
        utility::Optional<utility::Shared<T>> string_type;
        utility::Optional<utility::Shared<T>> variable_ref_type;
        utility::Optional<utility::Shared<T>> identifier_type;
        utility::Optional<utility::Shared<T>> function_type;
        utility::Optional<utility::Shared<T>> type_type;
        utility::Optional<utility::Shared<T>> scope_ref_type;
        utility::Optional<utility::Shared<T>> location_type;

        utility::Optional<utility::Shared<T>> float_half_type;
        utility::Optional<utility::Shared<T>> float_single_type;
        utility::Optional<utility::Shared<T>> float_double_type;
        utility::Optional<utility::Shared<T>> float_quad_type;

        TypeDictionary<core::VariabilityModifier> reference_types;
        TypeDictionary<size_t> array_types;

        template<typename Factory>
        static utility::Shared<T const> getOrCreate(utility::Optional<utility::Shared<T>>& type_slot, Factory factory)
        {
            if (!type_slot.hasValue())
            {
                type_slot = factory();
            }

            return type_slot.value();
        }

        template<typename Factory, typename Initializer>
        static utility::Shared<T const> getOrCreate(utility::Optional<utility::Shared<T>>& type_slot, Factory factory, Initializer initializer)
        {
            // todo: the main issue with getOrCreate is that it is a symptom of non-ideal type creation
            // todo: ideally, all methods would create a new type value every time
            // todo: but because types also create the functions, and these reference types, this would lead to endless recursion
            // todo: so we need a way to split type declaration from operator declaration

            if (!type_slot.hasValue())
            {
                type_slot = factory();
                initializer(*type_slot);
            }

            return type_slot.value();
        }

        [[nodiscard]] core::Identifier declareBinaryOperatorFunction(std::string const&         type_name,
                                                                     std::string const&         type_prefix,
                                                                           core::BinaryOperator const binary_operator,
                                                                           T const&                return_type) const
        {
            std::string const short_name     = binary_operator.toShortName();
            std::string const function_name  = std::format("__core_{}_op_{}", type_name, short_name);
            std::string const intrinsic_name = std::format("{}_{}", type_prefix, short_name);

            std::string const code = std::format("public {} (lhs: {}, rhs: {}) : {}\n"
                                                 "{{\n"
                                                 "    return intrinsic \"{}\" args (lhs, rhs);\n"
                                                 "}}\n",
                                                 function_name,
                                                 type_name,
                                                 type_name,
                                                 return_type.name().text(),
                                                 intrinsic_name);

            runner_.declareCore(code, function_name);

            return core::Identifier::make(function_name, core::Location::core());
        }

        [[nodiscard]] core::Identifier declareUnaryOperatorFunction(std::string const&        type_name,
                                                                    std::string const&        type_prefix,
                                                                          core::UnaryOperator const unary_operator) const
        {
            std::string const short_name     = unary_operator.toShortName();
            std::string const function_name  = std::format("__core_{}_op_{}", type_name, short_name);
            std::string const intrinsic_name = std::format("{}_{}", type_prefix, short_name);

            std::string const code = std::format("public {} (operand: {}) : {}\n"
                                                 "{{\n"
                                                 "    return intrinsic \"{}\" args (operand);\n"
                                                 "}}\n",
                                                 function_name,
                                                 type_name,
                                                 type_name,
                                                 intrinsic_name);

            runner_.declareCore(code, function_name);

            return core::Identifier::make(function_name, core::Location::core());
        }

        void addBinaryOperator(T& type, std::string const& type_prefix, core::BinaryOperator const binary_operator) const
        {
            type.implementation_->addBinaryOperatorFunction(binary_operator,
                                                            type,
                                                            declareBinaryOperatorFunction(type.toString(), type_prefix, binary_operator, type));
        }

        void addBinaryOperator(T& type, std::string const& type_prefix, core::BinaryOperator const binary_operator, T const& return_type) const
        {
            type.implementation_->addBinaryOperatorFunction(binary_operator,
                                                            type,
                                                            declareBinaryOperatorFunction(type.toString(), type_prefix, binary_operator, return_type));
        }

        void addArithmeticOperators(T& type, std::string const& type_prefix) const
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

        void addRelationalOperators(T& type, std::string const& type_prefix, T const& return_type) const
        {
            for (auto const op : {core::BinaryOperator::LESS_THAN,
                                  core::BinaryOperator::LESS_THAN_OR_EQUAL,
                                  core::BinaryOperator::GREATER_THAN,
                                  core::BinaryOperator::GREATER_THAN_OR_EQUAL})
            {
                addBinaryOperator(type, type_prefix, op, return_type);
            }
        }

        void addEqualityOperators(T& type, std::string const& type_prefix, T const& return_type) const
        {
            for (auto const op : {core::BinaryOperator::EQUAL, core::BinaryOperator::NOT_EQUAL})
            {
                addBinaryOperator(type, type_prefix, op, return_type);
            }
        }

        void addUnaryOperator(T& type, std::string const& type_prefix, core::UnaryOperator const unary_operator) const
        {
            type.implementation_->addUnaryOperatorFunction(unary_operator, declareUnaryOperatorFunction(type.toString(), type_prefix, unary_operator));
        }

        void ensureReadiness(utility::Shared<T const> type) const
        {
            // todo: that this function is necessary is really ugly, it should be removed at some point
            // todo: ideally, we can define the core types entirely using source code, we build that and we pass it to the runner like we do with all other parts of the language core
            // todo: it would then do everything and we simply query once to get the type
            // todo: when that is the case, we can also remove that the runner check for core declarations that they do not already exists (and skips when they do), instead it could throw
            // todo: or at least we should split type definition and operator definition, so we can define the operators once and centrally, and then construct new types whenever asked for them

            runner_.declareCoreVariable(type->name(), type);
        }
    };

    TypeContext::TypeContext(cet::Runner& runner) : implementation_(utility::makeOwned<Implementation>(runner)), type_type_(Type())
    {
        // The type 'T' is very integral and must be immediately available for the Value implementation.
        // As the value implementation needs access to the type even in const method, the type is stored additionally to the standard handling.
    }

    TypeContext::~TypeContext() = default;

    utility::Shared<Type const> TypeContext::Bool()
    {
        return Implementation::getOrCreate(
            implementation_->bool_type,
            [&] { return utility::makeShared<BasicType>(core::Identifier::make(core::BOOL_TYPE_NAME, core::Location::core()), *this); },
            [&](utility::Shared<T> type) {
                implementation_->ensureReadiness(type);
                implementation_->ensureReadiness(Function());

                std::string const type_prefix = "b";

                implementation_->addUnaryOperator(*type, type_prefix, core::UnaryOperator::NOT);
                implementation_->addEqualityOperators(*type, type_prefix, *type);
            });
    }

    utility::Shared<Type const> TypeContext::Unit()
    {
        return Implementation::getOrCreate(
            implementation_->unit_type,
            [&] { return utility::makeShared<BasicType>(core::Identifier::make(core::UNIT_TYPE_NAME, core::Location::core()), *this); },
            [&](utility::Shared<T> type) {
                implementation_->ensureReadiness(type);
                implementation_->ensureReadiness(Function());

                std::string const type_prefix = "u";

                implementation_->addEqualityOperators(*type, type_prefix, *Bool());
            });
    }

    utility::Shared<Type const> TypeContext::Size()
    {
        return Implementation::getOrCreate(
            implementation_->size_type,
            [&] { return utility::makeShared<BasicType>(core::Identifier::make("Size", core::Location::core()), *this); },
            [&](utility::Shared<T> type) {
                implementation_->ensureReadiness(type);
                implementation_->ensureReadiness(Function());

                std::string const type_prefix = "s";

                implementation_->addArithmeticOperators(*type, type_prefix);
                implementation_->addRelationalOperators(*type, type_prefix, *Bool());
                implementation_->addEqualityOperators(*type, type_prefix, *Bool());
                implementation_->addUnaryOperator(*type, type_prefix, core::UnaryOperator::BITWISE_NOT);
            });
    }

    utility::Shared<Type const> TypeContext::Float(core::Precision const precision)
    {
        auto getOrCreateFloatType = [&](utility::Optional<utility::Shared<T>>& slot, std::string const& type_name, std::string const& type_prefix) {
            return Implementation::getOrCreate(
                slot,
                [&] { return utility::makeShared<BasicType>(core::Identifier::make(type_name, core::Location::core()), *this); },
                [&](utility::Shared<T> type) {
                    implementation_->ensureReadiness(type);
                    implementation_->ensureReadiness(Function());

                    implementation_->addArithmeticOperators(*type, type_prefix);
                    implementation_->addRelationalOperators(*type, type_prefix, *Bool());
                    implementation_->addEqualityOperators(*type, type_prefix, *Bool());
                    implementation_->addUnaryOperator(*type, type_prefix, core::UnaryOperator::NEGATION);
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

        throw std::invalid_argument("Invalid precision");
    }

    utility::Shared<Type const> TypeContext::String()
    {
        return Implementation::getOrCreate(
            implementation_->string_type,
            [&] { return utility::makeShared<BasicType>(core::Identifier::make("String", core::Location::core()), *this); },
            [&](utility::Shared<T> type) {
                implementation_->ensureReadiness(type);
                implementation_->ensureReadiness(Function());

                std::string const type_prefix = "str";

                implementation_->addEqualityOperators(*type, type_prefix, *Bool());
            });
    }

    utility::Shared<Type const> TypeContext::VariableRef()
    {
        return Implementation::getOrCreate(implementation_->variable_ref_type,
                                           [&] { return utility::makeShared<BasicType>(core::Identifier::make(".Variable", core::Location::core()), *this); });
    }

    utility::Shared<Type const> TypeContext::Reference(utility::Shared<T const> referenced_type, core::VariabilityModifier variability)
    {
        return implementation_->reference_types.getOrCreate(bundleTypes(referenced_type), variability, [&] {
            return utility::makeShared<ReferenceType>(referenced_type, variability, *this);
        });
    }

    utility::Shared<Type const> TypeContext::Array(utility::Shared<T const> element_type, size_t const length)
    {
        return implementation_->array_types.getOrCreate(bundleTypes(element_type), length, [&] {
            return utility::makeShared<ArrayType>(element_type, length, *this);
        });
    }

    utility::Shared<Type const> TypeContext::Identifier()
    {
        return Implementation::getOrCreate(
            implementation_->identifier_type,
            [&] { return utility::makeShared<BasicType>(core::Identifier::make("Identifier", core::Location::core()), *this); },
            [&](utility::Shared<T> type) {
                implementation_->ensureReadiness(type);
                implementation_->ensureReadiness(Function());

                std::string const type_prefix = "id";

                implementation_->addEqualityOperators(*type, type_prefix, *Bool());
            });
    }

    utility::Shared<Type const> TypeContext::Function()
    {
        return Implementation::getOrCreate(implementation_->function_type, [&] {
            return utility::makeShared<BasicType>(core::Identifier::make(core::FUNCTION_TYPE_NAME, core::Location::core()), *this);
        });
    }

    utility::Shared<Type const> TypeContext::Type()
    {
        return Implementation::getOrCreate(implementation_->type_type,
                                           [&] { return utility::makeShared<BasicType>(core::Identifier::make("Type", core::Location::core()), *this); });
    }

    utility::Shared<Type const> TypeContext::Type() const
    {
        return type_type_;
    }

    utility::Shared<Type const> TypeContext::ScopeRef()
    {
        return Implementation::getOrCreate(implementation_->scope_ref_type,
                                           [&] { return utility::makeShared<BasicType>(core::Identifier::make(".Scope", core::Location::core()), *this); });
    }

    utility::Shared<Type const> TypeContext::Location()
    {
        return Implementation::getOrCreate(
            implementation_->location_type,
            [&] { return utility::makeShared<BasicType>(core::Identifier::make("Location", core::Location::core()), *this); },
            [&](utility::Shared<T> type) {
                implementation_->ensureReadiness(type);
                implementation_->ensureReadiness(Function());

                std::string const type_prefix = "loc";

                implementation_->addEqualityOperators(*type, type_prefix, *Bool());
            });
    }
}
