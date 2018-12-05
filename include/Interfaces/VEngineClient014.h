#pragma once

#include "Managers/Interfaces/InterfaceManager.h"

#include "Utils/QAngle.h"

namespace CodeNamePaste {
	namespace Interfaces {
		class VEngineClient014 {
		public:
			VFUNCTION(5, void(__thiscall*)(int& w, int& h), GetScreenSize)
			VFUNCTION(12, int(__thiscall*)(), GetLocalPlayer)
			VFUNCTION(19, void(__fastcall*)(void*, void*, Utils::QAngle& va), SetViewAngles)
			VFUNCTION(26, bool(__thiscall*)(), IsInGame)
			VFUNCTION(27, bool(__thiscall*)(), IsConnected)
		};

		using IClientEngine = VEngineClient014;
	}
}
