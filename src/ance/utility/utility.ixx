// Code inspired by: https://gist.github.com/tomas789/7844152

export module utility;

import <vector>;

export namespace ance::utility
{
    class VisitableBase
    {
      public:
        virtual ~VisitableBase() = default;
    };

    template<typename ReturnType, typename... VisitableTypes>
    class Visitor;

    template<typename ReturnType, typename VisitableType>
    class Visitor<VisitableType>
    {
      public:
        virtual ReturnType visit(VisitableType const& visitable) = 0;

        virtual ~Visitor() = default;
    };

    template<typename ReturnType, typename VisitableType, typename... VisitableTypes>
    class Visitor<ReturnType, VisitableType, VisitableTypes...> : public Visitor<ReturnType, VisitableTypes...>
    {
      public:
        using Visitor<ReturnType, VisitableTypes...>::visit;

        ReturnType visit(VisitableType const& visitable) override = 0;
    };

    template<typename ReturnType, typename... VisitableTypes>
    class Visitable : public virtual VisitableBase
    {
      public:
        virtual ReturnType accept(Visitor<ReturnType, VisitableTypes...>& visitor) const = 0;

      private:
        std::vector<std::reference_wrapper<Visitable>> children_ {};

      public:
        /**
         * Add a child to this visitable. The children are ordered in the way they are added.
         * @param child The child to add.
         */
        void addChild(Visitable& child) { children_.emplace_back(child); }

        /**
         * Get the number of children this visitable has.
         * @return The number of children.
         */
        [[nodiscard]] size_t childCount() const { return children_.size(); }

        /**
         * Get the child at the given index.
         * @param index The index of the child to get.
         * @return The child at the given index.
         */
        Visitable& getChild(size_t index) { return children_[index]; }

        /**
         * Get the child at the given index.
         * @param index The index of the child to get.
         * @return The child at the given index.
         */
        Visitable const& getChild(size_t index) const { return children_[index]; }

        /**
         * Clear all children from this visitable.
         */
        void clearChildren() { children_.clear(); }
    };

    /**
     * Offers the basic methods for visitor and tree functionality.
     * @tparam ReturnType The return type of the visitor.
     * @tparam VisitableTypes The types of visitable elements the visitor can visit.
     */
    template<typename ReturnType, typename... VisitableTypes>
    class VisitorBase : public Visitor<ReturnType, VisitableTypes...>
    {
      public:
        using Visitor<ReturnType, VisitableTypes...>::visit;
        using Visitable = Visitable<ReturnType, VisitableTypes...>;

        virtual void preVisit(Visitable const&) {}
        virtual void postVisit(Visitable const&) {}

        [[nodiscard]] virtual ReturnType initialize() { return {}; }
        [[nodiscard]] virtual ReturnType accumulate(ReturnType& previous, ReturnType& next) { return next; }

        /**
         * Correctly visit a visitable element. Use this instead of normal visit.
         * @param visitable The visitable to visit.
         * @return The result of the visit.
         */
        ReturnType visitTree(Visitable const& visitable)
        {
            ReturnType result;

            preVisit(visitable);
            Visitor<ReturnType, VisitableTypes...>& visitor = *this;
            result                     = visitable.accept(visitor);
            postVisit(visitable);

            return result;
        }

        /**
         * Visit all children of a visitable element.
         * @param visitable The visitable to visit all children of.
         * @return The result of the visit.
         */
        ReturnType visitChildren(Visitable const& visitable)
        {
            ReturnType result = initialize();

            for (size_t i = 0; i < visitable.childCount(); ++i)
            {
                ReturnType next = visitTree(visitable.getChild(i));
                result        = accumulate(result, next);
            }

            return result;
        }

        ~VisitorBase() override = default;
    };
}
