#ifndef ANCE_SRC_LANG_CONTEXT_H_
#define ANCE_SRC_LANG_CONTEXT_H_

#include "lang/type/Type.h"
#include "lang/utility/TypeRegistry.h"

namespace lang
{
    class GlobalScope;
}

namespace lang
{
    /**
     * The context in which a program or library is compiled.
     */
    class Context
    {
      public:
        explicit Context(GlobalScope& global_scope, bool contains_runtime);

        /**
         * Perform resolving on all types that require it.
         */
        void resolve();

        /**
         * Perform post resolving on all types that require it.
         */
        void postResolve();

        void buildNativeDeclarations(CompileContext& context);
        void buildNativeDefinitions(CompileContext& context);

        /**
         * Get an array type instance.
         * @param element_type The element type of the array.
         * @param size The size of the array. Must be greater than zero.
         * @return The array type instance.
         */
        lang::ResolvingHandle<lang::Type> getArrayType(lang::ResolvingHandle<lang::Type> element_type,
                                                       uint64_t                          size) const;

        /**
         * Get the boolean type.
         * @return The boolean type.
         */
        lang::ResolvingHandle<lang::Type> getBooleanType() const;

        /**
         * Get a buffer type instance.
         * @param element_type The element type of the buffer.
         * @return The buffer type instance.
         */
        lang::ResolvingHandle<lang::Type> getBufferType(lang::ResolvingHandle<lang::Type> element_type) const;

        /**
         * Get the char type.
         * @return The char type.
         */
        lang::ResolvingHandle<lang::Type> getCharType() const;

        /**
         * Get the double type.
         * @return The double type.
         */
        lang::ResolvingHandle<lang::Type> getDoubleType() const;

        /**
         * Get a fixed width integer type instance.
         * @param bit_size The size of the integer in bytes. Must be greater than zero.
         * @param is_signed Whether the integer is signed.
         * @return The fixed width integer type instance.
         */
        lang::ResolvingHandle<lang::Type> getFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const;

        /**
         * Get the half type.
         * @return The half type.
         */
        lang::ResolvingHandle<lang::Type> getHalfType() const;

        /**
         * Get the null pointer type.
         * @return The null pointer type.
         */
        lang::ResolvingHandle<lang::Type> getNullPointerType() const;

        /**
         * Get the opaque pointer type.
         * @return The opaque pointer type.
         */
        lang::ResolvingHandle<lang::Type> getOpaquePointerType() const;

        /**
         * Get a pointer type instance.
         * @param element_type The element type of the pointer.
         * @return The pointer type instance.
         */
        lang::ResolvingHandle<lang::Type> getPointerType(lang::ResolvingHandle<lang::Type> element_type) const;

        /**
         * Get the quad type.
         * @return The quad type.
         */
        lang::ResolvingHandle<lang::Type> getQuadType() const;

        /**
         * Get a reference type instance.
         * @param element_type The element type of the reference.
         * @return The reference type instance.
         */
        lang::ResolvingHandle<lang::Type> getReferenceType(lang::ResolvingHandle<lang::Type> element_type) const;

        /**
         * Get the single type.
         * @return The single type.
         */
        lang::ResolvingHandle<lang::Type> getSingleType() const;

        /**
         * Get the size type.
         * @return The size type.
         */
        lang::ResolvingHandle<lang::Type> getSizeType() const;

        /**
         * Get the diff type.
         * @return The diff type.
         */
        lang::ResolvingHandle<lang::Type> getDiffType() const;

        /**
         * Get the unsigned integer pointer type.
         * @return The unsigned integer pointer type.
         */
        lang::ResolvingHandle<lang::Type> getUnsignedIntegerPointerType() const;

        /**
         * Get a vector type instance.
         * @param element_type The element type of the vector.
         * @param size The size of the vector. Must be greater than zero.
         * @return The vector type instance.
         */
        lang::ResolvingHandle<lang::Type> getVectorType(lang::ResolvingHandle<lang::Type> element_type,
                                                        uint64_t                          size) const;

        /**
         * Get the void type.
         * @return The void type.
         */
        lang::ResolvingHandle<lang::Type> getVoidType() const;

        /**
         * Whether the application is being compiled with the runtime.
         */
        bool isContainingRuntime() const;

        /**
         * Use this for elements that depend on the runtime.
         * @param location The location of the element.
         * @param validation_logger The logger to use for validation.
         * @return True if the runtime is available.
         */
        bool validateRuntimeDependency(lang::Location location, ValidationLogger& validation_logger) const;

        struct DescriptionSource {
            std::string name;
            bool        is_public;
        };

        /**
         * Set the source (package) that is currently used.
         * All descriptions added after this call will be associated with this source.
         * @param source The source to set, or nullopt to set the current project as source.
         */
        void setCurrentDescriptionSource(Optional<DescriptionSource> source);

        Optional<std::string> getCurrentDescriptionSourceName() const;
        bool                  isCurrentDescriptionSourcePublic() const;

      private:
        GlobalScope&                               global_scope_;
        std::vector<lang::TypeDefinitionRegistry*> type_registries_ {};
        bool                                       contains_runtime_;
        Optional<DescriptionSource>                current_description_source_;

        mutable lang::TypeRegistry<uint64_t>                  array_types_;
        mutable lang::TypeRegistry<>                          buffer_types_;
        mutable lang::TypeRegistry<std::pair<uint64_t, bool>> fixed_width_integer_types_;
        mutable lang::TypeRegistry<>                          pointer_types_;
        mutable lang::TypeRegistry<>                          reference_types_;
        mutable lang::TypeRegistry<uint64_t>                  vector_types_;

        mutable Optional<lang::ResolvingHandle<lang::Type>> boolean_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> char_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> double_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> half_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> null_pointer_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> opaque_pointer_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> quad_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> single_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> size_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> diff_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> unsigned_integer_pointer_type_;
        mutable Optional<lang::ResolvingHandle<lang::Type>> void_type_;
    };
}

#endif
