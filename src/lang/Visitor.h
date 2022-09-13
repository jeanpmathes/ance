#ifndef ANCE_SRC_LANG_VISITOR_H_
#define ANCE_SRC_LANG_VISITOR_H_

#include <any>
#include <cassert>
#include <memory>
#include <utility>

#include "Constructs.h"

/**
 * Code inspired by:
 * https://gist.github.com/tomas789/7844152
 */

namespace lang
{
    class VisitableBase
    {
      public:
        virtual ~VisitableBase() = default;
    };

    template<typename... Types>
    class Visitor;

    template<typename T>
    class Visitor<T>
    {
      protected:
        virtual std::any defaultVisit(VisitableBase* ptr) = 0;

      public:
        virtual std::any visit(T& visitable) { return this->defaultVisit(&visitable); }

        virtual ~Visitor() = default;
    };

    template<typename T, typename... TList>
    class Visitor<T, TList...> : public Visitor<TList...>
    {
      public:
        using Visitor<TList...>::visit;

        virtual std::any visit(T& visitable) { return this->defaultVisit(&visitable); }
    };

    template<typename... TList>
    class Visitable : public virtual VisitableBase
    {
      public:
        virtual std::any accept(Visitor<TList...>& visitor) = 0;

      private:
        typedef lang::Visitable<TList...>         Self;
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

        /**
         * Clear all children from this visitable.
         */
        void clearChildren() { children_.clear(); }
    };

    /**
     * Offers the basic methods for visitor and tree functionality.
     * @tparam TList The list of visitable types.
     */
    template<typename... TList>
    class VisitorBase : public Visitor<TList...>
    {
      public:
        using Visitor<TList...>::visit;

        virtual void preVisit(Visitable<TList...>&) {}
        virtual void postVisit(Visitable<TList...>&) {}

        /**
         * Correctly visit a visitable element. Use this instead of normal visit.
         * @param visitable The visitable to visit.
         * @return The result of the visit.
         */
        std::any visitTree(Visitable<TList...>& visitable)
        {
            std::any result;

            preVisit(visitable);
            Visitor<TList...>& visitor = *this;
            result                     = visitable.accept(visitor);
            postVisit(visitable);

            return result;
        }

        virtual std::any initialize() { return {}; }
        virtual std::any accumulate(std::any&, std::any& next) { return next; }

        /**
         * Visit all children of a visitable element.
         * @param visitable The visitable to visit all children of.
         * @return The result of the visit.
         */
        std::any visitChildren(Visitable<TList...>& visitable)
        {
            std::any result = initialize();

            for (size_t i = 0; i < visitable.childCount(); ++i)
            {
                std::any next = visitTree(visitable.getChild(i));
                result        = accumulate(result, next);
            }

            return result;
        }

        ~VisitorBase() override = default;

      protected:
        std::any defaultVisit(VisitableBase* ptr) override
        {
            auto* visitable = dynamic_cast<Visitable<TList...>*>(ptr);
            assert(visitable != nullptr && "Visitable is not of the correct type.");
            return visitChildren(*visitable);
        }
    };
}

#endif

