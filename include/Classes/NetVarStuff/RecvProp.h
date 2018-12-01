#pragma once
#include <cstdint>

namespace CodeNamePaste::Classes {
// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/dt_common.h#L111
typedef enum {
  DPT_Int = 0,
  DPT_Float,
  DPT_Vector,
  DPT_VectorXY,  // Only encodes the XY of a vector, ignores Z
  DPT_String,
  DPT_Array,  // An array of the base types (can't be of datatables).
  DPT_DataTable,
#if 0  // We can't ship this since it changes the size of DTVariant to be 20
       // bytes instead of 16 and that breaks MODs!!!
		DPT_Quaternion,
#endif

  //#ifdef SUPPORTS_INT64
  DPT_Int64,
  //#endif

  DPT_NUMSendPropTypes
} SendPropType;

// https://github.com/pmrowla/hl2sdk-csgo/blob/master/public/dt_common.h#L128
class DVariant {
 public:
  union {
    float m_Float;
    long m_Int;
    char* m_pString;
    void* m_pData;  // For DataTables.
#if 0  // We can't ship this since it changes the size of DTVariant to be 20
       // bytes instead of 16 and that breaks MODs!!!
			float	m_Vector[4];
#else
    float m_Vector[3];
#endif
    int64_t m_Int64;
  };
  SendPropType m_Type;
};

class RecvProp;

// This is passed into RecvProxy functions.
class CRecvProxyData {
 public:
  const RecvProp* m_pRecvProp;  // The property it's receiving.

  DVariant m_Value;  // The value given to you to store.

  int m_iElement;  // Which array element you're getting.

  int m_ObjectID;  // The object being referred to.
};

typedef void (*RecvVarProxyFn)(const CRecvProxyData* pData,
                               void* pStruct,
                               void* pOut);
typedef void (*DataTableRecvVarProxyFn)(const RecvProp* pProp,
                                        void** pOut,
                                        void* pData,
                                        int objectID);
typedef void (*ArrayLengthRecvProxyFn)(void* pStruct,
                                       int objectID,
                                       int currentArrayLength);

class RecvTable;
class RecvProp {
 public:
  char* m_pVarName;
  SendPropType m_RecvType;
  int m_Flags;
  int m_StringBufferSize;

  bool m_bInsideArray;  // Set to true by the engine if this property sits
                        // inside an array.

  // Extra data that certain special property types bind to the property here.
  const void* m_pExtraData;

  // If this is an array (DPT_Array).
  RecvProp* m_pArrayProp;
  ArrayLengthRecvProxyFn m_ArrayLengthProxy;

  RecvVarProxyFn m_ProxyFn;
  DataTableRecvVarProxyFn m_DataTableProxyFn;  // For RDT_DataTable.

  RecvTable* m_pDataTable;  // For RDT_DataTable.
  int m_Offset;

  int m_ElementStride;
  int m_nElements;

  // If it's one of the numbered "000", "001", etc properties in an array, then
  // these can be used to get its array property name for debugging.
  const char* m_pParentArrayPropName;
};
}  // namespace CodeNamePaste::Classes
