#pragma once

#include "Classes/CBaseHandle.h"
#include "Classes/IEntity.h"

class VClientEntityList003 {
 public:
  virtual IClientNetworkable* GetClientNetworkable(int entnum) = 0;
  virtual IClientNetworkable* GetClientNetworkableFromHandle(
      CBaseHandle hEnt) = 0;
  virtual IClientUnknown* GetClientUnknownFromHandle(CBaseHandle hEnt) = 0;
  virtual IClientEntity* GetClientEntity(int entum) = 0;
  virtual IClientEntity* GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
  virtual int NumberOfEntities(bool bIncludeNonNetworkable) = 0;
  virtual int GetHighestEntityIndex() = 0;
  virtual void SetMaxEntities(int maxents) = 0;
  virtual int GetMaxEntities() = 0;
};

using IClientEntityList = VClientEntityList003;
