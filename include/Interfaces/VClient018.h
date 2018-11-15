#pragma once
#include "Classes/NetVarStuff/ClientClass.h"

#include "Managers/Interfaces/InterfaceManager.h"



class VClient018
{
public:
	VFUNCTION(8, ClientClass * (__thiscall *)(), GetAllClasses)
	VFUNCTION(13, void (__thiscall *)(const char*), HudText)
	//  36   36 CHLClient::FrameStageNotify(ClientFrameStage_t)
	//  64   64 CHLClient::GetScreenWidth(void)
	//  65   65 CHLClient::GetScreenHeight(void)
	//  69   69 CHLClient::GetPlayerView(CViewSetup &)
	//  77   77 CHLClient::OnScreenSizeChanged(int, int) // For menu reshizzle this would be needed
	//  82   82 CHLClient::SetBlurFade(float) // sounds interesting
	//  89   89 CHLClient::IsChatRaised(void) // checking when using keybinds
};

using IBaseClientDLL = VClient018;
