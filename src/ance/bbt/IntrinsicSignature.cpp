#include "IntrinsicSignature.h"

#include "ance/utility/Optional.h"

#include "ance/bbt/Type.h"

namespace
{
    class IntrinsicSignatureVisitor final : public ance::core::IntrinsicVisitor
    {
      public:
        using IntrinsicVisitor::visit;

        std::tuple<ance::bbt::Signature, ance::utility::Shared<ance::bbt::Type>> get(ance::core::Intrinsic const& intrinsic)
        {
            this->visit(intrinsic);
            return { signature_.value(), return_type_.value() };
        }

      protected:
        void visit(ance::core::Dynamic const& dynamic) override
        {
            signature_ = ance::bbt::Signature::like(dynamic.identifier());
            return_type_ = ance::bbt::Type::Unit();
        }

        void visit(ance::core::NoOp const& no_op) override
        {
            /// This intrinsic does not take any parameters and returns the unit type.

            signature_ = ance::bbt::Signature::like(no_op.identifier());
            return_type_ = ance::bbt::Type::Unit();
        }

        void visit(ance::core::Declare const& declare) override
        {
            /// This intrinsic takes the following parameters:
            /// - The scope to declare the variable in.
            /// - The identifier of the variable to declare.
            /// - Whether the declaration is final.
            /// - The type of the variable to declare.
            /// It returns a reference to the declared variable.

            signature_ = ance::bbt::Signature::likeUnnamed(
                declare.identifier(),
                ance::bbt::Type::ScopeRef(),
                ance::bbt::Type::Ident(),
                ance::bbt::Type::Bool(),
                ance::bbt::Type::Self());
            return_type_ = ance::bbt::Type::VariableRef();
        }

        void visit(ance::core::Resolve const& resolve) override
        {
            /// This intrinsic takes the following parameters:
            /// - The scope to resolve the variable in.
            /// - The identifier of the variable to resolve.
            /// It returns a reference to the resolved variable.

            signature_ = ance::bbt::Signature::likeUnnamed(
                resolve.identifier(),
                ance::bbt::Type::ScopeRef(),
                ance::bbt::Type::Ident());
            return_type_ = ance::bbt::Type::VariableRef();
        }

        void visit(ance::core::GetParent const& get_parent) override
        {
            /// This intrinsic takes the following parameters:
            /// - The scope to get the parent of.
            /// It returns the parent scope.

            signature_ = ance::bbt::Signature::likeUnnamed(
                get_parent.identifier(),
                ance::bbt::Type::ScopeRef());
            return_type_ = ance::bbt::Type::ScopeRef();
        }

        void visit(ance::core::Log const& log) override
        {
            /// This intrinsic takes the following parameters:
            /// - The string message to log.
            /// - The location to log the message at.
            /// It returns the unit type.

            signature_ = ance::bbt::Signature::likeUnnamed(
                log.identifier(),
                ance::bbt::Type::String(),
                ance::bbt::Type::Location());
            return_type_ = ance::bbt::Type::Unit();
        }

        void visit(ance::core::B2Str const& b2str) override
        {
            /// This intrinsic takes the following parameters:
            /// - The boolean to convert.
            /// It returns the string representation of the boolean.

            signature_ = ance::bbt::Signature::likeUnnamed(
                b2str.identifier(),
                ance::bbt::Type::Bool());
            return_type_ = ance::bbt::Type::String();
        }

        void visit(ance::core::Include const& include) override
        {
            /// This intrinsic takes the following parameters:
            /// - The path of the file to include.
            /// - The location of a file to use as base to resolve a relative path.
            /// It returns the unit type.

            signature_ = ance::bbt::Signature::likeUnnamed(
                include.identifier(),
                ance::bbt::Type::String(), // todo: path type
                ance::bbt::Type::Location());
            return_type_ = ance::bbt::Type::Unit();
        }

      private:
        ance::utility::Optional<ance::bbt::Signature> signature_;
        ance::utility::Optional<ance::utility::Shared<ance::bbt::Type>> return_type_;
    };
}

namespace ance::bbt
{
    std::tuple<Signature, utility::Shared<Type>> IntrinsicSignature::get(core::Intrinsic const& intrinsic)
    {
        IntrinsicSignatureVisitor visitor;
        return visitor.get(intrinsic);
    }
}
