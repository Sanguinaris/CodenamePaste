#pragma once
#include "IModule.h"

namespace CodeNamePaste::Managers::Modules {
class Module : public IModule {
 public:
  Module(std::string&& name);

 public:
  void DoInit() override;
  bool DoShutdown() override;

 public:
  void Toggle() override;
  void SetState(bool state) override;

 public:
  const bool IsActive() const override;
  const std::string& GetModuleName() const override;

 protected:
  bool moduleState = false;

 private:
  const std::string moduleName;
};
}  // namespace CodeNamePaste::Managers::Modules
