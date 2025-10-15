#ifndef ANCE_CORE_INTRINSIC_H
#define ANCE_CORE_INTRINSIC_H

#include <ostream>

#include "ance/core/Identifier.h"
#include "ance/core/Signature.h"

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
        NoOp();

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
        Declare();

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
        Resolve();

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
        GetParent();

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
        B2Str();

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
        Log();

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
        Include();

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
