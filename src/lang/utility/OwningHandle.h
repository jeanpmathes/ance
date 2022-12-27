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
        static lang::OwningHandle<T> takeOwnership(lang::ResolvingHandle<T> handle);

        lang::ResolvingHandle<T>                               handle();
        std::reference_wrapper<lang::ResolvingHandle<T> const> handle() const;

        T const& get() const;

        T* operator->() noexcept;
        T& operator*() noexcept;

        T const* operator->() const noexcept;
        T const& operator*() const noexcept;

      private:
        Owned<T>                 owner_ {};
        lang::ResolvingHandle<T> handle_;
    };
}

#include "OwningHandle.tpp"

#endif
