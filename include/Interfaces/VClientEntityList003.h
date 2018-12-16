#pragma once

#include "Classes/CBaseEntity.h"
#include "Managers/Interfaces/InterfaceManager.h"

namespace CodeNamePaste {
	namespace Interfaces {
		class VClientEntityList003 {
		public:
			VFUNCTION(3, Classes::CBaseEntity*(__fastcall *)(void*, void*, int idx), GetClientEntity);

		};

		using IClientEntityList = VClientEntityList003;
	}
}
