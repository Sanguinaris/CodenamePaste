#include <catch.hpp>

#include <cstdint>
#include <memory>
#include <windows.h>
#include <algorithm>
#include <future>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

// THESE TESTS MIGHT FAIL UNDER CERTAIN COMPILERS/ARCHITECTURE.
// PLEASE CREATE AN ISSUE IF THEY DO

/*template<typename T = void*>
class VFTManager {
public:
	VFTManager(T* baseClass) : _pBaseClass{ reinterpret_cast<T**>(baseClass)}, _pOrigVft{*_pBaseClass}
	{
		for (auto idx = *reinterpret_cast<T***>(_pBaseClass); idx[_iOrigVtableSize]; ++_iOrigVtableSize);
		_pNewVtable = std::make_unique<T[]>(_iOrigVtableSize);
		std::memcpy(reinterpret_cast<void*>(_pNewVtable.get()), reinterpret_cast<void*>(_pOrigVft), _iOrigVtableSize * sizeof(T*));
		
		DWORD old;
		VirtualProtect(*_pBaseClass, sizeof(T*), PAGE_EXECUTE_READWRITE, &old);
		*_pBaseClass = _pNewVtable.get();
		VirtualProtect(*_pBaseClass, sizeof(T*), old, &old);
	}

	~VFTManager()
	{
	//	DWORD old;
//		VirtualProtect(*_pBaseClass, sizeof(T*), PAGE_EXECUTE_READWRITE, &old);
//		*_pBaseClass = _pOrigVft;
//		VirtualProtect(*_pBaseClass, sizeof(T*), old, &old);
	}

public:
	template<typename Fn>
	Fn GetOriginal(const size_t idx) const
	{
		return reinterpret_cast<Fn>(_pOrigVtable[idx]);
	}

	bool HookIndex(const size_t idx, void* func)
	{
		if (idx > _iOrigVtableSize)
			return false;
		_pNewVtable[idx] = *reinterpret_cast<T*>(&func);
		return true;
	}

	void UnhookIndex(const size_t idx)
	{
		DWORD old;
		VirtualProtect(*_pBaseClass, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &old);
		_pBaseClass[idx] = _pNewVtable[idx];
		VirtualProtect(*_pBaseClass, sizeof(DWORD), old, &old);
	}

private:
	T** _pBaseClass;
	T* _pOrigVft;
	std::unique_ptr<T[]> _pNewVtable;
	size_t _iOrigVtableSize = 0;
};*/


class IExample {
public:
	virtual ~IExample() = default; // 0
	virtual bool DoTest() = 0; //1 
};

class IExample2 {
public:
	virtual ~IExample2() = default; // 0
	virtual int DoOne() = 0;	// 1
	virtual int DoTwo() = 0;	// 2
};

class Example : IExample {
public:
	bool DoTest() override {
		return false;
	}
};

class Example2 : IExample2{
public:
	int DoOne() override {
		return 1;
	}

	int DoTwo() override {
		return 2;
	}
};

class Example3 : IExample, IExample2 {
public:
	bool DoTest() override {
		return false;
	}

	int DoOne() override {
		return 1;
	}

	int DoTwo() override {
		return 2;
	}
};

bool __fastcall hkDoTest(Example* ecx, void*)
{
    return true;
}


TEST_CASE("Test is capable of hooking the base function", "InterfaceManager")
{
    GIVEN("An Example Class"){
        std::unique_ptr<Example> xmpl{std::make_unique<Example>()};
        
        WHEN("The unhooked Function returns value as expected")
        {
            REQUIRE_FALSE(xmpl->DoTest());
            
            THEN("Manually Hooking it will change that")
            {
                DWORD old;
                
				// address of skewedBase == base xmpl object
                auto skewedBase = *reinterpret_cast<uint32_t***>(xmpl.get());
				
				// Pointer to the vtable + (1 * sizeof(void*)), mark it writeable
                VirtualProtect(&skewedBase[1],  sizeof(void*), PAGE_EXECUTE_READWRITE, &old);

				// Overwrite that entry with my entry
                skewedBase[1] = reinterpret_cast<uint32_t*>(&hkDoTest);

				// Restore the page state of the memory
                VirtualProtect(&skewedBase[1], sizeof(void*), old, &old);

				// Do Test
                REQUIRE(xmpl->DoTest());
            }
        }
    }
}

TEST_CASE("We are capable of detecting the size of a VTable", "InterfaceManager")
{
	GIVEN("An example Class")
	{
		std::this_thread::sleep_for(10s);
        std::unique_ptr<Example> xmpl{std::make_unique<Example>()};
        std::unique_ptr<Example2> xmpl2{std::make_unique<Example2>()};
        std::unique_ptr<Example3> xmpl3{std::make_unique<Example3>()};
		
		WHEN("Calculating the Size of the Vtable")
		{
			// The VTable Size
			uint32_t iVtableSize = 0;
			uint32_t iVtableSize2 = 0;
			uint32_t iVtableSize3 = 0;
			uint32_t iVtableSize4 = 0;
			// Iterate over the base object and check for nullptr
			for (auto idx = *reinterpret_cast<uint32_t***>(xmpl.get()); idx[iVtableSize]; ++iVtableSize);
			for (auto idx = *reinterpret_cast<uint32_t***>(xmpl2.get()); idx[iVtableSize2]; ++iVtableSize2);
			for (auto idx = *reinterpret_cast<uint32_t***>(xmpl3.get()); idx[iVtableSize3]; ++iVtableSize3);
			for (auto idx = *reinterpret_cast<uint32_t***>(xmpl3.get()) + sizeof(void*); idx[iVtableSize4]; ++iVtableSize4);

			THEN("The Size should be correct")
			{
				CHECK(iVtableSize == 2);
				CHECK(iVtableSize2 == 3);
				//CHECK(iVtableSize3 == 2); // Different compilers do different stuff need to check
				//CHECK(iVtableSize4 == 3);
			}
		}
	}
}
