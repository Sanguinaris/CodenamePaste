#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include "Managers/IManager.h"

namespace CodeNamePaste {
namespace Managers {
namespace Interfaces {

enum class InterfaceNames : uint8_t {
  VClient018,
  VClientEntityList003,
  VEngineClient014,
  VMaterialSystem080,
  VClientMode,
  Size
};

#define GetInterfaceWrap(inst, type, name) \
  inst.GetInterface<type>([] { return name; })

#define VFUNCTION(idx, fnPtrType, name)                             \
  template <typename... Args>                                       \
  auto name(Args&&... args) {                                       \
    return reinterpret_cast<fnPtrType>((*reinterpret_cast<char***>( \
        this))[idx])(this, nullptr, std::forward<Args>(args)...);   \
  }

class InterfaceManager : public IManager {
 public:
  void DoInit() override;
  void DoTick() override;
  bool DoShutdown() override;

 public:
  template <typename T, typename F>
  T* GetInterface(F func) const {
    return reinterpret_cast<T*>(
        ifaceAddys[static_cast<uint8_t>(GetEnumFromString(func))]);
  }

 private:
  AutoNum* GetInterface(void* CreateInterfaceExp, std::string&& ifaceName);

 private:
  static constexpr const InterfaceNames GetEnumFromString_impl(
      std::string_view name) {
    if (name == "VClient")
      return InterfaceNames::VClient018;
    if (name == "VClientEntityList")
      return InterfaceNames::VClientEntityList003;
    if (name == "VEngineClient")
      return InterfaceNames::VEngineClient014;
    if (name == "VMaterialSystem")
      return InterfaceNames::VMaterialSystem080;
    if (name == "VClientMode")
      return InterfaceNames::VClientMode;
    return InterfaceNames::Size;
  }

  template <typename F>
  static constexpr const InterfaceNames GetEnumFromString(F func) {
    constexpr auto internalName = GetEnumFromString_impl(func());
    static_assert(internalName != InterfaceNames::Size);
    return internalName;
  }

 private:
  AutoNum* ifaceAddys[static_cast<uint8_t>(InterfaceNames::Size)] = {nullptr};
};
}  // namespace Interfaces
}  // namespace Managers
}  // namespace CodeNamePaste
