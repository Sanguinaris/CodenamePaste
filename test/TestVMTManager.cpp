#include <catch.hpp>

#include "Utils/VMTManager.h"

// THESE TESTS MIGHT FAIL UNDER CERTAIN COMPILERS/ARCHITECTURE.
// PLEASE CREATE AN ISSUE IF THEY DO

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

struct Example3 : public IExample, IExample2 {
  bool DoTest() override { return false; }

  int DoOne() override { return 1; }

  int DoTwo() override { return 2; }
};

bool __fastcall hkDoTest(Example* ecx, void*) {
  return true;
}

TEST_CASE("We are capable of detecting the size of a VTable") {
  GIVEN("An example Class") {
    std::unique_ptr<Example> xmpl{std::make_unique<Example>()};
    std::unique_ptr<Example2> xmpl2{std::make_unique<Example2>()};
    std::unique_ptr<Example3> xmpl3{std::make_unique<Example3>()};

    WHEN("Calculating the Size of the Vtable") {
      // The VTable Size
      uint32_t iVtableSize = 0;
      uint32_t iVtableSize2 = 0;
      uint32_t iVtableSize3 = 0;
      uint32_t iVtableSize4 = 0;
      // Iterate over the base object and check for nullptr
      for (auto idx = *reinterpret_cast<uint32_t***>(xmpl.get());
           idx[iVtableSize]; ++iVtableSize)
        ;
      for (auto idx = *reinterpret_cast<uint32_t***>(xmpl2.get());
           idx[iVtableSize2]; ++iVtableSize2)
        ;
      for (auto idx = *reinterpret_cast<uint32_t***>(xmpl3.get());
           idx[iVtableSize3]; ++iVtableSize3)
        ;
      for (auto idx =
               *reinterpret_cast<uint32_t***>(xmpl3.get()) + sizeof(void*);
           idx[iVtableSize4]; ++iVtableSize4)
        ;

      THEN("The Size should be correct") {
#ifdef _MSC_VER
        CHECK(iVtableSize == 2);
        CHECK(iVtableSize2 == 3);
#else
        CHECK(iVtableSize == 3);
        CHECK(iVtableSize2 == 4);
#endif
        // CHECK(iVtableSize3 == 2); // Different compilers do different stuff
        // need to check CHECK(iVtableSize4 == 3);
      }
    }
  }
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
