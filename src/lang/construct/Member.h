#ifndef ANCE_SRC_LANG_CONSTRUCT_MEMBER_H_
#define ANCE_SRC_LANG_CONSTRUCT_MEMBER_H_

#include "lang/AccessModifier.h"
#include "lang/Assigner.h"
#include "lang/expression/ConstantExpression.h"
#include "lang/type/Type.h"

class ConstantExpression;

namespace lang
{
    /**
     * A member of a class or struct.
     */
    class Member
    {
      public:
        /**
         * Creates a new member.
         * @param access The access modifier of the member.
         * @param name The name of the member.
         * @param type The type of the member.
         * @param assigner The assigner of the member.
         * @param constant_init The constant initializer of the member.
         * @param location The location of the member.
         * @param type_location The location of the type of the member.
         */
        Member(lang::AccessModifier                access,
               lang::Identifier                    name,
               lang::ResolvingHandle<lang::Type>   type,
               lang::Assigner                      assigner,
               Optional<Owned<ConstantExpression>> constant_init,
               lang::Location                      location,
               lang::Location                      type_location);

        [[nodiscard]] lang::AccessModifier    access() const;
        [[nodiscard]] lang::Identifier const& name() const;

        [[nodiscard]] lang::Type const&                 type() const;
        [[nodiscard]] lang::ResolvingHandle<lang::Type> type();

        [[nodiscard]] lang::Assigner assigner() const;
        [[nodiscard]] lang::Location location() const;
        [[nodiscard]] lang::Location typeLocation() const;

        /**
         * Set the scope that contains the member.
         */
        void setScope(lang::Scope* scope);

        /**
         * Validates the member.
         * @param validation_logger The logger to use for validation.
         * @return True if the member is valid, false otherwise.
         */
        bool validate(ValidationLogger& validation_logger) const;

        /**
         * Gets the constant initializer of the member.
         * @return The constant initializer of the member.
         */
        llvm::Constant* getConstantInitializer(llvm::Module& m) const;

        /**
         * Build the initialization of this member.
         * @param ptr The pointer to the member.
         * @param context The compile context.
         */
        void buildInitialization(llvm::Value* ptr, CompileContext& context);

        void expand();

      private:
        llvm::Constant* getInitialValue(llvm::Module& m) const;

      private:
        lang::AccessModifier                access_;
        lang::Identifier                    name_;
        lang::ResolvingHandle<lang::Type>   type_;
        lang::Assigner                      assigner_;
        Optional<Owned<ConstantExpression>> constant_init_;
        lang::Location                      location_;
        lang::Location                      type_location_;

        mutable llvm::Constant* initial_value_ {nullptr};
    };
}

#endif
