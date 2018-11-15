#include <catch.hpp>

#include "Managers/Hooking/HookingManager.h"

#include <future>

using namespace std::chrono_literals;

using namespace CodeNamePaste;
using namespace Managers;
using namespace Hooks;

TEST_CASE("Test whether or not Registering and unregistering a callback works")
{
	HookingManager hookMgr{};

	std::promise<void> func1{};
	std::promise<void> func2{};
	std::promise<void> func1s2{};
	std::promise<void> func2s2{};
	bool hasCalledOnce = false;

	const auto& token = RegisterCallbackWrap(hookMgr, "OnTick", [&](void*) {
		if (!hasCalledOnce)
			func1.set_value();
		else
			func2.set_value();
	});
	RegisterCallbackWrap(hookMgr, "OnTick", [&](void*) {
		if (!hasCalledOnce)
			func2.set_value();
		else
			func2s2.set_value();
	});
	hookMgr.DoTick();
	hasCalledOnce = true;
	CHECK(func1.get_future().wait_for(100ms) == std::future_status::ready);
	CHECK(func2.get_future().wait_for(100ms) == std::future_status::ready);
	UnRegisterCallbackWrap(hookMgr, "OnTick", token);
	hookMgr.DoTick();
	CHECK(func1s2.get_future().wait_for(100ms) == std::future_status::timeout);
	CHECK(func2s2.get_future().wait_for(100ms) == std::future_status::ready);
}
