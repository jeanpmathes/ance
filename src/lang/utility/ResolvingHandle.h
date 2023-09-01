#ifndef ANCE_SRC_LANG_UTILITY_RESOLVINGHANDLE_H_
#define ANCE_SRC_LANG_UTILITY_RESOLVINGHANDLE_H_

#include <memory>
#include <optional>

#include "lang/utility/Owners.h"

namespace lang// This is somewhat of a hack to allow upcasting of handles.
{
    template<typename T>
    struct HandleConfig {
        using BaseType = T;
    };

    template<typename T>
    class ResolvingHandle;
}

#include "lang/construct/Entity.h"

namespace lang
{
    template<typename T>
    class OwningHandle;

    template<typename T>
    class HandleNavigator;

    template<typename T>
    class HandleTarget;

    /**
     * A handle that helps resolving entities that can be used before defining them.
     * For that purpose the handle supports some rerouting operations.
     * @tparam T The type of the handled entity. Must conform to the handle target interface.
     */
    template<typename T>
    class ResolvingHandle
    {
      private:
        explicit ResolvingHandle(Owned<T> handled);

        template<typename U>
        friend lang::ResolvingHandle<U> wrapHandled(Owned<U>&& element)
            requires std::derived_from<U, HandleTarget<U>>;

        explicit ResolvingHandle(Shared<HandleNavigator<typename lang::HandleConfig<T>::BaseType>> navigator);

      public:
        ResolvingHandle(ResolvingHandle<T>&& value) noexcept;
        ResolvingHandle(ResolvingHandle<T>& value) noexcept;
        ResolvingHandle(ResolvingHandle<T> const& value) = delete;

        ResolvingHandle<T>& operator=(ResolvingHandle<T> value) noexcept;

        template<typename U>
            requires MoveConvertible<T*, U*>
        explicit(false) ResolvingHandle(ResolvingHandle<U>&& value) noexcept;// NOLINT(google-explicit-constructor)

        template<typename U>
            requires CopyConvertible<T*, U*>
        explicit(false) ResolvingHandle(ResolvingHandle<U>& value) noexcept;// NOLINT(google-explicit-constructor)

        template<typename U>
            requires MoveConvertible<T*, U*>
        ResolvingHandle<T>& operator=(ResolvingHandle<U>&& value) noexcept;

        template<typename U>
            requires CopyConvertible<T*, U*>
        ResolvingHandle<T>& operator=(ResolvingHandle<U>& value) noexcept;

        template<typename U>
        friend class ResolvingHandle;

      private:
        T*                     get();
        [[nodiscard]] T const* get() const;

      public:
        /**
         * Take ownership over the handled object.
         */
        Owned<T> take();

        /**
         * Reroute this handle to forget the currently handled object and target a new object.
         * @param target A handle to the new target.
         */
        void reroute(lang::ResolvingHandle<T> target);

        /**
         * Check whether this handle is targeting a specific type.
         * @tparam Destination The type to check for.
         * @return True if this handle is targeting the type.
         */
        template<typename Destination>
        [[nodiscard]] bool is() const;

        /**
         * Cast this handle to a handle of a derived type.
         * @tparam Destination The type to as to.
         * @return The casted handle, or an empty optional if the as is not possible.
         */
        template<typename Destination>
        Optional<lang::ResolvingHandle<Destination>> as();

        /**
         * Cast this handle to a pointer of a derived type.
         * @tparam Destination The type to as to.
         * @return The casted pointer, or nullptr if the as is not possible.
         */
        template<typename Destination>
        Destination const* as() const;

        typename lang::HandleConfig<T>::BaseType&       base();
        typename lang::HandleConfig<T>::BaseType const& base() const;

      public:
        T* operator->() noexcept;
        T& operator*() noexcept;

        T const* operator->() const noexcept;
        T const& operator*() const noexcept;

        operator T&() noexcept;            // NOLINT(google-explicit-constructor)
        operator T const&() const noexcept;// NOLINT(google-explicit-constructor)

        bool operator==(ResolvingHandle<T> const& other) const;
        bool operator!=(ResolvingHandle<T> const& other) const;

        bool operator<(ResolvingHandle<T> const& other) const;

      private:
        friend class OwningHandle<T>;

        /**
         * Invalidate this handle. This is called by the owning handle when it is destroyed.
         * It is possible that handles are routed away from the owning handle, which the owning handle does not know.
         * To prevent invalidation in that case, the owning handle passes a pointer to the element it owns.
         * @param element The element owned by the owning handle. No invalidation is performed if this is not the handled element.
         */
        void invalidate(T const* element);

      private:
        Shared<HandleNavigator<typename lang::HandleConfig<T>::BaseType>> getRootNavigator();

        Shared<HandleNavigator<typename lang::HandleConfig<T>::BaseType>> navigator_;
    };

    template<typename T>
    class HandleNavigator
    {
        Optional<Shared<HandleNavigator>> next_ {};

        Optional<Owned<T>> owned_element_ {};
        T*                 element_ {nullptr};

        explicit HandleNavigator(Shared<HandleNavigator> next);
        explicit HandleNavigator(Owned<T> element);

        Optional<Shared<HandleNavigator>> root();
        HandleNavigator*                  navigator();
        HandleNavigator const*            root() const;

        T*       get();
        T const* get() const;
        Owned<T> take();

        void target(Shared<HandleNavigator> next);

        template<typename U>
        friend class lang::ResolvingHandle;

      public:
        HandleNavigator(HandleNavigator const& other) = delete;
        HandleNavigator(HandleNavigator&& other)      = delete;
    };

    /**
     * The interface expected from handled entities.
     * @tparam SELF The type of the handled entity.
     */
    template<typename SELF>
    class HandleTarget
    {
      public:
        void                        setSelf(lang::ResolvingHandle<SELF> handle);
        SELF const&                 self() const;
        lang::ResolvingHandle<SELF> self();

        virtual ~HandleTarget() = default;

      private:
        Optional<lang::ResolvingHandle<SELF>> self_ {};
    };

    template<typename T>
    lang::ResolvingHandle<T> wrapHandled(Owned<T>&& element)
        requires std::derived_from<T, HandleTarget<T>>;

    template<typename T, class... ARGS>
    lang::ResolvingHandle<T> makeHandled(ARGS&&... args)
        requires std::derived_from<T, HandleTarget<T>>;
}

template<typename T>
T& deref(T* value)
{
    return *value;
}

template<typename T>
T& deref(T& value)
{
    return value;
}

template<typename T>
T& deref(lang::ResolvingHandle<T>& value)
{
    return *value;
}

template<typename T>
T& deref(std::reference_wrapper<T> value)
{
    return value.get();
}

#include "ResolvingHandle.tpp"

#endif
