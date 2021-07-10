#ifndef ANCE_SRC_MANAGEMENT_ELEMENTS_ELEMENT_H_
#define ANCE_SRC_MANAGEMENT_ELEMENTS_ELEMENT_H_

#include <optional>
#include <string>
#include <vector>

namespace data
{
    class Element
    {
      public:
        virtual std::optional<std::reference_wrapper<const data::Element>> operator[](const std::string& key) const;

        [[nodiscard]] virtual std::vector<std::reference_wrapper<const data::Element>>::const_iterator begin() const;

        [[nodiscard]] virtual std::vector<std::reference_wrapper<const data::Element>>::const_iterator end() const;

        [[nodiscard]] virtual std::optional<std::reference_wrapper<const std::string>> asString() const;

        [[nodiscard]] virtual std::optional<bool> asBool() const;

        virtual ~Element() = 0;

      private:
        inline static std::vector<std::reference_wrapper<const data::Element>> empty_vector_;
    };
}

#endif
