#ifndef ANCE_CORE_OCCURRENCE_H
#define ANCE_CORE_OCCURRENCE_H

#include <cstdint>
#include <string>

namespace ance::core
{
    /// Describes how often something occurs across all terminating paths through a
    /// control-flow graph. The value is the most precise range that contains the
    /// observed cardinalities; use the query methods when testing a requirement that
    /// is also satisfied by a more precise value.
    class Occurrence
    {
      public:
        enum Value : uint8_t
        {
            /// There are no terminating paths to which an occurrence constraint applies.
            NOT_APPLICABLE,

            /// The thing does not occur on any terminating path.
            NEVER,

            /// The thing occurs zero or one times on every terminating path.
            AT_MOST_ONCE,

            /// The thing may occur any number of times on a terminating path.
            UNCONSTRAINED,

            /// The thing occurs exactly once on every terminating path.
            EXACTLY_ONCE,

            /// The thing occurs one or more times on every terminating path.
            AT_LEAST_ONCE,

            /// The thing occurs more than once on every terminating path.
            MORE_THAN_ONCE
        };

        Occurrence() = default;
        constexpr Occurrence(Value const value)
            : value_(value) {} // NOLINT(google-explicit-constructor)

                 operator Value() const; // NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        /// Whether the thing occurs at most once on every terminating path.
        /// This is vacuously true when there are no terminating paths.
        [[nodiscard]] bool isAtMostOnce() const;

        /// Whether the thing occurs at least once on every terminating path.
        /// This is vacuously true when there are no terminating paths.
        [[nodiscard]] bool isAtLeastOnce() const;

        /// Whether the thing occurs exactly once on every terminating path.
        /// This is vacuously true when there are no terminating paths.
        [[nodiscard]] bool isExactlyOnce() const;

        /// Get this occurrence as a string.
        /// @return The string.
        [[nodiscard]] std::string toString() const;

      private:
        Value value_ = NOT_APPLICABLE;
    };
}

#endif
