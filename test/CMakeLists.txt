set(TEST_SOURCES
	TestMainFile.cpp
	TestInterfaceManager.cpp)

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

source_group("Unit Tests" REGULAR_EXPRESSION "/test/.*\\.cpp$")
source_group("Header Files" REGULAR_EXPRESSION "/include/I[A-z]+\\.h")
