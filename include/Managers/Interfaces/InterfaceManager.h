#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include "Managers/IManager.h"

namespace CodeNamePaste {
	namespace Managers {
		namespace Interfaces {

			enum class InterfaceNames : uint8_t {
				VMaterialSystem080,
				Size
			};

#define GetInterfaceWrap(inst, type, name) inst.GetInterface<type>([] {return name;})

			class InterfaceManager : public IManager
			{
			public:
				void DoInit() override;
				void DoTick() override;
				bool DoShutdown() override;

			public:
				template<typename T, typename F>
				T* GetInterface(F func)
				{
					return ifaceAddys[static_cast<uint8_t>(GetEnumFromString(func))];
				}

			private:
				AutoNum* GetInterface(void* CreateInterfaceExp, std::string&& ifaceName);

			private:
				  template <typename F>
				  static constexpr const InterfaceNames GetEnumFromString_impl(std::string_view name) {
					if (name == "VMaterialSystem")
					  return InterfaceNames::VMaterialSystem080;
					return InterfaceNames::Size;
				  }

				  template <typename F>
				  static constexpr const InterfaceNames GetEnumFromString(F func) {
					  constexpr auto internalName = GetEnumFromString_impl(func());
					static_assert(internalName != InterfaceNames::Size);
					return internalName;
				  }
			private:
				AutoNum* ifaceAddys[static_cast<uint8_t>(InterfaceNames::Size)] = { nullptr };
			};
		}
	}
}
