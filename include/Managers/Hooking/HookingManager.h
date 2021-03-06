#pragma once

#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "Managers/IManager.h"

#include "Managers/Interfaces/InterfaceManager.h"
#include "Managers/Offsets/OffsetManager.h"

#include "Interfaces/VClient018.h"
#include "Interfaces/VClientMode.h"
#include "Utils/VMTManager.h"

#include "Hooks/hkCreateMove.h"
#include "Hooks/hkFrameStageNotify.h"

namespace CodeNamePaste {
namespace Managers {
namespace Hooks {
enum class HookNames { OnTick, CreateMove, FrameStageNotify, Size };

#define RegisterCallbackWrap(inst, name, clbk) \
  inst.RegisterCallback([] { return name; }, clbk)
#define UnRegisterCallbackWrap(inst, name, clbk) \
  inst.UnRegisterCallback([] { return name; }, clbk)

class HookingManager : public IManager {
  friend bool(__fastcall CodeNamePaste::Hooks::hkCreateMove)(
      void*,
      void*,
      float,
      Classes::CUserCmd*);
  friend void(__fastcall CodeNamePaste::Hooks::hkFrameStageNotify)(
      void*,
      void*,
      Classes::ClientFrameStage_t);

 public:
  using CallbackFn = void(void*);

 public:
  HookingManager(const Interfaces::InterfaceManager&,
                 const Offsets::OffsetManager&);

 public:
  void DoInit() override;
  void DoTick() override;
  bool DoShutdown() override;

 public:
  template <typename F>
  void* RegisterCallback(F func, std::function<CallbackFn>&& clbk) {
    std::unique_lock<std::shared_mutex> lock{mutex_};
    return &funcCallbacks[GetEnumFromString(func)].emplace_back(
        std::move(clbk));
  }

  template <typename F>
  bool UnRegisterCallback(F func, const void* ref) {
    std::unique_lock<std::shared_mutex> lock{mutex_};
    bool deletedSomething = false;

    auto table = GetEnumFromString(func);

    auto curIdx = funcCallbacks[table].begin();
    while ((curIdx = std::find_if(curIdx, funcCallbacks[table].end(),
                                  [&ref](const auto& fn) {
                                    return std::addressof(fn) == ref;
                                  })) != funcCallbacks[table].end()) {
      curIdx = funcCallbacks[table].erase(curIdx);
      deletedSomething = true;
    }
    return deletedSomething;
  }

 private:
  static constexpr const HookNames GetEnumFromString_impl(
      std::string_view name) {
    if (name == "CreateMove")
      return HookNames::CreateMove;
    if (name == "OnTick")
      return HookNames::OnTick;
    if (name == "FrameStageNotify")
      return HookNames::FrameStageNotify;
    return HookNames::Size;
  }

  template <typename F>
  static constexpr HookNames GetEnumFromString(F func) {
    constexpr auto internalName = GetEnumFromString_impl(func());
    static_assert(internalName != HookNames::Size);
    return internalName;
  }

 private:
  std::unique_ptr<Utils::VMTManager<CodeNamePaste::Interfaces::VClientMode>>
      ClientMode;
  std::unique_ptr<Utils::VMTManager<CodeNamePaste::Interfaces::IBaseClientDLL>>
      BaseClientDll;
  std::unordered_map<HookNames, std::list<std::function<void(void*)>>>
      funcCallbacks{};
  std::shared_mutex mutex_;

 private:
  const Interfaces::InterfaceManager& ifaceMgr;
  const Offsets::OffsetManager& offyMgr;
};
}  // namespace Hooks
}  // namespace Managers
}  // namespace CodeNamePaste
