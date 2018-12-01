#include "Managers/Offsets/OffsetManager.h"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

using namespace CodeNamePaste;
using namespace Managers;
using namespace Offsets;

OffsetManager::OffsetManager(const NetVars::NetVarManager& nvarMgr)
    : netVarMgr{nvarMgr} {}

void OffsetManager::DoInit() {
  HMODULE hModule;
  do {
    hModule = GetModuleHandleA("client_panorama.dll");
    if (hModule == nullptr)
      std::this_thread::sleep_for(100ms);
  } while (hModule == nullptr);

  MODULEINFO modInfo;
  GetModuleInformation(GetCurrentProcess(), hModule, &modInfo,
                       sizeof(MODULEINFO));
  // TODO refactor this shit
  addrOffsets[static_cast<uint8_t>(OffsetNames::LocalPlayer)] =
      reinterpret_cast<AutoNum>(FindPatternWrap(
          (*this), uint32_t, static_cast<uint8_t*>(modInfo.lpBaseOfDll),
          static_cast<uint8_t*>(modInfo.lpBaseOfDll) + modInfo.SizeOfImage,
          "A3 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 59 C3 6A"));
  addrOffsets[static_cast<uint8_t>(OffsetNames::LocalPlayer)] =
      (*reinterpret_cast<AutoNum*>(
          addrOffsets[static_cast<uint8_t>(OffsetNames::LocalPlayer)] + 1)) +
      0x10;
}

void OffsetManager::DoTick() {}

bool OffsetManager::DoShutdown() {
  return true;
}
