#pragma once

#include <unordered_map>
#include <vector>
#include <string_view>
#include <utility>
#include <functional>

#include "Managers/IManager.h"

namespace CodeNamePaste {
	namespace Managers {
		namespace Hooks {
			enum class HookNames {
				OnTick,
				CreateMove,
				Size
			};

#define RegisterCallbackWarp(inst, name, clbk) inst.RegisterCallback([]{return name;}, clbk)

			class HookingManager : public IManager {
			public:


			public:
				void DoInit() override;
				void DoTick() override;
				bool DoShutdown() override;

			public:
				// TODO make callback registering constexpr
				template<typename F>
				void RegisterCallback(F func, std::function<void(void*)>&& clbk)
				{
					funcCallbacks[GetEnumFromString(func)].emplace_back(std::move(clbk));
				}

				//template<typename F>
				//void UnRegisterCallback(F func, )

			private:
				  static constexpr const HookNames GetEnumFromString_impl(std::string_view name) {
					  if (name == "CreateMove")
						 return HookNames::CreateMove;
					return HookNames::Size;
				  }

				  template <typename F>
				  static constexpr const HookNames GetEnumFromString(F func) {
					static_assert(GetEnumFromString_impl(func()) != HookNames::Size);
					return GetEnumFromString_impl(func());
				  }
			private:
				std::unordered_map<HookNames, std::vector<std::function<void(void*)>>> funcCallbacks{};
			};
		}
	}
}
