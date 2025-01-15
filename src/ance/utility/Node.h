#ifndef ANCE_UTILITY_NODE_H
#define ANCE_UTILITY_NODE_H

namespace ance::utility
{
    template<typename VisitorT>
    class AbstractNode
    {
      public:
        virtual ~AbstractNode() = default;

        virtual void accept(VisitorT& visitor) const = 0;
    };

    template<typename T, typename VisitorT>
    class ConcreteNode : public virtual AbstractNode<VisitorT>
    {
      public:
        ~ConcreteNode() override = default;

        void accept(VisitorT& visitor) const override { visitor.visit(static_cast<T const&>(*this)); }
    };

    template<typename VisitorT>
    class AbstractVisitor
    {
      public:
        virtual ~AbstractVisitor() = default;

        void visit(AbstractNode<VisitorT> const& node) { node.accept(static_cast<VisitorT&>(*this)); }
    };
}

#endif
