#pragma once
#include "RecvTable.h"

namespace CodeNamePaste::Classes {
// https://github.com/pmrowla/hl2sdk-csgo/blob/master/public/client_class.h#L49
class ClientClass {
 public:
  void* m_pCreateFn;       // CreateClientClassFn		m_pCreateFn;
  void* m_pCreateEventFn;  // CreateEventFn				m_pCreateEventFn;	//
                           // Only called for event objects.
  char* m_pNetworkName;
  RecvTable* m_pRecvTable;
  ClientClass* m_pNext;
  int m_ClassID;  // Managed by the engine.
};
}  // namespace CodeNamePaste::Classes
