#pragma once
#include <cstdint>
#include <memory>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

using f32 = float;
using f64 = double;

template<class T>
using UPtr = std::unique_ptr<T>;

template<class T>
using SPtr = std::shared_ptr<T>;

const f32 INF = std::numeric_limits<f32>::infinity();