#ifndef ANCE_CORE_INTRINSIC_H
#define ANCE_CORE_INTRINSIC_H

#include <ostream>

#include "ance/core/Identifier.h"
#include "ance/core/Signature.h"
#include "ance/core/Type.h"

#include "ance/utility/Node.h"

namespace ance::core
{
    class IntrinsicVisitor;

    class Type;

    /// Base class for all intrinsics.
    struct Intrinsic : virtual utility::AbstractNode<IntrinsicVisitor>
    {
        Intrinsic(Signature signature, Type const& return_type);
        ~Intrinsic() override = default;

        /// Get the signature of this intrinsic.
        /// \return The signature.
        [[nodiscard]] Signature const& signature() const;

        /// Get the return type of this intrinsic.
        [[nodiscard]] Type const& returnType() const;

        /// Get the identifier of this intrinsic.
        /// \return The identifier.
        [[nodiscard]] virtual Identifier const& identifier() const;

        /// Display this intrinsic to the given output stream.
        /// \param os The output stream to display to.
        virtual void display(std::ostream& os) const;

    private:
        Signature signature_;
        Type const& return_type_;
    };

    /// Dynamic intrinsic that is identified by a name.
    struct Dynamic final
        : Intrinsic
        , utility::ConcreteNode<Dynamic, IntrinsicVisitor>
    {
        Dynamic(Signature signature, Type const& return_type);
        ~Dynamic() override = default;

        void display(std::ostream& os) const override;
    };

    template<class T>
    struct Static
        : Intrinsic
        , utility::ConcreteNode<T, IntrinsicVisitor>
    {
        Static(Signature signature, Type const& return_type) : Intrinsic(std::move(signature), return_type) {}
        ~Static() override = default;
    };

    /// This intrinsic does nothing.
    struct NoOp final : Static<NoOp>
    {
    private:
        /// This intrinsic does not take any parameters and returns the unit type.
        NoOp() : Static(Signature::like("nop"), Type::Unit()) {}

    public:
        ~NoOp() override = default;

        static NoOp& instance()
        {
            static NoOp instance;
            return instance;
        }
    };

    /// This intrinsic declares an entity in the calling scope.
    struct Declare final : Static<Declare>
    {
    private:
        /// This intrinsic takes the following parameters:
        /// - The scope to declare the entity in.
        /// - The identifier of the entity to declare.
        /// - Whether the declaration is final.
        /// - The type of the entity to declare.
        /// It returns a reference to the declared entity.
        Declare() : Static(Signature::likeUnnamed("declare", Type::Scope(), Type::Ident(), Type::Bool(), Type::Self()), Type::EntityRef()) {}

    public:
        ~Declare() override = default;

        static Declare& instance()
        {
            static Declare instance;
            return instance;
        }
    };

    /// This intrinsic resolves an entity in the calling scope.
    struct Resolve final : Static<Resolve>
    {
    private:
        /// This intrinsic takes the following parameters:
        /// - The scope to resolve the entity in.
        /// - The identifier of the entity to resolve.
        /// It returns a reference to the resolved entity.
        Resolve() : Static(Signature::likeUnnamed("resolve", Type::Scope(), Type::Ident()), Type::EntityRef()) {}

    public:
        ~Resolve() override = default;

        static Resolve& instance()
        {
            static Resolve instance;
            return instance;
        }
    };

    /// This intrinsic retrieves the parent scope of a scope value.
    struct GetParent final : Static<GetParent>
    {
    private:
        /// This intrinsic takes the following parameters:
        /// - The scope to get the parent of.
        /// It returns the parent scope.
        GetParent() : Static(Signature::likeUnnamed("getparent", Type::Scope()), Type::Scope()) {}

    public:
        ~GetParent() override = default;

        static GetParent& instance()
        {
            static GetParent instance;
            return instance;
        }
    };

    /// This intrinsic converts a boolean to a string.
    struct B2Str final : Static<B2Str>
    {
    private:
        /// This intrinsic takes the following parameters:
        /// - The boolean to convert.
        /// It returns the string representation of the boolean.
        B2Str() : Static(Signature::likeUnnamed("b2str", Type::Bool()), Type::String()) {} // todo: path type

    public:
        ~B2Str() override = default;

        static B2Str& instance()
        {
            static B2Str instance;
            return instance;
        }
    };

    /// This intrinsic logs a message.
    struct Log final : Static<Log>
    {
    private:
        /// This intrinsic takes the following parameters:
        /// - The string message to log.
        /// - The location to log the message at.
        /// It returns the unit type.
        Log() : Static(Signature::likeUnnamed("log", Type::String(), Type::Location()), Type::Unit()) {}

    public:
        ~Log() override = default;

        static Log& instance()
        {
            static Log instance;
            return instance;
        }
    };

    /// This intrinsic includes another source file.
    struct Include final : Static<Include>
    {
    private:
        /// This intrinsic takes the following parameters:
        /// - The path of the file to include.
        /// - The location of a file to use as base to resolve a relative path.
        /// It returns the unit type.
        Include() : Static(Signature::likeUnnamed("include", Type::String(), Type::Location()), Type::Unit()) {} // todo: path type

    public:
        ~Include() override = default;

        static Include& instance()
        {
            static Include instance;
            return instance;
        }
    };

    /// Visitor for all intrinsics.
    class IntrinsicVisitor : public utility::AbstractVisitor<IntrinsicVisitor>
    {
      public:
        using AbstractVisitor::visit;
        ~IntrinsicVisitor() override = default;

        virtual void visit(Dynamic const& dynamic) = 0;
        virtual void visit(NoOp const& no_op)      = 0;
        virtual void visit(Declare const& declare) = 0;
        virtual void visit(Resolve const& resolve) = 0;
        virtual void visit(GetParent const& get_parent) = 0;
        virtual void visit(Log const& log)         = 0;
        virtual void visit(B2Str const& b2str)     = 0;
        virtual void visit(Include const& include) = 0;
    };
}

std::ostream& operator<<(std::ostream& os, ance::core::Intrinsic const& intrinsic);

#endif
