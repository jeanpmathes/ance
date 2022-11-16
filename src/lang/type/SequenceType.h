#ifndef ANCE_SRC_LANG_TYPE_SEQUENCETYPE_H_
#define ANCE_SRC_LANG_TYPE_SEQUENCETYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * Abstract base class for all sequence types.
     * A sequence type is a type that is a sequence of elements of the same type.
     * Examples are arrays, vectors and also pointers.
     */
    class SequenceType : public virtual lang::TypeDefinition
    {
      public:
        /**
         * Create a new sequence type.
         * @param element_type The type of the elements.
         * @param size An optional size.
         */
        SequenceType(lang::ResolvingHandle<lang::Type> element_type, std::optional<size_t> size);
        ~SequenceType() override = default;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> getElementType() const final;

        [[nodiscard]] StateCount getStateCount() const override;

        bool                              isSubscriptDefined() override;
        lang::ResolvingHandle<lang::Type> getSubscriptReturnType() override;
        bool                              validateSubscript(lang::Location                    indexed_location,
                                                            lang::ResolvingHandle<lang::Type> index_type,
                                                            lang::Location                    index_location,
                                                            ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value>      buildSubscript(std::shared_ptr<Value> indexed,
                                                         std::shared_ptr<Value> index,
                                                         CompileContext&        context) override;

      protected:
        llvm::Value* buildGetElementPointer(std::shared_ptr<lang::Value> const& indexed,
                                            std::shared_ptr<lang::Value> const& index,
                                            CompileContext&                     context);

        llvm::Value* buildGetElementPointer(llvm::Value* indexed, uint64_t index, CompileContext& context);

        virtual llvm::Type*  getIndexedType(CompileContext& context) const;
        virtual llvm::Value* getIndexingPointer(std::shared_ptr<Value> indexed, CompileContext& context);
        virtual llvm::SmallVector<llvm::Value*> getNativeIndices(llvm::Value* zero, llvm::Value* index);

        [[nodiscard]] std::vector<lang::TypeDefinition*> getDependencies() const override;

      public:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        void buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext& context) override;
        void buildSingleCopyInitializerDefinition(llvm::Value*    dts_ptr,
                                                  llvm::Value*    src_ptr,
                                                  CompileContext& context) override;
        void buildSingleDefaultFinalizerDefinition(llvm::Value* ptr, CompileContext& context) override;

      protected:
        /**
         * Create a value with the given elements. Only valid if the type is sized.
         * @param values The elements of the value. All values must be of the element type, and the count must match the size.
         * @param context The current compile context.
         * @return The value.
         */
        std::shared_ptr<lang::Value> createValue(std::vector<std::shared_ptr<lang::Value>> values,
                                                 CompileContext&                           context);

      protected:
        lang::ResolvingHandle<lang::Type> element_type_;
        lang::ResolvingHandle<lang::Type> element_reference_;

        std::optional<size_t> size_;
    };
}

#endif
