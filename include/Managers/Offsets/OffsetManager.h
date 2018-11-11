#pragma once
#include <cstdint>
#include <type_traits>

#include "Managers/IManager.h"

namespace CodeNamePaste {
namespace Managers {
namespace Offsets {

enum class OffsetNames : uint8_t {
  EnginePtr,
  GameRes,
  GlobalVars,
  ClientMode,
  Size
};
#define GetOffsetWrap(inst, name) inst.GetOffset([] { return name; })
using AutoNum = std::conditional_t<(sizeof(void*) == 8), uint64_t, uint32_t>;

class OffsetManager : public IManager {
 public:
  void DoInit() override;

  void DoTick() override;

  bool DoShutdown() override;

 public:
  template <typename F>
  const AutoNum GetOffset(F func) {
    return addrOffsets[static_cast<uint8_t>(GetEnumFromString(func))];
  }

  template <typename F>
  const AutoNum FindPattern(F func) {
    return {};
  }

 private:
  static constexpr const bool CompareString(const char* str1,
                                            const char* str2) {
    int i = 0;
    for (; str1[i] != '\0' && str2[i] != '\0'; ++i) {
      if (str1[i] != str2[i])
        return false;
    }

    if (str1[i] == '\0' && str2[i] == '\0')
      return true;
    return false;
  }

  template <typename F>
  static constexpr const OffsetNames GetEnumFromString_impl(F func) {
    if (CompareString(func(), "EnginePointer"))
      return OffsetNames::EnginePtr;
    if (CompareString(func(), "GameResources"))
      return OffsetNames::GameRes;
    if (CompareString(func(), "GlobalVars"))
      return OffsetNames::GlobalVars;
    if (CompareString(func(), "ClientMode"))
      return OffsetNames::ClientMode;
    return OffsetNames::Size;
  }

  template <typename F>
  static constexpr const OffsetNames GetEnumFromString(F func) {
    static_assert(GetEnumFromString_impl(func) != OffsetNames::Size);
    return GetEnumFromString_impl(func);
  }

 private:
  AutoNum addrOffsets[static_cast<uint8_t>(OffsetNames::Size)] = {0};
};
}  // namespace Offsets
}  // namespace Managers
}  // namespace CodeNamePaste
