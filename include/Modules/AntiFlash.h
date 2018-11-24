#pragma once

#include "Managers/Modules/Module.h"

namespace CodeNamePaste {
namespace Modules {
class AntiFlash : public Managers::Modules::Module {
 public:
  AntiFlash();

 private:
  void DoInit() override;
};
}  // namespace Modules
}  // namespace CodeNamePaste