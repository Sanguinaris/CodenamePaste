set(TEST_SOURCES
	TestMainFile.cpp
	Utils/TestVMTManager.cpp ../include/Utils/VMTManager.h
	Utils/TestVector.cpp ../include/Utils/Vector.h
	Utils/TestMathHelper.cpp ../include/Utils/MathHelper.h ../src/Utils/MathHelper.cpp
	Utils/TestQAngle.cpp ../include/Utils/QAngle.h)

if(WIN32 AND FALSE)
	set(WIN_SOURCES Managers/TestOffsetManager.cpp ../include/Managers/Offsets/OffsetManager.h ../src/Managers/Offsets/OffsetManager.cpp
	Managers/TestHookingManager.cpp ../include/Managers/Hooking/HookingManager.h ../src/Managers/Hooking/HookingManager.cpp)
endif()

add_executable(CTRLV ${TEST_SOURCES} ${WIN_SOURCES})
add_dependencies(CTRLV catch)

set_target_properties(CTRLV PROPERTIES
	C_STANDARD 11
	C_STANDARD_REQUIRED YES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	FOLDER Test
)

if(WIN32)
	target_link_libraries(CTRLV psapi)
endif()

add_test(
    NAME CTRLV
    COMMAND CTLRV -o report.xml -r junit)

source_group("Unit Tests" REGULAR_EXPRESSION "/test/.*\\.cpp$")
source_group("Header Files" REGULAR_EXPRESSION "/include/I[A-z]+\\.h")
