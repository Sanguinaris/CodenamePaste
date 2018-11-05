#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif
#include <cstdlib>

namespace CodeNamePaste {
namespace Utils {
template <typename T>
class VMTManager {
 public:
  VMTManager(T* base)
      : _pBaseClass{reinterpret_cast<uint32_t***>(base)},
        _pOrigVtable{*_pBaseClass} {
    // Calculate size of VTable
    for (; (*_pBaseClass)[iVtableSize]; ++iVtableSize)
      ;

    pVmtCopy = std::unique_ptr<uint32_t*[]>(new uint32_t*[iVtableSize]);

    std::copy(*_pBaseClass, *_pBaseClass + iVtableSize, pVmtCopy.get());

#ifdef _WIN32
    DWORD dwOldProt;
    DWORD dwOldProt2;
    // Make ptr to vtable writeable
    VirtualProtect(_pBaseClass, sizeof(T*), PAGE_EXECUTE_READWRITE, &dwOldProt);
    // mark dtor with same access rights as prev
    VirtualProtect(pVmtCopy.get(), sizeof(T*), dwOldProt, &dwOldProt2);
#endif
    // Replace the Vtable
    *_pBaseClass = pVmtCopy.get();

#ifdef _WIN32
    // Restore page rights
    VirtualProtect(_pBaseClass, sizeof(T*), dwOldProt, &dwOldProt);
#endif
  }

  ~VMTManager() {
#ifdef _WIN32
    // Restore old vtable
    DWORD dwOldProt;
    VirtualProtect(pVmtCopy.get(), sizeof(T*), PAGE_EXECUTE_READWRITE,
                   &dwOldProt);
    VirtualProtect(_pBaseClass, sizeof(T*), PAGE_EXECUTE_READWRITE, &dwOldProt);
#endif
    
    *_pBaseClass = _pOrigVtable;
    
#ifdef _WIN32
    VirtualProtect(_pBaseClass, sizeof(T*), dwOldProt, &dwOldProt);
#endif
  }

 public:
  template <typename Fn>
  bool HookIndex(const std::size_t idx, Fn* func) {
    if (idx > iVtableSize || idx < 1)
      return false;

    pVmtCopy[idx] = reinterpret_cast<uint32_t*>(func);

    return true;
  }

  bool UnHookIndex(const std::size_t idx) {
    if (idx > iVtableSize || idx < 1)
      return false;

    pVmtCopy[idx] = _pOrigVtable[idx];

    return true;
  }

  T* GetOriginal() { return reinterpret_cast<T*>(&_pOrigVtable); }

 private:
  std::size_t iVtableSize = 0;

  uint32_t*** _pBaseClass;
  uint32_t** _pOrigVtable;

  std::unique_ptr<uint32_t*[]> pVmtCopy;
};
}  // namespace Utils
}  // namespace CodeNamePaste
