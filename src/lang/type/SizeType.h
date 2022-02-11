#ifndef ANCE_SRC_ANCE_TYPE_SIZETYPE_H_
#define ANCE_SRC_ANCE_TYPE_SIZETYPE_H_

#include "TypeDefinition.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * Represents an unsigned integer capable of holding the size of the largest possible array as well as a type of holding all possible differences of such sizes.
     */
    class SizeType : public lang::TypeDefinition
    {
      private:
        SizeType(std::string name, llvm::Type*& backing);

        llvm::Type*& backing_;

      public:
        /**
         * The minimum size of a size/diff value.
         */
        static const size_t MINIMUM_BIT_SIZE = 16;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

        bool                         isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other) override;
        bool                         validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                lang::Location                    location,
                                                                ValidationLogger&                 validation_logger) override;
        std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                             std::shared_ptr<Value>            value,
                                                             CompileContext*                   context) override;

        bool isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other) override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::BinaryOperator              op,
                                                                lang::ResolvingHandle<lang::Type> other) override;
        bool                              validateOperator(lang::BinaryOperator              op,
                                                           lang::ResolvingHandle<lang::Type> other,
                                                           lang::Location                    left_location,
                                                           lang::Location                    right_location,
                                                           ValidationLogger&                 validation_logger) override;
        std::shared_ptr<lang::Value>      buildOperator(lang::BinaryOperator   op,
                                                        std::shared_ptr<Value> left,
                                                        std::shared_ptr<Value> right,
                                                        CompileContext*        context) override;

        [[nodiscard]] bool isSizeType() const override;
        [[nodiscard]] bool isDiffType() const override;

        /**
         * Build a value of the size type from a given type size.
         * @param size The type size to use as value.
         * @return The content value containing the given type size.
         */
        static llvm::Value* buildValue(llvm::TypeSize size);

      private:
        inline static unsigned int size_width_        = 0;
        inline static llvm::Type*  size_backing_type_ = nullptr;

        inline static unsigned int diff_width_        = 0;
        inline static llvm::Type*  diff_backing_type_ = nullptr;

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        /**
         * Initialize the size type.
         * @param c The llvm context.
         * @param app The current application.
         */
        static void init(llvm::LLVMContext& c, Application& app);

        /**
         * Get the size type instance.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> getSize();

        /**
         * Get the width of the size type.
         */
        static unsigned int getSizeWidth();

        /**
         * Get the diff type instance.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> getDiff();

        /**
         * Get the width of the diff type.
         */
        static unsigned int getDiffWidth();
    };
}
#endif