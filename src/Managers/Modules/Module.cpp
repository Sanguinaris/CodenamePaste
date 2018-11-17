#include "Managers/Modules/Module.h"

using namespace CodeNamePaste::Managers::Modules;

Module::Module(std::string&& name) : moduleName{std::move(name)} {}

void Module::DoInit() {}

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
