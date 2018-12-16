#pragma once

#include "Managers/Modules/Module.h"

#include "Interfaces/VClientEntityList003.h"
#include "Interfaces/VClient018.h"


namespace CodeNamePaste {
	namespace Modules {
		class Radar : public Managers::Modules::Module {
		public:
			Radar();

		private:
			void DoInit() override;
			bool DoShutdown() override;

		private:
			void DoRadar(Classes::ClientFrameStage_t stage);

		private:
			void* OnFrameStageNotiftClbk;

		private:
			Interfaces::IClientEntityList* pEntList = nullptr;
		};
	}
}
