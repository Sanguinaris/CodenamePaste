#include "Managers/Offsets/OffsetManager.h"

using namespace CodeNamePaste;
using namespace Managers;
using namespace Offsets;

OffsetManager::OffsetManager(const NetVars::NetVarManager& nvarMgr) : netVarMgr{ nvarMgr } {}

void OffsetManager::DoInit() {
	
}

void OffsetManager::DoTick() {}

bool OffsetManager::DoShutdown() {
  return true;
}
