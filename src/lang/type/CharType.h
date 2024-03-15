#ifndef ANCE_SRC_LANG_TYPE_CHARTYPE_H_
#define ANCE_SRC_LANG_TYPE_CHARTYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * The char type. Stores unicode code points.
     */
    class CharType : public lang::TypeDefinition
    {
      public:
        static constexpr size_t SIZE_IN_BITS = 32;

        CharType();
        ~CharType() override = default;

        [[nodiscard]] StateCount getStateCount() const override;
        bool                     isCharType() const override;

        bool isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const override;
        lang::Type const& getOperatorResultType(lang::BinaryOperator              op,
                                                                lang::Type const& other) const override;
        bool                              validateOperator(lang::BinaryOperator op,
                                                           lang::Type const&    other,
                                                           lang::Location       left_location,
                                                           lang::Location       right_location,
                                                           ValidationLogger&    validation_logger) const override;
        Shared<lang::Value>               buildOperator(lang::BinaryOperator op,
                                                        Shared<lang::Value>  left,
                                                        Shared<lang::Value>  right,
                                                        CompileContext&      context) const override;

        bool                isCastingPossibleTo(Type const& other) const override;
        bool                validateCast(Type const&       other,
                                         lang::Location    location,
                                         ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildCast(lang::Type const& other,
                                      Shared<lang::Value>               value,
                                      CompileContext&                   context) const override;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        std::string   createMangledName() const override;
        void          registerExecutionType(CompileContext& context) const override;

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
