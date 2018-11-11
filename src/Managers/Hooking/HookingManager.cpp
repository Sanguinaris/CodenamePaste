#include "Managers/Hooking/HookingManager.h"

using namespace CodeNamePaste;
using namespace Managers;
using namespace Hooks;

void HookingManager::DoInit() {}
void HookingManager::DoTick() {
	for (const auto& clbk : funcCallbacks[HookNames::OnTick])
	{
		clbk(nullptr);
	}
}
bool HookingManager::DoShutdown() {
	return true;
}


