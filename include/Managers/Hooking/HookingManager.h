#pragma once

#include <unordered_map>
#include <list>
#include <string_view>
#include <utility>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <algorithm>

#include "Managers/IManager.h"

namespace CodeNamePaste {
	namespace Managers {
		namespace Hooks {
			enum class HookNames {
				OnTick,
				CreateMove,
				Size
			};

#define RegisterCallbackWrap(inst, name, clbk) inst.RegisterCallback([]{return name;}, clbk)
#define UnRegisterCallbackWrap(inst, name, clbk) inst.UnRegisterCallback([]{return name;}, clbk)

			class HookingManager : public IManager {
			public:


			public:
				void DoInit() override;
				void DoTick() override;
				bool DoShutdown() override;

			public:
				// TODO make callback registering constexpr
				template<typename F>
				const std::function<void(void*)>& RegisterCallback(F func, std::function<void(void*)>&& clbk)
				{
					std::unique_lock<std::shared_mutex> lock{ mutex_ };
					return funcCallbacks[GetEnumFromString(func)].emplace_back(std::move(clbk));
				}

				template<typename F>
				void UnRegisterCallback(F func, std::function<void(void*)>& ref)
				{
					std::unique_lock<std::shared_mutex> lock{ mutex_ };

					auto table = GetEnumFromString(func);

					auto curIdx = funcCallbacks[table].begin();
					while ((curIdx = std::find_if(curIdx, funcCallbacks[table].end(), [&ref](const auto& func) {
						return std::addressof(func) == std::addressof(ref);
					})) != funcCallbacks[table].end())
					{
						curIdx = funcCallbacks[table].erase(curIdx);
					}
				}

			private:
				  static constexpr const HookNames GetEnumFromString_impl(std::string_view name) {
					  if (name == "CreateMove")
						 return HookNames::CreateMove;
					  if (name == "OnTick")
						  return HookNames::OnTick;
					return HookNames::Size;
				  }

				  template <typename F>
				  static constexpr HookNames GetEnumFromString(F func) {
					  constexpr auto internalName = GetEnumFromString_impl(func());
					static_assert(internalName != HookNames::Size);
					return internalName;
				  }
			private:
				std::unordered_map<HookNames, std::list<std::function<void(void*)>>> funcCallbacks{};
				std::shared_mutex mutex_;
			};
		}
	}
}
