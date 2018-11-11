#pragma once
namespace CodeNamePaste {
namespace Managers {
class IManager {
 public:
  virtual ~IManager() = default;

  virtual void DoInit() = 0;  // Throws on fatal failure
  virtual void DoTick() = 0;
  virtual bool DoShutdown() = 0;
};
}  // namespace Managers
}  // namespace CodeNamePaste
