#include <format>

std::string ance::bbt::Flow::id() const
{
    return identifier;
}

bool ance::bbt::Statement::isRelevantForReachability() const
{
    return true;
}

std::string ance::bbt::Temporary::id() const
{
    return std::format("t\"{}\"", identifier);
}

bool ance::bbt::OrderedScopeEnter::isRelevantForReachability() const
{
    return false;
}

bool ance::bbt::OrderedScopeExit::isRelevantForReachability() const
{
    return false;
}
