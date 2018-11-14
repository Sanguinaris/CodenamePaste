#pragma once
#include <vector>
#include <memory>

#include "Managers/Interfaces/InterfaceManager.h"
#include "Managers/Offsets/OffsetManager.h"
#include "Managers/Hooking/HookingManager.h"
#include "IModule.h"
#include "Managers/IManager.h"

namespace CodeNamePaste::Managers {
	namespace Modules {
		class ModuleManager : public IManager {
		public:
			void RegisterModule(std::unique_ptr<IModule>&& mod);

		public:
			void DoInit() override;
			void DoTick() override;
			bool DoShutdown() override;

		private:
			std::vector<std::unique_ptr<IModule>> modules{};
		};
	}
}