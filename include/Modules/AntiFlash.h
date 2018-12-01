#pragma once

#include "Managers/Modules/Module.h"

#include "Classes/CBaseEntity.h"

namespace CodeNamePaste {
namespace Modules {
class AntiFlash : public Managers::Modules::Module {
 public:
  AntiFlash();

 private:
  void DoInit() override;
  bool DoShutdown() override;

 private:
  void* OnTickClbk;

 private:
  Classes::CBaseEntity* pLocalPlayer = nullptr;
};
}  // namespace Modules
}  // namespace CodeNamePaste