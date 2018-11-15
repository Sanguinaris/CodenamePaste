#pragma once
#include <type_traits>
#include <cstdint>

namespace CodeNamePaste {
namespace Managers {

using AutoNum = std::conditional_t<(sizeof(void*) == 8), uint64_t, uint32_t>;

class IManager {
 public:
  virtual ~IManager() = default;

  virtual void DoInit() = 0;  // Throws on fatal failure
  virtual void DoTick() = 0;
  virtual bool DoShutdown() = 0;
};
}  // namespace Managers
}  // namespace CodeNamePaste
