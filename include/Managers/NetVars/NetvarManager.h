#pragma once
#include "Classes/NetVarStuff/RecvTable.h"
#include "Managers/IManager.h"
#include "Managers/Interfaces/InterfaceManager.h"

#include <unordered_map>

namespace CodeNamePaste {
namespace Managers {
namespace NetVars {
#define ADD_NETVAR(ret, name, table, prop)           \
  auto& name() {                                     \
    static CodeNamePaste::Managers::AutoNum offset = \
        Netvars->GetProperty(table, prop);           \
    return *reinterpret_cast<ret*>((*reinterpret_cast<char**>(this)) + offset);   \
  }

class NetVarManager : public IManager {
 public:
  NetVarManager(Interfaces::InterfaceManager& ifaceMgr);

 public:
  void DoInit() override;
  void DoTick() override;
  bool DoShutdown() override;

 public:
  const AutoNum GetProperty(const std::string& tableName,	// Originally GetProp but windows.h ain't no fun
                        const std::string& propName,
                        Classes::RecvProp** prop = nullptr) const;

 private:
  const AutoNum GetProp(const Classes::RecvTable& recvTable,
                        const std::string& propName,
                        Classes::RecvProp** prop = nullptr) const;

 private:
  Interfaces::InterfaceManager& ifaceMgr;
  std::unordered_map<std::string, Classes::RecvTable*> tables;
};
}  // namespace NetVars
}  // namespace Managers
}  // namespace CodeNamePaste
