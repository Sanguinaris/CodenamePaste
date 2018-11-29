#include "Managers/Offsets/OffsetManager.h"

using namespace CodeNamePaste;
using namespace Managers;
using namespace Offsets;

OffsetManager::OffsetManager(const NetVars::NetVarManager& nvarMgr)
    : netVarMgr{nvarMgr} {}

void OffsetManager::DoInit() {
	addrOffsets[static_cast<uint8_t>(OffsetNames::LocalPlayer)] = reinterpret_cast<AutoNum>(FindPatternWrap((*this), AutoNum, "client_panorama.dll", "A3 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 59 C3 6A"));
}

void OffsetManager::DoTick() {}

bool OffsetManager::DoShutdown() {
  return true;
}
