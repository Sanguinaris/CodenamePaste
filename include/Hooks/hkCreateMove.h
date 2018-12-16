#pragma once
#include "Classes/CUserCmd.h"
#include "Managers/IManager.h"

namespace CodeNamePaste {
namespace Hooks {
extern Managers::IManager* hkManager;

bool __fastcall hkCreateMove(void* ecx,
                             void* edx,
                             float sequence,
                             Classes::CUserCmd* userCMD);
}  // namespace Hooks
}  // namespace CodeNamePaste
