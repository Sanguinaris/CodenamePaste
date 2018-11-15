#pragma once
#include "Managers/IManager.h"
#include "Managers/Interfaces/InterfaceManager.h"
#include "Classes/NetVarStuff/RecvTable.h"

#include <unordered_map>


namespace CodeNamePaste::Managers {
	namespace NetVars {
		class NetVarManager : public IManager {
		public:
			NetVarManager(Interfaces::InterfaceManager& ifaceMgr);

		public:
			void DoInit() override;
			void DoTick() override;
			bool DoShutdown() override;

		public:
			const AutoNum GetProp(const std::string& tableName, const std::string& propName, RecvProp** prop = nullptr) const;

		private:
			const AutoNum GetProp(const RecvTable& recvTable, const std::string& propName, RecvProp** prop = nullptr) const;

		private:
			Interfaces::InterfaceManager& ifaceMgr;
			std::unordered_map<std::string, RecvTable*> tables;
		};
	}
}
