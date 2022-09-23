#pragma once
#include "Types.h"

#include <variant>

namespace Details
{
    namespace detail
    {
        template<class... Ts>
        struct overloaded : Ts...
        {
            using Ts::operator()...;
        };

        template<class... Ts>
        overloaded(Ts...)->overloaded<Ts...>;

    }

    template <typename Variant, typename... Matchers>
    auto match(Variant&& variant, Matchers&&... matchers)
    {
        return std::visit(
            detail::overloaded{ std::forward<Matchers>(matchers)... },
            std::forward<Variant>(variant));
    }
}