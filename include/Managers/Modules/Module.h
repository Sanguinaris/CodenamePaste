#pragma once
#include <optional>
#include "IModule.h"

namespace CodeNamePaste::Managers {
namespace Modules {
class Module : public IModule {
 public:
  Module(std::string&& name);

 public:
  void DoInit() override;
  void DoInit(const Interfaces::InterfaceManager&,
              const NetVars::NetVarManager&,
              const Offsets::OffsetManager&,
              Hooks::HookingManager&) override;
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
  std::optional<std::reference_wrapper<const Interfaces::InterfaceManager>>
      ifaceMgr;
  std::optional<std::reference_wrapper<const NetVars::NetVarManager>> netMgr;
  std::optional<std::reference_wrapper<const Offsets::OffsetManager>> offyMgr;
  std::optional<std::reference_wrapper<Hooks::HookingManager>> hookMgr;

 private:
  const std::string moduleName;
};
}  // namespace Modules
}  // namespace CodeNamePaste::Managers
