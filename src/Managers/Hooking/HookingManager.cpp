#include "Managers/Hooking/HookingManager.h"

#include <stdexcept>

using namespace CodeNamePaste;

Managers::Hooks::HookingManager::HookingManager(const Interfaces::InterfaceManager& ifaceMgr, const Offsets::OffsetManager& offyMgr) : ifaceMgr{ ifaceMgr }, offyMgr{offyMgr}
{}

void Managers::Hooks::HookingManager::DoInit() {
	ClientMode = std::make_unique<Utils::VMTManager<CodeNamePaste::Interfaces::VClientMode>>(GetInterfaceWrap(ifaceMgr, CodeNamePaste::Interfaces::VClientMode, "VClientMode"));

	CodeNamePaste::Hooks::hkManager = this;
	if (!ClientMode->HookIndex(24, &CodeNamePaste::Hooks::hkCreateMove))
	{
		throw std::runtime_error{ "CreateMove failed to Hook" };
	}
}

void Managers::Hooks::HookingManager::DoTick() {
  std::shared_lock<std::shared_mutex> lock{mutex_};
  for (const auto& clbk : funcCallbacks[HookNames::OnTick]) {
    clbk(nullptr);
  }
}

bool Managers::Hooks::HookingManager::DoShutdown() {
  return true;
}
