#include <Windows.h>

#include <thread>
#include <chrono>

using namespace chrono_literals;
// Inject injection handler here trigger page fault initialize us. unlink us.
// return execution
HANDLE threadHandle;
bool ShouldRun = true;

DWORD WINAPI OffloadThread(LPVOID)
{
    while(ShouldRun)
    {
        std::this_thread::sleep_for(50ms);
    }
    
    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      DisableThreadLibraryCalls(hinstDLL);
      threadHandle = CreateRemoteThread(nullptr, 0, &OffloadThread, nullptr, 0, nullptr);
      break;
    case DLL_PROCESS_DETACH:
        ShouldRun = false;
        WaitForSingleObject(threadHandle, 200);
      break;
  }
  return TRUE;
}
