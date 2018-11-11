#define WIN32_LEAN_AND_MEAN

#include <catch.hpp>

#include <Windows.h>

#include "Managers/Offsets/OffsetManager.h"



using namespace CodeNamePaste;
using namespace Managers;
using namespace Offsets;

const char totallyCool[] = "\x12\x14\x17\x69\x99";

TEST_CASE("Test wether or not OffsetManager is capable of finding Signatures")
{
	OffsetManager offsetMgr{};
	CHECK(!strcmp(totallyCool, "\x12\x14\x17\x69\x99"));
	auto x = FindPatternWrap(offsetMgr, char, "CTRLV.exe", "12 14 17 ?? 99");
	REQUIRE_FALSE(x == nullptr);
	CHECK(x == totallyCool);
}
