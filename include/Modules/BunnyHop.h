#pragma once

#include "Managers/Modules/Module.h"

#include "Classes/CBaseEntity.h"

namespace CodeNamePaste {
namespace Modules {
class BunnyHop : public Managers::Modules::Module {
 public:
  BunnyHop();

 private:
  bool DoShutdown() override;

 private:
  void DoBunnyHop(Classes::CUserCmd*);

 private:
  const void* OnCreateMoveClbk;

 private:
  Classes::CBaseEntity* pLocalPlayer = nullptr;
};
}  // namespace Modules
}  // namespace CodeNamePaste
