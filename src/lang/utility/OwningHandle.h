#ifndef ANCE_SRC_LANG_UTILITY_OWNINGHANDLE_H_
#define ANCE_SRC_LANG_UTILITY_OWNINGHANDLE_H_

#include <memory>

#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    template<typename T>
    class OwningHandle
    {
      private:
        OwningHandle(Owned<T> owner, lang::ResolvingHandle<T> handle);

      public:
        OwningHandle(OwningHandle&& other) noexcept            = default;
        OwningHandle& operator=(OwningHandle&& other) noexcept = default;

        template<typename OtherT>
            requires MoveConvertible<T*, OtherT*>
        explicit(false) OwningHandle(OwningHandle<OtherT>&& value) noexcept;// NOLINT(google-explicit-constructor)

        template<typename OtherT>
            requires MoveConvertible<T*, OtherT*>
        OwningHandle<T>& operator=(OwningHandle<OtherT>&& value) noexcept;

        /**
         * Take ownership of a resolving handle.
         * @param handle The handle to take ownership of. It must currently own itself.
         * @return The owning handle.
         */
        static lang::OwningHandle<T> takeOwnership(lang::ResolvingHandle<T> handle);

        /**
         * Cast an owning handle of different type to this type.
         * @param owning_handle The handle to cast.
         * @return The casted handle.
         */
        template<typename Original>
        static lang::OwningHandle<T> cast(lang::OwningHandle<Original>&& owning_handle);

        lang::ResolvingHandle<T>                               handle();
        std::reference_wrapper<lang::ResolvingHandle<T> const> handle() const;

        T const& get() const;

        T* operator->() noexcept;
        T& operator*() noexcept;

        T const* operator->() const noexcept;
        T const& operator*() const noexcept;

        ~OwningHandle();

        template<typename Other>
        friend class OwningHandle;

      private:
        Owned<T>                 owner_ {};
        lang::ResolvingHandle<T> handle_;
    };
}

#include "OwningHandle.tpp"

#endif
