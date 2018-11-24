#include "Managers/Modules/Module.h"

using namespace CodeNamePaste::Managers;
using namespace Modules;

Module::Module(std::string&& name) : moduleName{std::move(name)} {}

void Module::DoInit() {}

void Module::DoInit(const Interfaces::InterfaceManager& ifaceMgr,
                    const NetVars::NetVarManager& netMgr,
                    const Offsets::OffsetManager& offMgr,
                    Hooks::HookingManager& hookMgr) {
  this->ifaceMgr = ifaceMgr;
  this->netMgr = netMgr;
  this->offyMgr = offMgr;
  this->hookMgr = hookMgr;

  DoInit();
}

bool Module::DoShutdown() {
  return true;
}

void Module::Toggle() {
  moduleState = !moduleState;
}

void Module::SetState(bool state) {
  moduleState = state;
}

const bool Module::IsActive() const {
  return moduleState;
}

const std::string& Module::GetModuleName() const {
  return moduleName;
}
