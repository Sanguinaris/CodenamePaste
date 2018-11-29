#include "Modules/AntiFlash.h"

using namespace CodeNamePaste;
using namespace Modules;

AntiFlash::AntiFlash() : Module::Module{"AntiFlash"} {}

void AntiFlash::DoInit() {
	RegisterCallbackWrap(hookMgr->get(), "OnTick", [](const auto) {

	});
}
