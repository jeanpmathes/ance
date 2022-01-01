#ifndef ANCE_SRC_ANCE_TYPE_FLOATINGPOINTTYPE_H_
#define ANCE_SRC_ANCE_TYPE_FLOATINGPOINTTYPE_H_

#include "TypeDefinition.h"

namespace ance
{
    /**
     * The base class of all floating point types.
     */
    class FloatingPointType : virtual public ance::TypeDefinition
    {
      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        ~FloatingPointType() override = default;

        [[nodiscard]] bool isFloatingPointType() const override;
        [[nodiscard]] bool isFloatingPointType(size_t precision) const override = 0;

        bool isOperatorDefined(BinaryOperator op, ance::ResolvingHandle<ance::Type> other) override;
        ance::ResolvingHandle<ance::Type> getOperatorResultType(BinaryOperator                    op,
                                                                ance::ResolvingHandle<ance::Type> other) override;
        bool                              validateOperator(BinaryOperator                    op,
                                                           ance::ResolvingHandle<ance::Type> other,
                                                           ance::Location                    left_location,
                                                           ance::Location                    right_location,
                                                           ValidationLogger&                 validation_logger) override;
        std::shared_ptr<ance::Value>      buildOperator(BinaryOperator         op,
                                                        std::shared_ptr<Value> left,
                                                        std::shared_ptr<Value> right,
                                                        CompileContext*        context) override;
    };
}
#endif