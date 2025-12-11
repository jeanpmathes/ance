#include "IntrinsicSignature.h"

#include "ance/utility/Optional.h"

#include "ance/bbt/Type.h"

namespace
{
    class IntrinsicSignatureVisitor final : public ance::core::IntrinsicVisitor
    {
      public:
        using IntrinsicVisitor::visit;

        explicit IntrinsicSignatureVisitor(ance::bbt::TypeContext& type_context) : type_context_(type_context) {}

        std::tuple<ance::bbt::Signature, ance::utility::Shared<ance::bbt::Type>> get(ance::core::Intrinsic const& intrinsic)
        {
            this->visit(intrinsic);
            return {signature_.value(), return_type_.value()};
        }

      protected:
        void visit(ance::core::Dynamic const& dynamic) override
        {
            signature_   = ance::bbt::Signature::like(dynamic.identifier());
            return_type_ = type_context_.getUnit();
        }

        void visit(ance::core::NoOp const& no_op) override
        {
            /// This intrinsic does not take any parameters and returns the unit type.

            signature_   = ance::bbt::Signature::like(no_op.identifier());
            return_type_ = type_context_.getUnit();
        }

        void visit(ance::core::Declare const& declare) override
        {
            /// This intrinsic takes the following parameters:
            /// - The scope to declare the variable in.
            /// - The identifier of the variable to declare.
            /// - Whether the declaration is final.
            /// - The type of the variable to declare.
            /// It returns a reference to the declared variable.

            signature_   = ance::bbt::Signature::likeUnnamed(declare.identifier(),
                                                           type_context_.getScopeRef(),
                                                           type_context_.getIdentifier(),
                                                           type_context_.getBool(),
                                                           type_context_.getType());
            return_type_ = type_context_.getVariableRef();
        }

        void visit(ance::core::Resolve const& resolve) override
        {
            /// This intrinsic takes the following parameters:
            /// - The scope to resolve the variable in.
            /// - The identifier of the variable to resolve.
            /// It returns a reference to the resolved variable.

            signature_   = ance::bbt::Signature::likeUnnamed(resolve.identifier(), type_context_.getScopeRef(), type_context_.getIdentifier());
            return_type_ = type_context_.getVariableRef();
        }

        void visit(ance::core::GetParent const& get_parent) override
        {
            /// This intrinsic takes the following parameters:
            /// - The scope to get the parent of.
            /// It returns the parent scope.

            signature_   = ance::bbt::Signature::likeUnnamed(get_parent.identifier(), type_context_.getScopeRef());
            return_type_ = type_context_.getScopeRef();
        }

        void visit(ance::core::Log const& log) override
        {
            /// This intrinsic takes the following parameters:
            /// - The string message to log.
            /// - The location to log the message at.
            /// It returns the unit type.

            signature_   = ance::bbt::Signature::likeUnnamed(log.identifier(), type_context_.getString(), type_context_.getLocation());
            return_type_ = type_context_.getUnit();
        }

        void visit(ance::core::B2Str const& b2str) override
        {
            /// This intrinsic takes the following parameters:
            /// - The boolean to convert.
            /// It returns the string representation of the boolean.

            signature_   = ance::bbt::Signature::likeUnnamed(b2str.identifier(), type_context_.getBool());
            return_type_ = type_context_.getString();
        }

        void visit(ance::core::Include const& include) override
        {
            /// This intrinsic takes the following parameters:
            /// - The path of the file to include.
            /// - The location of a file to use as base to resolve a relative path.
            /// It returns the unit type.

            signature_   = ance::bbt::Signature::likeUnnamed(include.identifier(),
                                                           type_context_.getString(),// todo: path type
                                                           type_context_.getLocation());
            return_type_ = type_context_.getUnit();
        }

      private:
        ance::utility::Optional<ance::bbt::Signature>                   signature_;
        ance::utility::Optional<ance::utility::Shared<ance::bbt::Type>> return_type_;
        ance::bbt::TypeContext&                                         type_context_;
    };
}

namespace ance::bbt
{
    std::tuple<Signature, utility::Shared<Type>> IntrinsicSignature::get(core::Intrinsic const& intrinsic, TypeContext& type_context)
    {
        IntrinsicSignatureVisitor visitor(type_context);
        return visitor.get(intrinsic);
    }
}
