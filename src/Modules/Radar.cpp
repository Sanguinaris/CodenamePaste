#include "Modules/Radar.h"

using namespace CodeNamePaste;
using namespace Modules;

Radar::Radar() : Module::Module{"Radar"} {}

void Radar::DoInit()
{
  pEntList = GetInterfaceWrap((ifaceMgr->get()), Interfaces::IClientEntityList, "VClientEntityList");
  OnFrameStageNotiftClbk =
      RegisterCallbackWrap(hookMgr->get(), "FrameStageNotify", [this](const auto pStage) {
	  this->DoRadar(*static_cast<Classes::ClientFrameStage_t*>(pStage));
      });
}

bool Radar::DoShutdown()
{
	return UnRegisterCallbackWrap(hookMgr->get(), "FrameStageNotify", OnFrameStageNotiftClbk);
}

void Radar::DoRadar(Classes::ClientFrameStage_t stage)
{
	for (auto i = 1; i < 12; ++i)
	{
		void* ent = nullptr;
		//auto ent = pEntList->GetClientEntity(i);
		if (ent)
		{

		}
		
	}
}
