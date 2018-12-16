#pragma once
#include "Managers/NetVars/NetvarManager.h"
#include "Managers/Offsets/OffsetManager.h"

namespace CodeNamePaste {
namespace Classes {
enum PlayerFlags : int {
  FL_ONGROUND = (1 << 0),
  FL_DUCKING = (1 << 1),
  FL_ANIMDUCKING = (1 << 2),
  FL_WATERJUMP = (1 << 3),
  FL_ONTRAIN = (1 << 4),
  FL_INRAIN = (1 << 5),
  FL_FROZEN = (1 << 6),
  FL_ATCONTROLS = (1 << 7),
  FL_CLIENT = (1 << 8),
  FL_FAKECLIENT = (1 << 9),
  FL_INWATER = (1 << 10),
  FL_FLY = (1 << 11),
  FL_SWIM = (1 << 12),
  FL_CONVEYOR = (1 << 13),
  FL_NPC = (1 << 14),
  FL_GODMODE = (1 << 15),
  FL_NOTARGET = (1 << 16),
  FL_AIMTARGET = (1 << 17),
  FL_PARTIALGROUND = (1 << 18),
  FL_STATICPROP = (1 << 19),
  FL_GRAPHED = (1 << 20),
  FL_GRENADE = (1 << 21),
  FL_STEPMOVEMENT = (1 << 22),
  FL_DONTTOUCH = (1 << 23),
  FL_BASEVELOCITY = (1 << 24),
  FL_WORLDBRUSH = (1 << 25),
  FL_OBJECT = (1 << 26),
  FL_KILLME = (1 << 27),
  FL_ONFIRE = (1 << 28),
  FL_DISSOLVING = (1 << 29),
  FL_TRANSRAGDOLL = (1 << 30),
  FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
};

class CBaseEntity {
 public:
  static const Managers::NetVars::NetVarManager* Netvars;
  static const Managers::Offsets::OffsetManager* Offsets;

 public:
  ADD_NETVAR(int, m_iHealth, "CCSPlayer", "m_iHealth")
  ADD_NETVAR(float, m_flFlashDuration, "CCSPlayer", "m_flFlashDuration")
  ADD_NETVAR(PlayerFlags, m_fFlags, "CBasePlayer", "m_fFlags")
  ADD_NETVAR(bool, m_bSpotted, "CBaseEntity", "m_bSpotted")
  bool& m_bDormant();
};
}  // namespace Classes
}  // namespace CodeNamePaste
