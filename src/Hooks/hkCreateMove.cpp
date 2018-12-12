#include "..\..\include\Hooks\hkCreateMove.h"

#include "Managers/Hooking/HookingManager.h"

#include "Interfaces/VEngineClient014.h"

namespace CodeNamePaste {
namespace Hooks {
	Managers::IManager* hkManager;

	bool __fastcall hkCreateMove(void* ecx, void* edx, float sequence, Classes::CUserCmd* userCMD)
	{
		auto IEngineClient = GetInterfaceWrap(static_cast<CodeNamePaste::Managers::Hooks::HookingManager*>(hkManager)->ifaceMgr,
			Interfaces::IClientEngine, "VEngineClient");
		if (static_cast<CodeNamePaste::Managers::Hooks::HookingManager*>(hkManager)->ClientMode->GetOriginal()->CreateMove(sequence, userCMD))
 			IEngineClient->SetViewAngles(userCMD->viewangles);

		{
			std::shared_lock<std::shared_mutex> lock{static_cast<CodeNamePaste::Managers::Hooks::HookingManager*>(hkManager)->mutex_};
			  for (const auto& clbk : static_cast<CodeNamePaste::Managers::Hooks::HookingManager*>(hkManager)->funcCallbacks[CodeNamePaste::Managers::Hooks::HookNames::CreateMove]) {
				clbk(userCMD);
			  }
		}
		return false;
	}
}
}
