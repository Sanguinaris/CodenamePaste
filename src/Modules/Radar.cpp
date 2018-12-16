#include "Modules/Radar.h"

using namespace CodeNamePaste;
using namespace Modules;

Radar::Radar() : Module::Module{"Radar"} {
  pEntList = GetInterfaceWrap((ifaceMgr->get()), Interfaces::IClientEntityList,
                              "VClientEntityList");
  pGlobalVars = GetOffsetWrapP((offyMgr->get()), Classes::CGlobalVars, "GlobalVars");
  OnFrameStageNotiftClbk = RegisterCallbackWrap(
      hookMgr->get(), "FrameStageNotify", [this](const auto pStage) {
        this->DoRadar(*static_cast<Classes::ClientFrameStage_t*>(pStage));
      });
}

bool Radar::DoShutdown() {
  return UnRegisterCallbackWrap(hookMgr->get(), "FrameStageNotify",
                                OnFrameStageNotiftClbk);
}

void Radar::DoRadar(Classes::ClientFrameStage_t stage) {
  for (auto i = 1; i < pGlobalVars->maxClients; ++i) {
    auto ent = pEntList->GetClientEntity(i);
	if (ent && true )//ent->m_bDormant())
	{

	}
  }
}
