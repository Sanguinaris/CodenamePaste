#pragma once
#include "RecvProp.h"

// https://github.com/pmrowla/hl2sdk-csgo/blob/master/public/dt_recv.h#L170
class RecvTable {
 public:
  // typedef RecvProp	PropType;

  RecvTable();
  RecvTable(RecvProp* pProps, int nProps, char* pNetTableName);
  ~RecvTable();

  void Construct(RecvProp* pProps, int nProps, char* pNetTableName);

  int GetNumProps();
  RecvProp* GetProp(int i);

  const char* GetName();

  // Used by the engine while initializing array props.
  void SetInitialized(bool bInitialized);
  bool IsInitialized() const;

  // Used by the engine.
  void SetInMainList(bool bInList);
  bool IsInMainList() const;

 public:
  // Properties described in a table.
  RecvProp* m_pProps;
  int m_nProps;

  // The decoder. NOTE: this covers each RecvTable AND all its children (ie: its
  // children will have their own decoders that include props for all their
  // children).
  void* m_pDecoder;  // CRecvDecoder		*m_pDecoder;

  char* m_pNetTableName;  // The name matched between client and server.

 private:
  bool m_bInitialized;
  bool m_bInMainList;
};

inline int RecvTable::GetNumProps() {
  return m_nProps;
}

inline RecvProp* RecvTable::GetProp(int i) {
  return &m_pProps[i];
}

inline const char* RecvTable::GetName() {
  return m_pNetTableName;
}

inline void RecvTable::SetInitialized(bool bInitialized) {
  m_bInitialized = bInitialized;
}

inline bool RecvTable::IsInitialized() const {
  return m_bInitialized;
}

inline void RecvTable::SetInMainList(bool bInList) {
  m_bInMainList = bInList;
}

inline bool RecvTable::IsInMainList() const {
  return m_bInMainList;
}
