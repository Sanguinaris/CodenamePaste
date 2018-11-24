#pragma once

#include "Managers/Interfaces/InterfaceManager.h"

class IEngineClient {
 public:
  VFUNCTION(5, void(__thiscall*)(int& w, int& h), GetScreenSize);
  VFUNCTION(12, int(__thiscall*)(), GetLocalPlayer);
};
