#include <catch.hpp>

#include "Utils/VMTManager.h"

// THESE TESTS MIGHT FAIL UNDER CERTAIN COMPILERS/ARCHITECTURE.
// PLEASE CREATE AN ISSUE IF THEY DO

using namespace CodeNamePaste;
using namespace Utils;

class IExample {
 public:
  virtual ~IExample() = default;  // 0
  virtual bool DoTest() = 0;      // 1
};

class IExample2 {
 public:
  virtual ~IExample2() = default;  // 0
  virtual int DoOne() = 0;         // 1
  virtual int DoTwo() = 0;         // 2
};

struct Example : IExample {
  bool DoTest() override { return false; }
};

struct Example2 : IExample2 {
  int DoOne() override { return 1; }

  int DoTwo() override { return 2; }
};

bool hkDoTest() {
  return true;
}
int hkDoOne() {
  return 0;
}
int hkDoTwo() {
  return 0;
}

TEST_CASE("Test is capable of hooking the base function") {
  GIVEN("An Example Class") {
    std::unique_ptr<Example> xmpl{std::make_unique<Example>()};

    WHEN("The unhooked Function returns value as expected") {
      REQUIRE_FALSE(xmpl->DoTest());

      THEN("Automatically hooking it will change that") {
        VMTManager<IExample> mgr{xmpl.get()};
#ifdef _MSC_VER
        REQUIRE(mgr.HookIndex(1, &hkDoTest));
#else
        REQUIRE(mgr.HookIndex(2, &hkDoTest));
#endif
        REQUIRE(xmpl->DoTest());
      }
      AND_THEN(
          "After the Manager Deconstructed we should be calling the original "
          "again") {
        REQUIRE_FALSE(xmpl->DoTest());
      }
    }
  }
  GIVEN("An Example2 Class") {
    std::unique_ptr<Example2> xmpl{std::make_unique<Example2>()};
    WHEN("The unhooked Function returns value as expected") {
      REQUIRE(xmpl->DoOne() == 1);
      REQUIRE(xmpl->DoTwo() == 2);

      THEN("Automatically hooking it will change that") {
        VMTManager<IExample2> mgr{xmpl.get()};
#ifdef _MSC_VER
        REQUIRE(mgr.HookIndex(1, &hkDoOne));
        REQUIRE(mgr.HookIndex(2, &hkDoTwo));
#else
        REQUIRE(mgr.HookIndex(2, &hkDoOne));
        REQUIRE(mgr.HookIndex(3, &hkDoTwo));
#endif
        REQUIRE(xmpl->DoOne() == 0);
        REQUIRE(xmpl->DoTwo() == 0);
      }
      AND_THEN(
          "After the Manager Deconstructed we should be calling the original "
          "again") {
        REQUIRE(xmpl->DoOne() == 1);
        REQUIRE(xmpl->DoTwo() == 2);
      }
    }
  }
}

TEST_CASE("Test is capable of unhooking a function") {
  GIVEN("We've got a base Example Class and Vtable Manager") {
    std::unique_ptr<Example> xmpl{std::make_unique<Example>()};
    VMTManager<IExample> mgr{xmpl.get()};

    REQUIRE_FALSE(xmpl->DoTest());

    WHEN("When we hook the function") {
#ifdef _MSC_VER
      REQUIRE(mgr.HookIndex(1, &hkDoTest));
#else
      REQUIRE(mgr.HookIndex(2, &hkDoTest));
#endif
      REQUIRE(xmpl->DoTest());

      THEN("Then if we unhook it, we get the original result") {
#ifdef _MSC_VER
        REQUIRE(mgr.UnHookIndex(1));
#else
        REQUIRE(mgr.UnHookIndex(2));
#endif
        REQUIRE_FALSE(xmpl->DoTest());
      }
    }
  }
}

TEST_CASE(
    "Test is not capable of hooking and unhooking a function that is not "
    "present") {
  GIVEN("We've got a base Example Class and Vtable Manager") {
    std::unique_ptr<Example> xmpl{std::make_unique<Example>()};
    VMTManager<IExample> mgr{xmpl.get()};

    REQUIRE_FALSE(xmpl->DoTest());

    WHEN("When we hook the function") {
      REQUIRE_FALSE(mgr.HookIndex(1337, &hkDoTest));
      REQUIRE_FALSE(xmpl->DoTest());

      THEN("Then if we unhook it, we get the original result") {
        REQUIRE_FALSE(mgr.UnHookIndex(1337));
        REQUIRE_FALSE(xmpl->DoTest());
      }
    }
  }
}

TEST_CASE("Test is capable of calling the original function after hooking") {
  GIVEN("We've got a base Example Class and Vtable Manager") {
    std::unique_ptr<Example> xmpl{std::make_unique<Example>()};
    VMTManager<IExample> mgr{xmpl.get()};

    REQUIRE_FALSE(xmpl->DoTest());

    WHEN("If we hook the function") {
#ifdef _MSC_VER
      REQUIRE(mgr.HookIndex(1, &hkDoTest));
#else
      REQUIRE(mgr.HookIndex(2, &hkDoTest));
#endif

      THEN("Then we should be able to call hooked and orignal function") {
        REQUIRE_FALSE(mgr.GetOriginal()->DoTest());
        REQUIRE(xmpl->DoTest());
      }
    }
  }
}
