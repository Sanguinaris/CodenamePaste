#include "Modules/AntiFlash.h"

using namespace CodeNamePaste;
using namespace Modules;

AntiFlash::AntiFlash() : Module::Module{"AntiFlash"} {}

void AntiFlash::DoInit() {
  pLocalPlayer = reinterpret_cast<Classes::CBaseEntity*>(
      GetOffsetWrap(offyMgr->get(), "LocalPlayer"));
  OnTickClbk =
      RegisterCallbackWrap(hookMgr->get(), "OnTick", [this](const auto) {
        if (pLocalPlayer)
          pLocalPlayer->m_flFlashDuration() = 0;
      });
}

bool CodeNamePaste::Modules::AntiFlash::DoShutdown() {
  return UnRegisterCallbackWrap(hookMgr->get(), "OnTick", OnTickClbk);
}
