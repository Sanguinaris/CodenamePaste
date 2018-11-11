#include <Windows.h>

#include "Managers/Offsets/OffsetManager.h"

#include <thread>
#include <chrono>
#include <utility>

using namespace std::chrono_literals;

// Inject injection handler here trigger page fault initialize us. unlink us.
// return execution

using namespace CodeNamePaste;
using namespace Managers;
using namespace Offsets;

HANDLE threadHandle;
bool ShouldRun = true;

DWORD WINAPI OffloadThread(LPVOID)
{
	OffsetManager offsetMgr{};

	try {
		offsetMgr.DoInit();
	}
	catch (const std::runtime_error& ex)
	{

	}
	FindPatternWrap(offsetMgr, int, "client.dll", "12 14 17 ?? 99");

    while(ShouldRun)
    {
		offsetMgr.DoTick();
        std::this_thread::sleep_for(50ms);
    }

	offsetMgr.DoShutdown();
    
    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      DisableThreadLibraryCalls(hinstDLL);
      threadHandle = CreateThread(nullptr, 0, &OffloadThread, nullptr, 0, nullptr);
      break;
    case DLL_PROCESS_DETACH:
        ShouldRun = false;
        WaitForSingleObject(threadHandle, 200);
      break;
  }
  return TRUE;
}
