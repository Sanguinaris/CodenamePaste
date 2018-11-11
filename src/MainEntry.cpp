#include <Windows.h>

#include "Managers/Interfaces/InterfaceManager.h"
#include "Managers/Offsets/OffsetManager.h"

#include <chrono>
#include <thread>
#include <utility>

using namespace std::chrono_literals;

// Inject injection handler here trigger page fault initialize us. unlink us.
// return execution

using namespace CodeNamePaste;
using namespace Managers;

HANDLE threadHandle;
bool ShouldRun = true;

DWORD WINAPI OffloadThread(LPVOID) {
  Offsets::OffsetManager offsetMgr{};
  Interfaces::InterfaceManager ifaceMgr{};

  try {
    offsetMgr.DoInit();
    ifaceMgr.DoInit();
  } catch (const std::runtime_error& ex) {
    throw;
  }
  FindPatternWrap(offsetMgr, int, "client.dll", "12 14 17 ?? 99");

  while (ShouldRun) {
    offsetMgr.DoTick();
    ifaceMgr.DoTick();
    std::this_thread::sleep_for(50ms);
  }

  ifaceMgr.DoShutdown();
  offsetMgr.DoShutdown();

  return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      DisableThreadLibraryCalls(hinstDLL);
      threadHandle =
          CreateThread(nullptr, 0, &OffloadThread, nullptr, 0, nullptr);
      break;
    case DLL_PROCESS_DETACH:
      ShouldRun = false;
      WaitForSingleObject(threadHandle, 200);
      break;
  }
  return TRUE;
}
