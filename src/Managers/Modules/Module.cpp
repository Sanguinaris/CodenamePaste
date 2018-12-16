#include "Managers/Modules/Module.h"

using namespace CodeNamePaste::Managers;
using namespace Modules;

std::optional<std::reference_wrapper<const Interfaces::InterfaceManager>>
      CodeNamePaste::Managers::Modules::Module::ifaceMgr;
std::optional<std::reference_wrapper<const NetVars::NetVarManager>> CodeNamePaste::Managers::Modules::Module::netMgr;
std::optional<std::reference_wrapper<const Offsets::OffsetManager>> CodeNamePaste::Managers::Modules::Module::offyMgr;
std::optional<std::reference_wrapper<Hooks::HookingManager>> CodeNamePaste::Managers::Modules::Module::hookMgr;

Module::Module(std::string&& name) : moduleName{std::move(name)} {}

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
