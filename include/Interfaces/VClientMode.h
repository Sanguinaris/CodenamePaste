#pragma once
#include "Classes/CUserCmd.h"

namespace CodeNamePaste {
	namespace Interfaces {
		class VClientMode
		{
		public:
			VFUNCTION(24, bool(__fastcall*)(void*, void*, float, Classes::CUserCmd*), CreateMove)
		};
	}
}
