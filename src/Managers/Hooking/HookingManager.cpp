#include "Managers/Hooking/HookingManager.h"

using namespace CodeNamePaste;
using namespace Managers;
using namespace Hooks;

void HookingManager::DoInit() {}
void HookingManager::DoTick() {
	std::shared_lock<std::shared_mutex> lock{ mutex_ };
	for (const auto& clbk : funcCallbacks[HookNames::OnTick])
	{
		clbk(nullptr);
	}
}
bool HookingManager::DoShutdown() {
	return true;
}


