#pragma once
#include "Managers/NetVars/NetvarManager.h"

namespace CodeNamePaste {
namespace Classes {
class CBaseEntity {
 public:
  static const Managers::NetVars::NetVarManager* Netvars;

 public:
  ADD_NETVAR(int, m_iHealth, "DT_CSPlayer", "m_iHealth")
};
}  // namespace Classes
}  // namespace CodeNamePaste
