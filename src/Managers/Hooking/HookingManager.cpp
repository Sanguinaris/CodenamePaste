#include "Managers/Hooking/HookingManager.h"

#include <stdexcept>

using namespace CodeNamePaste;

Managers::Hooks::HookingManager::HookingManager(
    const Interfaces::InterfaceManager& ifaceMgr,
    const Offsets::OffsetManager& offyMgr)
    : ifaceMgr{ifaceMgr}, offyMgr{offyMgr} {}

void Managers::Hooks::HookingManager::DoInit() {
  ClientMode = std::make_unique<
      Utils::VMTManager<CodeNamePaste::Interfaces::VClientMode>>(
      GetInterfaceWrap(ifaceMgr, CodeNamePaste::Interfaces::VClientMode,
                       "VClientMode"));
  BaseClientDll = std::make_unique<
      Utils::VMTManager<CodeNamePaste::Interfaces::IBaseClientDLL>>(
      GetInterfaceWrap(ifaceMgr, CodeNamePaste::Interfaces::IBaseClientDLL,
                       "VClient"));

  CodeNamePaste::Hooks::hkManager = this;
  if (!ClientMode->HookIndex(24, &CodeNamePaste::Hooks::hkCreateMove)) {
    throw std::runtime_error{"CreateMove failed to Hook"};
  }
  if (!BaseClientDll->HookIndex(37,
                                &CodeNamePaste::Hooks::hkFrameStageNotify)) {
    throw std::runtime_error{"FrameStageNotify failed to Hook"};
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
