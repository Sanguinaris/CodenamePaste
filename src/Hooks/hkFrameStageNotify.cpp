#include "Hooks/hkFrameStageNotify.h"

#include "Managers/Hooking/HookingManager.h" 


namespace CodeNamePaste {
	namespace Hooks {
		void __fastcall hkFrameStageNotify(void* ecx, void* edx, Classes::ClientFrameStage_t stage)
		{


			static_cast<CodeNamePaste::Managers::Hooks::HookingManager*>(hkManager)->BaseClientDll->GetOriginal()->FrameStageNotify(stage);

			{
				std::shared_lock<std::shared_mutex> lock{ static_cast<CodeNamePaste::Managers::Hooks::HookingManager*>(hkManager)->mutex_ };
				for (const auto& clbk : static_cast<CodeNamePaste::Managers::Hooks::HookingManager*>(hkManager)->funcCallbacks[CodeNamePaste::Managers::Hooks::HookNames::FrameStageNotify]) {
					clbk(&stage);
				}
			}


		}
	}
}
