cmake_minimum_required (VERSION 3.8)
project ("CodenamePaste" VERSION 0.0.1)

include(CPack)
include(ext/deps.cmake)
include_directories(include include/Managers/Interfaces include/Managers/Modules include/Managers/NetVars include/Managers/Offsets include/Managers/Render  ${CMAKE_BINARY_DIR})

#find_program(CCACHE_FOUND ccache)
#if(CCACHE_FOUND)
#	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
#	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
#endif()

add_subdirectory(src)

option(BUILD_OFFLINE "Build Offline" OFF)
option(ENABLE_TESTING "Enable Building of Unit Tests" OFF)

if(ENABLE_TESTING)
	enable_testing()
	add_subdirectory(test)
endif()

