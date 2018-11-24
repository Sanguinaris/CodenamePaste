#pragma once
#include <memory>
#include <vector>

#include "IModule.h"
#include "Managers/Hooking/HookingManager.h"
#include "Managers/IManager.h"
#include "Managers/Interfaces/InterfaceManager.h"
#include "Managers/NetVars/NetvarManager.h"
#include "Managers/Offsets/OffsetManager.h"

namespace CodeNamePaste::Managers {
namespace Modules {
class ModuleManager : public IManager {
 public:
  ModuleManager(const Interfaces::InterfaceManager& ifaceMgr,
                const NetVars::NetVarManager& netMgr,
                const Offsets::OffsetManager& offyMgr,
                Hooks::HookingManager& hookMgr);

 public:
  void RegisterModule(std::unique_ptr<IModule>&& mod);

 public:
  void DoInit() override;
  void DoTick() override;
  bool DoShutdown() override;

 private:
  const Interfaces::InterfaceManager& ifaceMgr;
  const NetVars::NetVarManager& netMgr;
  const Offsets::OffsetManager& offyMgr;
  Hooks::HookingManager& hookMgr;

 private:
  std::vector<std::unique_ptr<IModule>> modules{};
};
}  // namespace Modules
}  // namespace CodeNamePaste::Managers