#ifndef ANCE_SRC_LANG_UTILITY_RESOLVINGHANDLE_H_
#define ANCE_SRC_LANG_UTILITY_RESOLVINGHANDLE_H_

#include <memory>
#include <optional>

#include "lang/utility/Owners.h"

namespace lang
{
    /**
     * A get that helps resolving entities that can be used before defining them.
     * For that purpose the get supports some rerouting operations.
     * @tparam T The type of the handled entity. Must conform to the get target interface.
     */
    template<typename T>
    class ResolvingHandle
    {
      public:
        explicit ResolvingHandle(Owned<T> handled);

        ResolvingHandle(ResolvingHandle<T>&& value) noexcept;
        ResolvingHandle(ResolvingHandle<T>& value) noexcept;
        ResolvingHandle(ResolvingHandle<T> const& value) = delete;

        ResolvingHandle<T>& operator=(ResolvingHandle<T> value) noexcept;

      private:
        T*       get();
        T const* get() const;

      public:
        /**
         * Take ownership over the handled object.
         */
        Owned<T> take();

        /**
         * Reroute this get to forget the currently handled object and target a new object.
         * @param target A get to the new target.
         */
        void reroute(lang::ResolvingHandle<T> target);

      private:
        class HandleNavigator
        {
            Optional<Shared<HandleNavigator>> next_ {};

            Optional<Owned<T>> owned_element_ {};
            T*                 element_ {nullptr};

            explicit HandleNavigator(Shared<HandleNavigator> next);
            explicit HandleNavigator(Owned<T> element);

            Optional<Shared<HandleNavigator>> sRoot();

            HandleNavigator*       root();
            HandleNavigator const* root() const;

            T*       get();
            T const* get() const;
            Owned<T> take();

            void target(Shared<HandleNavigator> next);

            friend class lang::ResolvingHandle<T>;

          public:
            HandleNavigator(HandleNavigator const& other) = delete;
            HandleNavigator(HandleNavigator&& other)      = delete;
        };

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
        Shared<HandleNavigator> getRootNavigator();

        Shared<HandleNavigator> navigator_;
    };

    template<typename T, class... ARGS>
    lang::ResolvingHandle<T> makeHandled(ARGS&&... args);

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

        virtual bool equalsTarget(SELF const* other) const;

        virtual ~HandleTarget() = default;

      private:
        Optional<lang::ResolvingHandle<SELF>> self_ {};
    };
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
