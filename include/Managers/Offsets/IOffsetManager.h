#pragma once
#include <type_traits>
#include <cstdint>

namespace CodeNamePaste {
using AutoNum = std::conditional_t<(sizeof(void*) == 8), uint64_t, uint32_t>;

namespace Offsets {
class IOffsetManager {
public:
    virtual ~IOffsetManager() = default;
    virtual AutoNum GetOffset(const char* name) = 0;
    virtual AutoNum FindPattern(const char* pattern) = 0;
};
}
}
