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

#include "Managers/NetVars/NetVarManager.h"

namespace CodeNamePaste::Managers {
namespace Offsets {

template <unsigned int N>
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
  EnginePtr,
  GameRes,
  GlobalVars,
  ClientMode,

  flashDuration,

  Size
};

#define GetOffsetWrap(inst, name) inst.GetOffset([] { return name; })
#define FindPatternWrap(inst, ret, mod, pattern) \
  inst.FindPattern<ret>(mod, [] { return pattern; })

class OffsetManager : public IManager {
public:
	OffsetManager(const NetVars::NetVarManager& nvarMgr);

 public:
  void DoInit() override;

  void DoTick() override;

  bool DoShutdown() override;

 public:
  template <typename F>
  const AutoNum GetOffset(F func) {
    return addrOffsets[static_cast<uint8_t>(GetEnumFromString(func))];
  }

  template <typename ret, typename F>
  const ret* FindPattern(std::string&& mod, F func) {
    auto info = BuildPatternSignature<GetPatternSize(func()), decltype(func)>(func);

    HMODULE hModule = GetModuleHandleA(mod.c_str());

    if (hModule == nullptr)
      return nullptr;

    MODULEINFO modInfo;
    GetModuleInformation(GetCurrentProcess(), hModule, &modInfo,
                         sizeof(MODULEINFO));

    return FindPattern(
        reinterpret_cast<ret*>(modInfo.lpBaseOfDll),
        reinterpret_cast<ret*>(modInfo.lpBaseOfDll) + modInfo.SizeOfImage,
        std::move(info));
  }

 private:
  template <typename ret, unsigned int N>
  ret* FindPattern(ret* start, ret* end, PatternInfo<N>&& info) {
    auto pattern = BuildArrPattern<N>(info.Pattern, info.Mask);

    auto addy = std::search(
        start, end, pattern.begin(), pattern.end(),
        [&](unsigned char curr, const PatternSlice& currPattern) {
          return currPattern.bIgnore || curr == currPattern.cPattern;
        });
    return (addy != end) ? addy : 0;
  }

 private:
  template <unsigned int N>
  static constexpr const std::array<PatternSlice, N> BuildArrPattern(
      const unsigned char* lpPattern,
      const unsigned char* pszMask) {
    std::array<PatternSlice, N> ret{};
    for (auto i = 0u; i < N; ++i) {
      ret[i].cPattern = lpPattern[i];
      ret[i].bIgnore = pszMask[i] == '?';
    }
    return ret;
  }

  template <typename F>
  static constexpr const OffsetNames GetEnumFromString_impl(std::string_view name) {
	  if (name == "EnginePointer")
      return OffsetNames::EnginePtr;
	  if (name == "GameResources")
      return OffsetNames::GameRes;
	  if (name == "GlobalVars")
      return OffsetNames::GlobalVars;
    if (name == "ClientMode")
      return OffsetNames::ClientMode;
	if (name == "Player_FlashDuration")
		return OffsetNames::flashDuration;
    return OffsetNames::Size;
  }

  template <typename F>
  static constexpr const OffsetNames GetEnumFromString(F func) {
    static_assert(GetEnumFromString_impl(func()) != OffsetNames::Size);
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

  template <unsigned int L, typename F>
  static constexpr const PatternInfo<L> BuildPatternSignature(F func) {
    PatternInfo<L> info{};

    auto idaSig = func();

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
        tmpChar +=
            (idaSig[i] >= 'a')
                ? idaSig[i] - ('a' + 10)
                : (idaSig[i] >= 'A') ? idaSig[i] - ('A' + 10) : idaSig[i] - '0';
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
}  // namespace Managers
