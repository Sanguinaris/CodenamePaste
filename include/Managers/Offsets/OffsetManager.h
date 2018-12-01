#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include <Windows.h>

#include <Psapi.h>

#include "Managers/IManager.h"

#include "Managers/NetVars/NetvarManager.h"

namespace CodeNamePaste::Managers {
namespace Offsets {

template <size_t N>
struct PatternInfo {
  unsigned char Pattern[N];
  unsigned char Mask[N];
  constexpr explicit PatternInfo() : Pattern{}, Mask{} {}
};

struct PatternSlice {
  unsigned char cPattern;
  bool bIgnore;

  constexpr PatternSlice() : cPattern{}, bIgnore{false} {}
};

enum class OffsetNames : uint8_t {
  LocalPlayer,
  EnginePtr,
  GameRes,
  GlobalVars,
  ClientMode,

  Size
};

#define GetOffsetWrap(inst, name) inst.GetOffset([] { return name; })
#define FindPatternWrap(inst, ret, start, end, pattern) \
  inst.FindPattern<ret>(start, end, [] { return pattern; })

class OffsetManager : public IManager {
 public:
  OffsetManager(const NetVars::NetVarManager& nvarMgr);

 public:
  void DoInit() override;

  void DoTick() override;

  bool DoShutdown() override;

 public:
  template <typename F>
  const AutoNum GetOffset(F func) const {
    return addrOffsets[static_cast<uint8_t>(GetEnumFromString(func))];
  }

  template <typename ret, typename F>
  const ret* FindPattern(const uint8_t* start, const uint8_t* end, F func) {
    constexpr auto pattern =
        BuildArrPattern(BuildPatternSignature<GetPatternSize(func())>(func()));

    auto addy = std::search(
        start, end, pattern.begin(), pattern.end(),
        [&](unsigned char curr, const PatternSlice& currPattern) {
          return currPattern.bIgnore || curr == currPattern.cPattern;
        });
    return (addy != end) ? reinterpret_cast<const ret*>(addy) : nullptr;
  }

 private:
  template <size_t N>
  static constexpr const std::array<PatternSlice, N> BuildArrPattern(
      const PatternInfo<N>&& info) {
    std::array<PatternSlice, N> ret{};
    for (auto i = 0u; i < N; ++i) {
      ret[i].cPattern = info.Pattern[i];
      ret[i].bIgnore = info.Mask[i] == '?';
    }
    return ret;
  }

  static constexpr const OffsetNames GetEnumFromString_impl(
      std::string_view name) {
    if (name == "LocalPlayer")
      return OffsetNames::LocalPlayer;
    if (name == "EnginePointer")
      return OffsetNames::EnginePtr;
    if (name == "GameResources")
      return OffsetNames::GameRes;
    if (name == "GlobalVars")
      return OffsetNames::GlobalVars;
    if (name == "ClientMode")
      return OffsetNames::ClientMode;
    return OffsetNames::Size;
  }

  template <typename F>
  static constexpr const OffsetNames GetEnumFromString(F func) {
    constexpr auto internalName = GetEnumFromString_impl(func());
    static_assert(internalName != OffsetNames::Size);
    return GetEnumFromString_impl(func());
  }

  static constexpr unsigned int GetPatternSize(const char* name) {
    unsigned int ret = 1;
    for (auto i = 0u; name[i] != '\0'; ++i) {
      if (name[i] == ' ')
        ++ret;
    }
    return ret;
  }

  template <size_t L>
  static constexpr const PatternInfo<L> BuildPatternSignature(
      const char* idaSig) {
    PatternInfo<L> info{};

    unsigned char tmpChar = 0;
    auto curSigIdx = 0;
    auto i = 0;
    for (; idaSig[i] != '\0'; ++i) {
      if (idaSig[i] == ' ' && idaSig[i - 1] != '?') {
        info.Pattern[curSigIdx] = tmpChar;
        info.Mask[curSigIdx] = 'x';

        tmpChar = 0;
        ++curSigIdx;
      } else if (idaSig[i] == '?' && idaSig[i + 1] != '?') {
        info.Pattern[curSigIdx] = '\x00';
        info.Mask[curSigIdx] = '?';
        ++curSigIdx;
      } else if (idaSig[i] != '?' && idaSig[i] != ' ') {
        tmpChar *= 16;
        if (idaSig[i] >= 'a')  // Lowercase letterz
        {
          tmpChar += idaSig[i] - ('a' + 10);
        } else if (idaSig[i] >= 'A')  // Uppercase letterz
        {
          tmpChar += idaSig[i] - 'A' + 10;
        } else {  // Numeros
          tmpChar += idaSig[i] - '0';
        }
      }
    }
    if (idaSig[i - 1] != '?') {
      info.Pattern[curSigIdx] = tmpChar;
      info.Mask[curSigIdx] = 'x';
    }

    return info;
  }

 private:
  const NetVars::NetVarManager& netVarMgr;

  AutoNum addrOffsets[static_cast<uint8_t>(OffsetNames::Size)] = {0};
};
}  // namespace Offsets
}  // namespace CodeNamePaste::Managers
