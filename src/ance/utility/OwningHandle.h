#ifndef ANCE_SRC_ANCE_UTILITY_OWNINGHANDLE_H_
#define ANCE_SRC_ANCE_UTILITY_OWNINGHANDLE_H_

#include <memory>

#include "ance/utility/ResolvingHandle.h"

namespace ance
{
    template<typename T>
    class OwningHandle
    {
      private:
        OwningHandle(std::unique_ptr<T> owner, ance::ResolvingHandle<T> handle);

      public:
        OwningHandle();

        static ance::OwningHandle<T> takeOwnership(ance::ResolvingHandle<T> handle);

        ance::ResolvingHandle<T> handle();

        T* operator->() const noexcept;
        T& operator*() const noexcept;

      private:
        std::unique_ptr<T>       owner_ {};
        ance::ResolvingHandle<T> handle_;
    };
}

#include "OwningHandle.tpp"

#endif
