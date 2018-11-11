#pragma once
#include <cstdint>
#include <type_traits>
#include <utility>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <Windows.h>
#include <Psapi.h>

#include "Managers/IManager.h"

namespace CodeNamePaste {
namespace Managers {
namespace Offsets {

template<unsigned int N>
struct PatternInfo
{
	unsigned int PatternSize;
    unsigned char Pattern[N];
    unsigned char Mask[N];
	constexpr explicit PatternInfo() : PatternSize{N}, Pattern {}, Mask{}
    {}
};

struct PatternSlice
{
	unsigned char cPattern;
	bool bIgnore;

	constexpr PatternSlice() : cPattern{}, bIgnore{ false } {}
};

enum class OffsetNames : uint8_t {
  EnginePtr,
  GameRes,
  GlobalVars,
  ClientMode,
  Size
};

#define GetOffsetWrap(inst, name) inst.GetOffset([] { return name; })
#define FindPatternWrap(inst, ret, mod, pattern) inst.FindPattern<ret>(mod, [] { return pattern; })
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

  template <typename ret, typename F>
  const ret* FindPattern(std::string&& mod, F func) {
	  auto info = BuildPattern<GetPatternSize(func)>(func);

	  
	HMODULE hModule = GetModuleHandleA(mod.c_str());
	
	if (hModule == INVALID_HANDLE_VALUE)
		return nullptr;
	
	MODULEINFO modInfo;
	GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));

    return FindPattern(reinterpret_cast<ret*>(modInfo.lpBaseOfDll), reinterpret_cast<ret*>(modInfo.lpBaseOfDll) + modInfo.SizeOfImage, std::move(info));
  }

private:
	template<typename ret, unsigned int N>
	ret* FindPattern(ret* start, ret* end, PatternInfo<N>&& info)
	{
		auto pattern = BuildArrPattern<N>(info.Pattern, info.Mask);

		auto addy = std::search(start, end, pattern.begin(), pattern.end(), 
            [&](unsigned char curr, const PatternSlice& currPattern) 
        { 
            return currPattern.bIgnore || curr == currPattern.cPattern; 
        });
		return (addy != end) ? addy : 0;
	}

 private:
  template<unsigned int N>
  static constexpr const std::array<PatternSlice, N> BuildArrPattern(const unsigned char* lpPattern, const unsigned char* pszMask)
  {
	  std::array<PatternSlice, N> ret{};
	  for (auto i = 0; i < N; ++i)
	  {
		  ret[i].cPattern = lpPattern[i];
		  ret[i].bIgnore = pszMask[i] == '?';
	  }
	  return ret;
  }

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


  template <typename F>
  static constexpr int GetPatternSize(F func)
  {
	  auto name = func();
	  int ret = 1;
	  for (auto i = 0; name[i] != '\0'; ++i)
	  {
		  if (name[i] == ' ')
			  ++ret;
	  }
	  return ret;
  }

  template <int L, typename F>
  static constexpr const PatternInfo<L> BuildPattern(F func)
  {
	  PatternInfo<L> info{};

	  auto idaSig = func();

	  unsigned char tmpChar = 0;
	  auto curSigIdx = 0;
	  auto i = 0;
	  for (; idaSig[i] != '\0'; ++i)
	  {
		  if (idaSig[i] == ' ' && idaSig[i - 1] != '?')
		  {
			  info.Pattern[curSigIdx] = tmpChar;
			  info.Mask[curSigIdx] = 'x';

			  tmpChar = 0;
			  ++curSigIdx;
		  }
		  else if (idaSig[i] == '?' && idaSig[i + 1] != '?')
		  {
			info.Pattern[curSigIdx] = '\x00';
			info.Mask[curSigIdx] = '?';
			++curSigIdx;
		  }
		  else if (idaSig[i] != '?' && idaSig[i] != ' ')
		  {
			  tmpChar *= 16;
			  tmpChar += (idaSig[i] >= 'a') ? idaSig[i] - ('a' + 10) : (idaSig[i] >= 'A') ? idaSig[i] - ('A' + 10) : idaSig[i] - '0';
		  }
	  }
	  if (idaSig[i - 1] != '?')
	  {
		  info.Pattern[curSigIdx] = tmpChar;
		  info.Mask[curSigIdx] = 'x';
	  }

	  return info;
  }

 private:
  AutoNum addrOffsets[static_cast<uint8_t>(OffsetNames::Size)] = {0};
};
}  // namespace Offsets
}  // namespace Managers
}  // namespace CodeNamePaste
