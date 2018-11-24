#include "Managers/Modules/ModuleManager.h"

using namespace CodeNamePaste::Managers;
using namespace Modules;

ModuleManager::ModuleManager(const Interfaces::InterfaceManager& ifaceMgr,
                             const NetVars::NetVarManager& netMgr,
                             const Offsets::OffsetManager& offyMgr,
                             Hooks::HookingManager& hookMgr)
    : ifaceMgr{ifaceMgr}, netMgr{netMgr}, offyMgr{offyMgr}, hookMgr{hookMgr} {}

void ModuleManager::DoInit() {
  for (const auto& mod : modules)
    mod->DoInit(ifaceMgr, netMgr, offyMgr, hookMgr);
}

void ModuleManager::DoTick() {}

bool ModuleManager::DoShutdown() {
  for (const auto& mod : modules)
    if (!mod->DoShutdown())
      continue;  // TODO: add logging
  return true;
}

void ModuleManager::RegisterModule(std::unique_ptr<IModule>&& mod) {
  modules.emplace_back(std::move(mod));
}
