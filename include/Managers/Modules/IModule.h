#pragma once

#include "Managers/Hooking/HookingManager.h"
#include "Managers/Interfaces/InterfaceManager.h"
#include "Managers/NetVars/NetvarManager.h"
#include "Managers/Offsets/OffsetManager.h"

#include <string>

namespace CodeNamePaste::Managers {
namespace Modules {
class IModule {
 public:
  virtual ~IModule() = default;

 public:
  virtual void DoInit() = 0;
  virtual void DoInit(const Interfaces::InterfaceManager&,
                      const NetVars::NetVarManager&,
                      const Offsets::OffsetManager&,
                      Hooks::HookingManager&) = 0;
  virtual bool DoShutdown() = 0;

 public:
  virtual void Toggle() = 0;
  virtual void SetState(bool state) = 0;

 public:
  virtual const std::string& GetModuleName() const = 0;
  virtual const bool IsActive() const = 0;
};
}  // namespace Modules
}  // namespace CodeNamePaste::Managers