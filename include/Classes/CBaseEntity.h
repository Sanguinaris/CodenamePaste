#pragma once
#include "Managers/NetVars/NetvarManager.h"

namespace CodeNamePaste {
namespace Classes {
class CBaseEntity {
 public:
  static const Managers::NetVars::NetVarManager* Netvars;

 public:
  ADD_NETVAR(int, m_iHealth, "CCSPlayer", "m_iHealth")
  ADD_NETVAR(float, m_flFlashDuration, "CCSPlayer", "m_flFlashDuration")
};
}  // namespace Classes
}  // namespace CodeNamePaste
