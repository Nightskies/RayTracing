#pragma once
#include "Types.h"

#include <variant>
#include <random>
#include <optional>
#include <glm/glm.hpp>

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

    inline glm::vec3 get_random_vector(f32 min = 0.0f, f32 max = 1.0f)
    {
        return { random(min, max), random(min, max), random(min, max) };
    }

    inline glm::vec3 random_in_unit_sphere()
    {
        while (true)
        {
            auto p = get_random_vector(-1.0f, 1.0f);
            if (glm::pow(glm::length(p), 2) >= 1)
            {
                continue;
            }

            return p;
        }
    }

    inline glm::vec3 random_unit_vector()
    {
        return glm::normalize(random_in_unit_sphere());
    }

    inline bool near_zero_vector(const glm::vec3& v)
    {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8f;
        return (glm::abs(v[0]) < s) && (glm::abs(v[1]) < s) && (glm::abs(v[2]) < s);
    }
}