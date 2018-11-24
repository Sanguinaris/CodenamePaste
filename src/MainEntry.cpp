#include <Windows.h>

#include "Managers/Hooking/HookingManager.h"
#include "Managers/Interfaces/InterfaceManager.h"
#include "Managers/Modules/ModuleManager.h"
#include "Managers/NetVars/NetvarManager.h"
#include "Managers/Offsets/OffsetManager.h"

#include "Classes/CBaseEntity.h"
#include "Modules/AntiFlash.h"

#include <chrono>
#include <thread>
#include <utility>

using namespace std::chrono_literals;

// Inject injection handler here trigger page fault initialize us. unlink us.
// return execution

using namespace CodeNamePaste;

HANDLE threadHandle;
bool ShouldRun = true;

DWORD WINAPI OffloadThread(LPVOID mod) {
  Managers::Interfaces::InterfaceManager ifaceMgr{};
  Managers::NetVars::NetVarManager netMgr{ifaceMgr};
  Managers::Offsets::OffsetManager offsetMgr{netMgr};
  Managers::Hooks::HookingManager hookMgr{};
  Managers::Modules::ModuleManager modMgr{ifaceMgr, netMgr, offsetMgr, hookMgr};

  Classes::CBaseEntity::Netvars = &netMgr;

  modMgr.RegisterModule(std::make_unique<Modules::AntiFlash>());

  ifaceMgr.DoInit();
  netMgr.DoInit();
  offsetMgr.DoInit();
  hookMgr.DoInit();
  modMgr.DoInit();

  while (ShouldRun) {
    ifaceMgr.DoTick();
    netMgr.DoTick();
    offsetMgr.DoTick();
    hookMgr.DoTick();
    modMgr.DoTick();
    std::this_thread::sleep_for(50ms);
  }

  modMgr.DoShutdown();
  hookMgr.DoShutdown();
  offsetMgr.DoShutdown();
  netMgr.DoShutdown();
  ifaceMgr.DoShutdown();

  FreeLibraryAndExitThread(static_cast<HMODULE>(mod), 0);
  return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      DisableThreadLibraryCalls(hinstDLL);
      threadHandle =
          CreateThread(nullptr, 0, &OffloadThread, hinstDLL, 0, nullptr);
      break;
    case DLL_PROCESS_DETACH:
      ShouldRun = false;
      WaitForSingleObject(threadHandle, 200);
      break;
  }
  return TRUE;
}
