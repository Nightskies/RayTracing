#pragma once
#include "Types.h"

#include <variant>
#include <random>

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

namespace Utils
{
    inline f32 random(f32 min = 0.0f, f32 max = 1.0f)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<f32> distribution(min, max);
        return distribution(gen);
    }
}