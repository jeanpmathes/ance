#ifndef ANCE_SRC_LANG_VISITOR_H_
#define ANCE_SRC_LANG_VISITOR_H_

#include <any>
#include <memory>
#include <utility>

#include "Constructs.h"

/**
 * Code inspired by:
 * https://gist.github.com/tomas789/7844152
 */

namespace lang
{
    template<typename... Types>
    class Visitor;

    template<typename T>
    class Visitor<T>
    {
      public:
        virtual std::any visit(T& visitable) = 0;
    };

    template<typename T, typename... TList>
    class Visitor<T, TList...> : public Visitor<TList...>
    {
      public:
        using Visitor<TList...>::visit;

        virtual std::any visit(T& visitable) = 0;
    };

    template<typename... TList>
    class VisitorImplementation;

    template<typename U, typename T>
    class VisitorImplementation<U, T>;

    template<typename U, typename T>
    concept CanVisit = requires(U visitor, T& visitable)
    {
        {
            visitor.visit(visitable)
            } -> std::same_as<std::any>;
    };

    template<typename U, typename T>
    class VisitorImplementation<U, T>
    {
      protected:
        std::unique_ptr<U> u_;

      public:
        template<typename... ParamList>
        explicit VisitorImplementation(ParamList&&... plist)
            : u_(std::make_unique<U>(std::forward<ParamList>(plist)...))
        {}

        virtual std::any visit(T& t)
        {
            if constexpr (CanVisit<U, T>) { return u_->visit(t); }
            else {
                return {};
            }
        }
    };

    template<typename U, typename T, typename... TList>
    class VisitorImplementation<U, T, TList...> : public virtual VisitorImplementation<U, TList...>
    {
      public:
        template<typename... ParamList>
        explicit VisitorImplementation(ParamList&&... plist)
            : VisitorImplementation<U, TList...>(std::forward<ParamList>(plist)...)
        {}

        using VisitorImplementation<U, TList...>::visit;
        using VisitorImplementation<U, TList...>::u_;

        virtual std::any visit(T& t)
        {
            if constexpr (CanVisit<U, T>) { return u_->visit(t); }
            else {
                return {};
            }
        }
    };

    template<typename... TList>
    class Visitable
    {
        virtual std::any accept(Visitor<TList...>& visitor) = 0;

      private:
        typedef lang::Visitable<TList...> Self;

        std::vector<std::reference_wrapper<Self>> children_ {};

      public:
        /**
         * Add a child to this visitable. The children are ordered in the way they are added.
         * @param child The child to add.
         */
        void addChild(Self& child) { children_.emplace_back(child); }

        /**
         * Get the number of children this visitable has.
         * @return The number of children.
         */
        size_t childCount() { return children_.size(); }

        /**
         * Get the child at the given index.
         * @param index The index of the child to get.
         * @return The child at the given index.
         */
        Visitable& getChild(size_t index) { return children_[index]; }
    };

    template<typename U, typename... TList>
    class GenericVisitor : public virtual VisitorImplementation<U, TList...>
    {
      public:
        using VisitorImplementation<U, TList...>::u_;

        template<typename... ParamList>
        explicit GenericVisitor(ParamList&&... plist)
            : VisitorImplementation<U, TList...>(std::forward<ParamList>(plist)...)
        {
            u_->setVisitor(this);
        }
    };

    /**
     * Offers the basic methods required by the generic visitor.
     * @tparam Derived The derived class.
     * @tparam TList The list of visitable types.
     */
    template<typename Derived, typename... TList>
    class VisitorBase
    {
      private:
        using V = GenericVisitor<Derived, TList...>;
        V* visitor_;

      protected:
        V& visitor() { return *visitor_; }

      public:
        void setVisitor(V* visitor) { visitor_ = visitor; }

        virtual void preVisit(Visitable<TList...>&) {}
        virtual void postVisit(Visitable<TList...>&) {}

        std::any visitSome(Visitable<TList...>& visitable)
        {
            std::any result;

            preVisit(visitable);
            result = visitable.accept(visitor());
            postVisit(visitable);

            return result;
        }

        virtual std::any initialize() { return {}; }
        virtual std::any accumulate(std::any&, std::any& next) { return next; }

        std::any visitChildren(Visitable<TList...>& visitable)
        {
            std::any result = initialize();

            for (size_t i = 0; i < visitable.childCount(); ++i)
            {
                std::any next = visit(visitable.getChild(i));
                result        = accumulate(result, next);
            }

            return result;
        }

        virtual ~VisitorBase() = default;
    };
}

#endif
