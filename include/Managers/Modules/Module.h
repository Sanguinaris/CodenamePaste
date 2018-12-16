#pragma once
#include "IModule.h"

#include "Managers/Hooking/HookingManager.h"
#include "Managers/Interfaces/InterfaceManager.h"
#include "Managers/NetVars/NetvarManager.h"
#include "Managers/Offsets/OffsetManager.h"

#include <optional>

namespace CodeNamePaste::Managers {
namespace Modules {
	class ModuleManager;
class Module : public IModule {
	friend ModuleManager;
 public:
  Module(std::string&& name);

 public:
  bool DoShutdown() override;

 public:
  void Toggle() override;
  void SetState(bool state) override;

 public:
  const bool IsActive() const override;
  const std::string& GetModuleName() const override;

 protected:
  bool moduleState = false;

 protected:
  static std::optional<std::reference_wrapper<const Interfaces::InterfaceManager>>
      ifaceMgr;
  static std::optional<std::reference_wrapper<const NetVars::NetVarManager>> netMgr;
  static std::optional<std::reference_wrapper<const Offsets::OffsetManager>> offyMgr;
  static std::optional<std::reference_wrapper<Hooks::HookingManager>> hookMgr;

 private:
  const std::string moduleName;
};
}  // namespace Modules
}  // namespace CodeNamePaste::Managers
