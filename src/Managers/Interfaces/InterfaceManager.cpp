#include "Managers/Interfaces/InterfaceManager.h"

#include <stdexcept>
#include <string_view>

#include <Windows.h>

using namespace CodeNamePaste;
using namespace Managers;
using namespace Interfaces;

void InterfaceManager::DoInit() {
  {  // Material System
    AutoNum* ifaceFn = reinterpret_cast<AutoNum*>(GetProcAddress(
        GetModuleHandleA("materialsystem.dll"), "CreateInterface"));
    ifaceAddys[static_cast<uint8_t>(InterfaceNames::VMaterialSystem080)] =
        GetInterface(ifaceFn, "VMaterialSystem080");
  }
  {
    // Material System
    AutoNum* ifaceFn = reinterpret_cast<AutoNum*>(GetProcAddress(
        GetModuleHandleA("client_panorama.dll"), "CreateInterface"));
    ifaceAddys[static_cast<uint8_t>(InterfaceNames::VClient018)] =
        GetInterface(ifaceFn, "VClient018");
    ifaceAddys[static_cast<uint8_t>(InterfaceNames::VClientEntityList003)] =
        GetInterface(ifaceFn, "VClientEntityList003");
  }
  {
    AutoNum* ifaceFn = reinterpret_cast<AutoNum*>(
        GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"));
    ifaceAddys[static_cast<uint8_t>(InterfaceNames::VEngineClient)] =
        GetInterface(ifaceFn, "VEngineClient");
  }

  for (auto i = 0; i < static_cast<uint8_t>(InterfaceNames::Size); ++i)
    if (!ifaceAddys[i])
      MessageBoxW(nullptr, L"Not all interfaces found\nexpect this to crash",
                  L"Error", MB_ICONERROR | MB_OK);
}

void InterfaceManager::DoTick() {}
bool InterfaceManager::DoShutdown() {
  return true;
}

typedef void* (*InstantiateInterfaceFn)();

class InterfaceReg {
 public:
  InterfaceReg(InstantiateInterfaceFn fn, const char* pName);

 public:
  InstantiateInterfaceFn m_CreateFn;
  const char* m_pName;

  InterfaceReg* m_pNext;  // For the global list.
};

AutoNum* InterfaceManager::GetInterface(void* CreateInterfaceExp,
                                        std::string&& name) {
  auto jmpStart = reinterpret_cast<AutoNum>(CreateInterfaceExp) + 4;
  auto jmpTarget = jmpStart + *reinterpret_cast<AutoNum*>(jmpStart + 1) + 5;

  auto* ifaceRegList = **reinterpret_cast<InterfaceReg***>(jmpTarget + 6);

  for (auto* cur = ifaceRegList; cur; cur = cur->m_pNext) {
    if (std::string_view{cur->m_pName} == name)
      return reinterpret_cast<AutoNum*>(cur->m_CreateFn());
  }
  return nullptr;
}
