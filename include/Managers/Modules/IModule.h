#pragma once

#include "Managers/Interfaces/InterfaceManager.h"
#include "Managers/Offsets/OffsetManager.h"

#include <string>

namespace CodeNamePaste::Managers::Modules {
	class IModule {
	public:
		virtual ~IModule() = default;

	public:
		virtual void DoInit() = 0;
		virtual bool DoShutdown() = 0;

	public:
		virtual void Toggle() = 0;
		virtual void SetState(bool state) = 0;

	public:
		virtual const std::string& GetModuleName() const = 0;
		virtual const bool IsActive() const = 0;
	};
}