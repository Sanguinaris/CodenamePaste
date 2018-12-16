#include "Managers/Offsets/OffsetManager.h"

#include "Classes/CBaseEntity.h"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

using namespace CodeNamePaste;
using namespace Managers;
using namespace Offsets;

OffsetManager::OffsetManager(const NetVars::NetVarManager& nvarMgr)
    : netVarMgr{nvarMgr} {
  Classes::CBaseEntity::Offsets = this;
}

void OffsetManager::DoInit() {
  HMODULE hModuleClient;
  HMODULE hModuleEngine;
  do {
    hModuleClient = GetModuleHandleA("client_panorama.dll");
    hModuleEngine = GetModuleHandleA("engine.dll");
    if (hModuleClient == nullptr || hModuleEngine == nullptr)
      std::this_thread::sleep_for(100ms);
  } while (hModuleClient == nullptr);


  { // client.dll sigs
	  MODULEINFO modInfo;
	  GetModuleInformation(GetCurrentProcess(), hModuleClient, &modInfo,
		  sizeof(MODULEINFO));

	  // dwLocalPlayer
	  addrOffsets[static_cast<uint8_t>(OffsetNames::LocalPlayer)] =
		  *reinterpret_cast<const AutoNum*>(
			  FindPatternWrap(
			  (*this), uint8_t, static_cast<uint8_t*>(modInfo.lpBaseOfDll),
				  static_cast<uint8_t*>(modInfo.lpBaseOfDll) + modInfo.SizeOfImage,
				  "8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF") +
			  0x03) +
		  0x04;

	  // m_bDormant
	  addrOffsets[static_cast<uint8_t>(OffsetNames::NetVars_mBDormant)] =
		  *reinterpret_cast<const AutoNum*>(
			  FindPatternWrap(
			  (*this), uint8_t, static_cast<uint8_t*>(modInfo.lpBaseOfDll),
				  static_cast<uint8_t*>(modInfo.lpBaseOfDll) + modInfo.SizeOfImage,
				  "8A 81 ? ? ? ? C3 32 C0") +
			  0x03) +
		  0x08;
  }
  { // engine.dll sigs
	  MODULEINFO modInfo;
	  GetModuleInformation(GetCurrentProcess(), hModuleEngine, &modInfo,
		  sizeof(MODULEINFO));

	  // CGlobalVars
	  addrOffsets[static_cast<uint8_t>(OffsetNames::GlobalVars)] =
		  *reinterpret_cast<const AutoNum*>(
			  FindPatternWrap(
			  (*this), uint8_t, static_cast<uint8_t*>(modInfo.lpBaseOfDll),
				  static_cast<uint8_t*>(modInfo.lpBaseOfDll) + modInfo.SizeOfImage,
				  "68 ? ? ? ? 68 ? ? ? ? FF 50 08 85 C0") +				// "g_ClientDLL->Init"
			  0x01);
  }
}

void OffsetManager::DoTick() {}

bool OffsetManager::DoShutdown() {
  return true;
}
