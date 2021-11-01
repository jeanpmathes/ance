#ifndef ANCE_SRC_ANCE_UTILITY_RESOLVINGHANDLE_H_
#define ANCE_SRC_ANCE_UTILITY_RESOLVINGHANDLE_H_

#include <memory>

namespace ance
{
    /**
     * A handle that helps resolving entities that can be used before defining them.
     * For that purpose the handle supports some rerouting operations.
     * @tparam T The type of the handled entity.
     */
    template<typename T>
    class ResolvingHandle
    {
      public:
        explicit ResolvingHandle(std::unique_ptr<T> handled);

        ResolvingHandle(const ResolvingHandle& other) noexcept = default;
        ResolvingHandle(ResolvingHandle&& other) noexcept      = default;

        T* get() const;

        std::unique_ptr<T> take();

      private:
        class HandleNavigator
        {
            std::shared_ptr<HandleNavigator> next_ {};

            std::unique_ptr<T> owned_element_ {};
            T*                 element_ {nullptr};

            explicit HandleNavigator(std::shared_ptr<HandleNavigator> next);
            explicit HandleNavigator(std::unique_ptr<T> element);

            HandleNavigator* root();

            T*                 get();
            std::unique_ptr<T> take();

            friend class ance::ResolvingHandle<T>;

          public:
            HandleNavigator(const HandleNavigator& other) = delete;
            HandleNavigator(HandleNavigator&& other)      = delete;
        };

      public:
        T* operator->() const noexcept;
        T& operator*() const noexcept;

      private:
        std::shared_ptr<HandleNavigator> navigator_;
    };

    template<typename T, class... ARGS>
    ance::ResolvingHandle<T> makeHandled(ARGS&&... args);
}

#include "ResolvingHandle.tpp"

#endif
