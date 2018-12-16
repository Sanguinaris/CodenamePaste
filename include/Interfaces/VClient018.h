#pragma once
#include "Classes/NetVarStuff/ClientClass.h"

#include "Managers/Interfaces/InterfaceManager.h"

namespace CodeNamePaste {
	namespace Classes {
		enum ClientFrameStage_t
{
    FRAME_UNDEFINED = -1,
    FRAME_START,
    FRAME_NET_UPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_END,
    FRAME_NET_UPDATE_END,
    FRAME_RENDER_START,
    FRAME_RENDER_END
};
	}
namespace Interfaces {
class VClient018 {
 public:
	 VFUNCTION(8, Classes::ClientClass*(__fastcall*)(void*, void*), GetAllClasses)
	 VFUNCTION(13, void(__fastcall*)(void*, void*, const char*), HudText)
	 VFUNCTION(37, void(__fastcall*)(void*, void*, Classes::ClientFrameStage_t), FrameStageNotify)
  //  36   36 CHLClient::FrameStageNotify(ClientFrameStage_t)
  //  64   64 CHLClient::GetScreenWidth(void)
  //  65   65 CHLClient::GetScreenHeight(void)
  //  69   69 CHLClient::GetPlayerView(CViewSetup &)
  //  77   77 CHLClient::OnScreenSizeChanged(int, int) // For menu reshizzle
  //  this would be needed 82   82 CHLClient::SetBlurFade(float) // sounds
  //  interesting 89   89 CHLClient::IsChatRaised(void) // checking when using
  //  keybinds
};

using IBaseClientDLL = VClient018;
}  // namespace Interfaces
}  // namespace CodeNamePaste
