#pragma once

#include "Managers/Modules/Module.h"

#include "Interfaces/VClient018.h"
#include "Interfaces/VClientEntityList003.h"

#include "Classes/CGlobalVars.h"

namespace CodeNamePaste {
namespace Modules {
class Radar : public Managers::Modules::Module {
 public:
  Radar();

 private:
  bool DoShutdown() override;

 private:
  void DoRadar(Classes::ClientFrameStage_t stage);

 private:
  const void* OnFrameStageNotiftClbk;

 private:
  Interfaces::IClientEntityList* pEntList = nullptr;
  const Classes::CGlobalVars* pGlobalVars = nullptr;
};
}  // namespace Modules
}  // namespace CodeNamePaste
