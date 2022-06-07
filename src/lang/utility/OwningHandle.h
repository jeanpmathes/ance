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
        OwningHandle(std::unique_ptr<T> owner, lang::ResolvingHandle<T> handle);

      public:
        OwningHandle();

        static lang::OwningHandle<T> takeOwnership(lang::ResolvingHandle<T> handle);

        lang::ResolvingHandle<T> handle() const;

        T* operator->() noexcept;
        T& operator*() noexcept;

        const T* operator->() const noexcept;
        const T& operator*() const noexcept;

      private:
        std::unique_ptr<T>       owner_ {};
        lang::ResolvingHandle<T> handle_;
    };
}

#include "OwningHandle.tpp"

#endif
