#ifndef ANCE_SRC_ANCE_TYPE_SIZETYPE_H_
#define ANCE_SRC_ANCE_TYPE_SIZETYPE_H_

#include "TypeDefinition.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"

class Application;

namespace ance
{
    /**
     * Represents an unsigned integer capable of holding the size of the largest possible array as well as a type of holding all possible differences of such sizes.
     */
    class SizeType : public ance::TypeDefinition
    {
      private:
        SizeType(std::string name, llvm::Type*& backing);

        llvm::Type*& backing_;

      public:
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

        bool isSizeType() const override;
        bool isDiffType() const override;

        /**
         * Build a value of the size type from a given type size.
         * @param size The type size to use as value.
         * @return The content value containing the given type size.
         */
        static llvm::Value* buildValue(llvm::TypeSize size);

      private:
        inline static unsigned int size_width_        = 0;
        inline static Type*        size_instance_     = nullptr;
        inline static llvm::Type*  size_backing_type_ = nullptr;

        inline static unsigned int diff_width_        = 0;
        inline static Type*        diff_instance_     = nullptr;
        inline static llvm::Type*  diff_backing_type_ = nullptr;

      protected:
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
        static ance::ResolvingHandle<ance::Type> getSize();

        /**
         * Get the width of the size type.
         */
        static unsigned int getSizeWidth();

        /**
         * Get the diff type instance.
         * @return The instance.
         */
        static ance::ResolvingHandle<ance::Type> getDiff();

        /**
         * Get the width of the diff type.
         */
        static unsigned int getDiffWidth();
    };
}
#endif