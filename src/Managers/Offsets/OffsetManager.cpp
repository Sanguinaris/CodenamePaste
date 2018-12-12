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
          "8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF"));
  addrOffsets[static_cast<uint8_t>(OffsetNames::LocalPlayer)] =
      (*reinterpret_cast<AutoNum*>(
          addrOffsets[static_cast<uint8_t>(OffsetNames::LocalPlayer)] + 0x03)) +
      0x04;
}

void OffsetManager::DoTick() {}

bool OffsetManager::DoShutdown() {
  return true;
}
