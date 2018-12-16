#include "Interfaces/VClient018.h"
#include "Managers/IManager.h"

namespace CodeNamePaste {
namespace Hooks {
extern Managers::IManager* hkManager;

void __fastcall hkFrameStageNotify(void* ecx,
                                   void* edx,
                                   Classes::ClientFrameStage_t stage);
}  // namespace Hooks
}  // namespace CodeNamePaste