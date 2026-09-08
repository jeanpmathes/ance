#include "ControlFlowAnalysis.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Node.h"

namespace
{
    enum class Count : uint8_t
    {
        ZERO = 1 << 0,
        ONE  = 1 << 1,
        MANY = 1 << 2
    };

    Count operator+(Count const left, Count const right)
    {
        if (left == Count::ONE && right == Count::ONE) return Count::MANY;
        return std::max(left, right);
    }

    Count operator+(Count const left, size_t const right)
    {
        if (right == 0) return left;
        if (right == 1) return left + Count::ONE;
        return Count::MANY;
    }

    struct Counts
    {
        Counts() = default;
        Counts(Count const count) // NOLINT(google-explicit-constructor)
            : counts_(static_cast<uint8_t>(count))
        {}

        [[nodiscard]] bool contains(Count const count) const
        {
            return (counts_ & static_cast<uint8_t>(count)) != 0;
        }

        Counts& operator+=(Count const count)
        {
            Counts const previous = *this;
            counts_               = 0;

            if (previous.contains(Count::ZERO)) insert(Count::ZERO + count);
            if (previous.contains(Count::ONE)) insert(Count::ONE + count);
            if (previous.contains(Count::MANY)) insert(Count::MANY);

            return *this;
        }

        [[nodiscard]] Counts operator+(Count const count) const
        {
            Counts result = *this;
            result += count;
            return result;
        }

        Counts& operator|=(Counts const& other)
        {
            counts_ |= other.counts_;
            return *this;
        }

        [[nodiscard]] ance::core::Occurrence occurrence() const
        {
            bool const zero = contains(Count::ZERO);
            bool const one  = contains(Count::ONE);
            bool const many = contains(Count::MANY);

            if (zero)
            {
                if (!one && !many) return ance::core::Occurrence::NEVER;
                if (!many) return ance::core::Occurrence::AT_MOST_ONCE;
                return ance::core::Occurrence::UNCONSTRAINED;
            }

            if (one)
            {
                if (!many) return ance::core::Occurrence::EXACTLY_ONCE;
                return ance::core::Occurrence::AT_LEAST_ONCE;
            }

            assert(many);
            return ance::core::Occurrence::MORE_THAN_ONCE;
        }

        bool operator==(Counts const& other) const = default;

      private:
        void insert(Count const count)
        {
            counts_ |= static_cast<uint8_t>(count);
        }

        uint8_t counts_ = 0;
    };

    struct BBData
    {
        Count                                     count = Count::ZERO;
        std::vector<ance::bbt::BasicBlock const*> next  = {};
    };

    class AnalyzingVisitor final : public ance::bbt::Visitor
    {
      public:
        using Visitor::visit;

        explicit AnalyzingVisitor(
            ance::bbt::ControlFlowAnalysis::CounterFunction const& counter
        )
            : counter_(counter)
        {}

        BBData getData(ance::bbt::BasicBlock const& basic_block)
        {
            data_ = {};
            visit(basic_block);
            return data_;
        }

        void visit(ance::bbt::BasicBlock const& basic_block) override
        {
            for (auto const& statement : basic_block.statements)
            {
                data_.count = data_.count + counter_(*statement);
            }

            visit(*basic_block.link);
        }

        void visit(ance::bbt::Return const&) override
        {
            // A return ends the path.
        }

        void visit(ance::bbt::Branch const& branch_link) override
        {
            data_.next.emplace_back(&branch_link.true_branch);
            data_.next.emplace_back(&branch_link.false_branch);
        }

        void visit(ance::bbt::Jump const& jump_link) override
        {
            data_.next.emplace_back(&jump_link.target);
        }

        void visit(ance::bbt::Switch const& switch_link) override
        {
            for (auto const& switch_case : switch_link.cases)
            {
                data_.next.emplace_back(&switch_case->target);
            }
        }

        void visit(ance::bbt::Flows const&) override {}
        void visit(ance::bbt::UnorderedScope const&) override {}
        void visit(ance::bbt::Flow const&) override {}
        void visit(ance::bbt::ErrorLink const&) override {}
        void visit(ance::bbt::ErrorStatement const&) override {}
        void visit(ance::bbt::Pass const&) override {}
        void visit(ance::bbt::Assert const&) override {}
        void visit(ance::bbt::Store const&) override {}
        void visit(ance::bbt::Access const&) override {}
        void visit(ance::bbt::Temporary const&) override {}
        void visit(ance::bbt::Dereference const&) override {}
        void visit(ance::bbt::Intrinsic const&) override {}
        void visit(ance::bbt::Call const&) override {}
        void visit(ance::bbt::Subscript const&) override {}
        void visit(ance::bbt::FunctionConstructor const&) override {}
        void visit(ance::bbt::Constant const&) override {}
        void visit(ance::bbt::Default const&) override {}
        void visit(ance::bbt::CurrentScope const&) override {}
        void visit(ance::bbt::GetUnaryOperatorFunctionIdentifier const&) override {}
        void visit(ance::bbt::GetBinaryOperatorFunctionIdentifier const&) override {}
        void visit(ance::bbt::TypeOf const&) override {}
        void visit(ance::bbt::ArrayTypeConstructor const&) override {}
        void visit(ance::bbt::ArrayConstructor const&) override {}
        void visit(ance::bbt::OrderedScopeEnter const&) override {}
        void visit(ance::bbt::OrderedScopeExit const&) override {}
        void visit(ance::bbt::SetReturnValue const&) override {}
        void visit(ance::bbt::SwitchCase const&) override {}

      private:
        ance::bbt::ControlFlowAnalysis::CounterFunction const& counter_;
        BBData                                                 data_;
    };
}

ance::bbt::ControlFlowAnalysis::ControlFlowAnalysis(CounterFunction counter)
    : counter_(std::move(counter))
{}

ance::core::Occurrence ance::bbt::ControlFlowAnalysis::analyze(Flow const& flow) const
{
    AnalyzingVisitor visitor(counter_);

    std::unordered_map<BasicBlock const*, BBData> block_data;
    block_data.reserve(flow.blocks.size());
    for (auto const& block : flow.blocks)
    {
        block_data.emplace(block.get(), visitor.getData(*block));
    }

    std::unordered_map<BasicBlock const*, Counts> incoming_range;
    incoming_range.reserve(flow.blocks.size());
    incoming_range.emplace(&flow.entry, Count::ZERO);

    std::queue<BasicBlock const*> open;
    open.emplace(&flow.entry);
    while (!open.empty())
    {
        BasicBlock const* const block = open.front();
        open.pop();

        BBData const& data           = block_data.at(block);
        Counts const  outgoing_range = incoming_range.at(block) + data.count;

        for (BasicBlock const* const next : data.next)
        {
            auto [iterator, inserted] = incoming_range.emplace(next, outgoing_range);
            auto& [key, range]        = *iterator;

            Counts const previous_range = range;
            range |= outgoing_range;

            if (inserted || range != previous_range)
            {
                open.emplace(key);
            }
        }
    }

    bool   has_ending_path = false;
    Counts end_range;
    for (auto const& [block, range] : incoming_range)
    {
        BBData const& data = block_data.at(block);
        if (!data.next.empty()) continue;

        Counts const outgoing_range = range + data.count;

        if (!has_ending_path)
        {
            end_range       = outgoing_range;
            has_ending_path = true;
        }
        else
        {
            end_range |= outgoing_range;
        }
    }

    if (!has_ending_path) return core::Occurrence::NOT_APPLICABLE;
    return end_range.occurrence();
}
