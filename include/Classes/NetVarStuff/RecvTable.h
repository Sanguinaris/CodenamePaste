#pragma once
#include "RecvProp.h"

namespace CodeNamePaste::Classes {
// https://github.com/pmrowla/hl2sdk-csgo/blob/master/public/dt_recv.h#L170
class RecvTable {
public:
  // Properties described in a table.
  RecvProp* m_pProps;
  int m_nProps;

  // The decoder. NOTE: this covers each RecvTable AND all its children (ie: its
  // children will have their own decoders that include props for all their
  // children).
  void* m_pDecoder;  // CRecvDecoder		*m_pDecoder;

  char* m_pNetTableName;  // The name matched between client and server.

  bool m_bInitialized;
  bool m_bInMainList;
};
}  // namespace CodeNamePaste::Classes
