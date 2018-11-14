#include "Managers/Modules/ModuleManager.h"

using namespace CodeNamePaste::Managers::Modules;

void ModuleManager::DoInit() {
	for (const auto& mod : modules)
		mod->DoInit();
}

void ModuleManager::DoTick() {}

bool ModuleManager::DoShutdown() {
	for (const auto& mod : modules)
		if (!mod->DoShutdown())
			continue;				// TODO: add logging
	return true;
}

void ModuleManager::RegisterModule(std::unique_ptr<IModule>&& mod)
{
	modules.emplace_back(std::move(mod));
}
