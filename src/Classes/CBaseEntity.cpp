#include "Classes/CBaseEntity.h"

using namespace CodeNamePaste::Classes;
using namespace CodeNamePaste;

const Managers::NetVars::NetVarManager* CBaseEntity::Netvars = nullptr;
const Managers::Offsets::OffsetManager* CBaseEntity::Offsets = nullptr;

bool& CBaseEntity::m_bDormant() {
  static CodeNamePaste::Managers::AutoNum offset =
      GetOffsetWrap((*Offsets), "m_bDormant");
  return *(*reinterpret_cast<bool**>(this) + offset);
}
