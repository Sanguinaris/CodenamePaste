#include "Managers/Modules/ModuleManager.h"

#include "Modules/AntiFlash.h"
#include "Modules/BunnyHop.h"
#include "Modules/Radar.h"

using namespace CodeNamePaste::Managers;
using namespace Modules;

ModuleManager::ModuleManager(const Interfaces::InterfaceManager& ifaceMgr,
                             const NetVars::NetVarManager& netMgr,
                             const Offsets::OffsetManager& offyMgr,
                             Hooks::HookingManager& hookMgr)
    : ifaceMgr{ifaceMgr}, netMgr{netMgr}, offyMgr{offyMgr}, hookMgr{hookMgr} {
	Module::hookMgr = hookMgr;
	Module::ifaceMgr = ifaceMgr;
	Module::netMgr = netMgr;
	Module::offyMgr = offyMgr;
}

void ModuleManager::DoInit() {
  RegisterModule(std::make_unique<CodeNamePaste::Modules::AntiFlash>());
  RegisterModule(std::make_unique<CodeNamePaste::Modules::BunnyHop>());
  RegisterModule(std::make_unique<CodeNamePaste::Modules::Radar>());
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
