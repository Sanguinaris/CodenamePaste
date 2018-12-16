#include "Modules/BunnyHop.h"

#include "..\..\include\Modules\Radar.h"
#include "Classes/CUserCmd.h"

using namespace CodeNamePaste;
using namespace Modules;

BunnyHop::BunnyHop() : Module{"Bunny Hop"} {}

void BunnyHop::DoInit() {
  pLocalPlayer = reinterpret_cast<Classes::CBaseEntity*>(
      GetOffsetWrap(offyMgr->get(), "LocalPlayer"));
  OnCreateMoveClbk =
      RegisterCallbackWrap(hookMgr->get(), "CreateMove", [this](auto pUserCmd) {
        if (!pUserCmd)
          return;
        DoBunnyHop(reinterpret_cast<Classes::CUserCmd*>(pUserCmd));
      });
}

bool BunnyHop::DoShutdown() {
  return UnRegisterCallbackWrap(hookMgr->get(), "CreateMove", OnCreateMoveClbk);
}

void BunnyHop::DoBunnyHop(Classes::CUserCmd* userCmd) {
  if (!(pLocalPlayer->m_fFlags() & Classes::PlayerFlags::FL_ONGROUND))
    if (userCmd->buttons & IN_JUMP)
      userCmd->buttons &= ~IN_JUMP;
}
