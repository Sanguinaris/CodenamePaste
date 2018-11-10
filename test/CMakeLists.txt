set(TEST_SOURCES
	TestMainFile.cpp
	Utils/TestVMTManager.cpp ../include/Utils/VMTManager.h
	Utils/TestVector.cpp ../include/Utils/Vector.h ../src/Utils/Vector.cpp
	Utils/TestMathHelper.cpp ../include/Utils/MathHelper.h ../src/Utils/MathHelper.cpp
	Utils/TestQAngle.cpp ../include/Utils/QAngle.h ../src/Utils/QAngle.cpp)

add_executable(CTRLV ${TEST_SOURCES})
add_dependencies(CTRLV catch)
#target_link_libraries
set_target_properties(CTRLV PROPERTIES
	C_STANDARD 11
	C_STANDARD_REQUIRED YES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	FOLDER Test
)

add_test(
    NAME CTRLV
    COMMAND CTLRV -o report.xml -r junit)

source_group("Unit Tests" REGULAR_EXPRESSION "/test/.*\\.cpp$")
source_group("Header Files" REGULAR_EXPRESSION "/include/I[A-z]+\\.h")
