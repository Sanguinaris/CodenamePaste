#pragma once

#include "Managers/Hooking/HookingManager.h"
#include "Managers/Interfaces/InterfaceManager.h"
#include "Managers/Modules/ModuleManager.h"
#include "Managers/NetVars/NetvarManager.h"
#include "Managers/Offsets/OffsetManager.h"

namespace CodeNamePaste {
	class Hack {
	public:
		Hack();

	public:
		bool Run();
		void Shutdown();
		void Unload();	// Should find a better name

	private:
		bool ShouldRun = true;
		bool UncleanUnload = false;

	private:
		FILE* pNewStdOut = nullptr;

	private:
		  Managers::Interfaces::InterfaceManager ifaceMgr{};
		  Managers::NetVars::NetVarManager netMgr{ifaceMgr};
		  Managers::Offsets::OffsetManager offsetMgr{netMgr};
		  Managers::Hooks::HookingManager hookMgr{ifaceMgr, offsetMgr};
		  Managers::Modules::ModuleManager modMgr{ifaceMgr, netMgr, offsetMgr, hookMgr};
	};
}
