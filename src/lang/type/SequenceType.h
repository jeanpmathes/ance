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
        SequenceType(lang::ResolvingHandle<lang::Type> element_type, Optional<uint64_t> size);
        ~SequenceType() override = default;

        ResolvingHandle<lang::Type> getElementType() override;
        lang::Type const&           getElementType() const override;

        [[nodiscard]] StateCount         getStateCount() const override;
        [[nodiscard]] Optional<uint64_t> getSize() const;

        bool                              isSubscriptDefined() const override;
        lang::Type const& getSubscriptReturnType() const override;
        bool                              validateSubscript(lang::Location    indexed_location,
                                                            lang::Type const& index_type,
                                                            lang::Location    index_location,
                                                            ValidationLogger& validation_logger) const override;
        Shared<lang::Value>               buildSubscript(Shared<lang::Value> indexed,
                                                         Shared<lang::Value> index,
                                                         CompileContext& context) const override;
        Shared<lang::Value>               buildSubscriptInBounds(Shared<lang::Value> indexed,
                                                                 Shared<lang::Value> index,
                                                                 CompileContext&     context) const;
        Shared<lang::Value>               buildSubscript(Shared<lang::Value> indexed,
                                                         Shared<lang::Value> index,
                                                         bool            check_bounds,
                                           CompileContext& context) const;

      protected:
        virtual Execution::IndexingMode getIndexingMode() const = 0;

      public:
        std::vector<lang::ResolvingHandle<lang::Type>> getDeclarationDependencies() override;
        std::vector<lang::ResolvingHandle<lang::Type>> getDefinitionDependencies() override;

        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        void performSingleDefaultInitializerDefinition(Shared<lang::Value> ptr, CompileContext& context) const override;
        void performSingleCopyInitializerDefinition(Shared<lang::Value> dts_ptr,
                                                    Shared<lang::Value> src_ptr,
                                                    CompileContext& context) const override;
        void buildSingleDefaultFinalizerDefinition(Shared<lang::Value> ptr, CompileContext& context) const override;

        /**
         * Create a value with the given elements. Only valid if the type is sized.
         * @param values The elements of the value. All values must be of the element type, and the count must match the size.
         * @param context The current compile context.
         * @return The value.
         */
        Shared<lang::Value> createValue(std::vector<Shared<lang::Value>> values, CompileContext& context) const;

      protected:
        lang::ResolvingHandle<lang::Type> element_type_;

        Optional<uint64_t> size_;
    };
}

#endif
