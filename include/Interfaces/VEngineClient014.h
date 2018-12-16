#pragma once

#include "Managers/Interfaces/InterfaceManager.h"

#include "Utils/QAngle.h"

namespace CodeNamePaste {
namespace Interfaces {
class VEngineClient014 {
 public:
  VFUNCTION(5, void(__fastcall*)(void*, void*, int& w, int& h), GetScreenSize)
  VFUNCTION(12, int(__fastcall*)(void*, void*), GetLocalPlayer)
  VFUNCTION(19,
            void(__fastcall*)(void*, void*, Utils::QAngle& va),
            SetViewAngles)
  VFUNCTION(26, bool(__fastcall*)(void*, void*), IsInGame)
  VFUNCTION(27, bool(__fastcall*)(void*, void*), IsConnected)
};

using IClientEngine = VEngineClient014;
}  // namespace Interfaces
}  // namespace CodeNamePaste
