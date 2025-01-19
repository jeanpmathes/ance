#ifndef ANCE_UTILITY_OWNERS_H
#define ANCE_UTILITY_OWNERS_H

#include <memory>
#include <any>

#include "Optional.h"

namespace ance::utility
{
    template<typename T>
    class Owned;

    template<typename T, class... Args>
    Owned<T> makeOwned(Args&&... args);

    /**
     * Owns a value. Prefer this over std::unique_ptr for ownership.
     * @tparam T The type of the value.
     */
    template<typename T>
    class Owned
    {
      public:
        explicit Owned(T& value);
        Owned(Owned&& value) noexcept;
        template<typename OtherT>
            requires MoveConvertible<T*, OtherT*>
        explicit(false) Owned(Owned<OtherT>&& value) noexcept;

        Owned& operator=(Owned&& value) noexcept;
        template<typename OtherT>
            requires MoveConvertible<T*, OtherT*>
        Owned& operator=(Owned<OtherT>&& value) noexcept;

        static T* release(Owned&& value);

      private:
        explicit Owned(std::unique_ptr<T>&& value);

      public:
        T*       get();
        T const* get() const;

        T& operator*();
        T* operator->();

        T const& operator*() const;
        T const* operator->() const;

        template<typename OtherT>
        friend class Owned;

        template<typename TargetT, class... Args>
        friend Owned<TargetT> makeOwned(Args&&... args);

      private:
        std::unique_ptr<T> value_;
    };

    template<typename T, class... Args>
    Owned<T> makeOwned(Args&&... args)
    {
        return Owned<T>(std::make_unique<T>(std::forward<Args>(args)...));
    }

    template<typename T>
    Optional<Owned<T>> wrap(T* value)
    {
        if (value) return Optional<Owned<T>>(Owned<T>(*value));
        return std::nullopt;
    }

    template<typename T>
    Owned<T> wrap(std::any const& value)
    {
        T* ptr = std::any_cast<T*>(value);
        return Owned<T>(*ptr);
    }

    template<typename T>
    T* getPtr(Optional<Owned<T>>& value)
    {
        if (value.hasValue()) return value->get();
        return nullptr;
    }

    template<typename T>
    T const* getPtr(Optional<Owned<T>> const& value)
    {
        if (value.hasValue()) return value->get();
        return nullptr;
    }

    template<typename T>
    T* unwrap(Owned<T>&& value)
    {
        return Owned<T>::release(std::move(value));
    }

    template<typename T>
    class Shared;

    template<typename T, class... Args>
    Shared<T> makeShared(Args&&... args);

    /**
     * Shares a value. Prefer this over std::shared_ptr for shared ownership.
     * @tparam T The type of the value.
     */
    template<typename T>
    class Shared
    {
      public:
        explicit Shared(T& value);
        Shared(Shared&& value) noexcept;
        Shared(Shared& value) noexcept;

        template<typename OtherT>
            requires MoveConvertible<T*, OtherT*>
        explicit(false) Shared(Shared<OtherT>&& value) noexcept;

        template<typename OtherT>
            requires CopyConvertible<T*, OtherT*>
        explicit(false) Shared(Shared<OtherT>& value) noexcept;

        Shared& operator=(Shared value) noexcept;

        template<typename OtherT>
            requires MoveConvertible<T*, OtherT*>
        Shared& operator=(Shared<OtherT>&& value) noexcept;

        template<typename OtherT>
            requires CopyConvertible<T*, OtherT*>
        Shared& operator=(Shared<OtherT>& value) noexcept;

        bool operator==(Shared const& other) const noexcept;
        bool operator!=(Shared const& other) const noexcept;

      private:
        explicit Shared(std::shared_ptr<T>&& value);

      public:
        T*       get();
        T const* get() const;

        T& operator*();
        T* operator->();

        T const& operator*() const;
        T const* operator->() const;

        template<typename OtherT>
        friend class Shared;

        template<typename TargetT, class... Args>
        friend Shared<TargetT> makeShared(Args&&... args);

        template<typename OtherT>
        Shared<OtherT> cast();

        template<typename OtherT>
        OtherT const& cast() const;

        template<typename OtherT>
        [[nodiscard]] bool is() const;

      private:
        std::shared_ptr<T> value_;
    };

    template<typename T, class... Args>
    Shared<T> makeShared(Args&&... args)
    {
        return Shared<T>(std::make_shared<T>(std::forward<Args>(args)...));
    }
}

#include "Owners.tpp"

#endif
