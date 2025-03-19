#ifndef ANCE_CORE_INTRINSIC_H
#define ANCE_CORE_INTRINSIC_H

#include <ostream>

#include "ance/core/Identifier.h"
#include "ance/utility/Node.h"

namespace ance::core
{
    class IntrinsicVisitor;

    /// Base class for all intrinsics.
    struct Intrinsic : virtual utility::AbstractNode<IntrinsicVisitor>
    {
        ~Intrinsic() override = default;

        static struct Print const& print();

        /// Get the identifier of this intrinsic.
        /// \return The identifier.
        [[nodiscard]] virtual Identifier const& identifier() const = 0;

        /// Display this intrinsic to the given output stream.
        /// \param os The output stream to display to.
        virtual void display(std::ostream& os) const = 0;
    };


    /// Dynamic intrinsic that can be identified by name.
    struct Dynamic final
        : Intrinsic
        , utility::ConcreteNode<Dynamic, IntrinsicVisitor>
    {
        explicit Dynamic(Identifier const& identifier);
        ~Dynamic() override = default;

        [[nodiscard]] Identifier const& identifier() const override;

        void display(std::ostream& os) const override;

      private:
        Identifier identifier_;
    };

    template<class T>
    struct Static
        : Intrinsic
        , utility::ConcreteNode<T, IntrinsicVisitor>
    {
        ~Static() override = default;

        [[nodiscard]] Identifier const& identifier() const override
        {
            static Identifier identifier = Identifier::like(T::name);
            return identifier;
        }

        void display(std::ostream& os) const override { os << T::name; }
    };


    /// Print intrinsic.
    struct Print final : Static<Print>// todo: remove this, rather have a log_info/log_warning/log_error intrinsic
    {
        ~Print() override = default;

        static constexpr auto name = "print";
    };


    /// This intrinsic does nothing.
    struct NoOp final : Static<NoOp>
    {
        ~NoOp() override = default;

        static constexpr auto name = "nop";
    };

    /// Visitor for all intrinsics.
    class IntrinsicVisitor : public utility::AbstractVisitor<IntrinsicVisitor>
    {
      public:
        using AbstractVisitor::visit;
        ~IntrinsicVisitor() override = default;

        virtual void visit(Dynamic const& dynamic) = 0;
        virtual void visit(Print const& print)     = 0;
        virtual void visit(NoOp const& no_op)      = 0;
    };
}

std::ostream& operator<<(std::ostream& os, ance::core::Intrinsic const& intrinsic);

#endif
