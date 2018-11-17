#include "Managers/NetVars/NetvarManager.h"
#include "Interfaces/VClient018.h"

#include <string_view>

using namespace CodeNamePaste::Managers::NetVars;
using namespace CodeNamePaste::Managers::Interfaces;

NetVarManager::NetVarManager(InterfaceManager& ifaceMgr) : ifaceMgr{ifaceMgr} {}

void NetVarManager::DoInit() {
  tables.clear();

  for (auto client = GetInterfaceWrap(ifaceMgr, IBaseClientDLL, "VClient")
                         ->GetAllClasses();
       client; client = client->m_pNext) {
    auto recvTable = client->m_pRecvTable;
    if (recvTable)
      tables.emplace(std::string{client->GetName()}, recvTable);
  }
}

void NetVarManager::DoTick() {}

bool NetVarManager::DoShutdown() {
  return true;
}

const CodeNamePaste::Managers::AutoNum NetVarManager::GetProp(
    const std::string& tableName,
    const std::string& propName,
    RecvProp** prop) const {
  const auto recvTable = tables.find(tableName);
  if (recvTable == tables.end() || !recvTable->second)
    return 0;
  return GetProp(*(recvTable->second), propName, prop);
}

const CodeNamePaste::Managers::AutoNum NetVarManager::GetProp(
    const RecvTable& recvTable,
    const std::string& propName,
    RecvProp** prop) const {
  AutoNum addOffy = 0;

  for (auto i = 0; i < recvTable.m_nProps; ++i) {
    auto& recvProp = recvTable.m_pProps[i];
    auto recvChild = recvProp.m_pDataTable;

    if (recvChild && recvChild->m_nProps > 0) {
      addOffy += recvProp.m_Offset + GetProp(*recvChild, propName, prop);
    }

    if (std::string_view{recvProp.m_pVarName} != propName)
      continue;

    if (prop)
      *prop = &recvProp;

    return recvProp.m_Offset + addOffy;
  }
  return addOffy;
}
