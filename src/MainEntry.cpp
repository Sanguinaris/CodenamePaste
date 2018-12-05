#include "Hack.h"

// Inject injection handler here trigger page fault initialize us. unlink us.
// return execution

using namespace CodeNamePaste;

HANDLE threadHandle;
Hack hack{};

DWORD WINAPI OffloadThread(LPVOID mod) {

  while (hack.Run());

  hack.Shutdown();

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
      hack.Unload();
      WaitForSingleObject(threadHandle, 200);
      break;
  }
  return TRUE;
}
