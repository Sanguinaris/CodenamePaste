#pragma once

#include <string>

namespace CodeNamePaste::Managers {
namespace Modules {
class IModule {
 public:
  virtual ~IModule() = default;

 public:
  virtual bool DoShutdown() = 0;

 public:
  virtual void Toggle() = 0;
  virtual void SetState(bool state) = 0;

 public:
  virtual const std::string& GetModuleName() const = 0;
  virtual const bool IsActive() const = 0;
};
}  // namespace Modules
}  // namespace CodeNamePaste::Managers