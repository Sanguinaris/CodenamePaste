#include "Hack.h"

#include <Windows.h>

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

using namespace CodeNamePaste;

Hack::Hack() {
  AllocConsole();
  AttachConsole(GetCurrentProcessId());
  freopen_s(&pNewStdOut, "CON", "w", stdout);

  try {
    ifaceMgr.DoInit();
    netMgr.DoInit();
    offsetMgr.DoInit();
    hookMgr.DoInit();
    modMgr.DoInit();
  } catch (const std::exception& ex) {
    MessageBoxA(NULL, ex.what(), "ERROR", MB_OK | MB_ICONERROR);
    ShouldRun = false;
    UncleanUnload = true;
  }
}

bool Hack::Run() {
  if (!ShouldRun)
    return false;
  ifaceMgr.DoTick();
  netMgr.DoTick();
  offsetMgr.DoTick();
  hookMgr.DoTick();
  modMgr.DoTick();
  std::this_thread::sleep_for(50ms);
  return (GetAsyncKeyState(VK_F10) & 1) != 1;
}

void Hack::Shutdown() {
  if (UncleanUnload)
    return;
  modMgr.DoShutdown();
  hookMgr.DoShutdown();
  offsetMgr.DoShutdown();
  netMgr.DoShutdown();
  ifaceMgr.DoShutdown();

  fclose(pNewStdOut);
  FreeConsole();
}

void Hack::Unload() {
  ShouldRun = false;
}
