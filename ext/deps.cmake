include(ExternalProject)
include(ProcessorCount)
ProcessorCount(N)

set(TROMP_DIR ${CMAKE_BINARY_DIR}/trompel)
set(CATCH_DIR ${CMAKE_BINARY_DIR}/catch)

if(BUILD_OFFLINE)
	set_property(DIRECTORY PROPERTY EP_UPDATE_DISCONNECTED TRUE)
endif()

ExternalProject_Add(trompeloeil
	GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
	GIT_TAG v32
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${TROMP_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS} -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS} -DCMAKE_EXE_LINKER_FLAGS=${CMAKE_EXE_LINKER_FLAGS} -DCMAKE_STATIC_LINKER_FLAGS=${CMAKE_STATIC_LINKER_FLAGS} -DCMAKE_AR=${CMAKE_AR} -DCMAKE_RANLIB=${CMAKE_RANLIB} -DCMAKE_C_ARCHIVE_FINISH=${CMAKE_C_ARCHIVE_FINISH} -DCMAKE_CXX_ARCHIVE_FINISH=${CMAKE_CXX_ARCHIVE_FINISH}
	EXCLUDE_FROM_ALL 1
	UPDATE_COMMAND ""
)

ExternalProject_Add(catch
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.4.1
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CATCH_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS} -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS} -DCMAKE_EXE_LINKER_FLAGS=${CMAKE_EXE_LINKER_FLAGS} -DCMAKE_STATIC_LINKER_FLAGS=${CMAKE_STATIC_LINKER_FLAGS} -DCMAKE_AR=${CMAKE_AR} -DCMAKE_RANLIB=${CMAKE_RANLIB} -DCMAKE_C_ARCHIVE_FINISH=${CMAKE_C_ARCHIVE_FINISH} -DCMAKE_CXX_ARCHIVE_FINISH=${CMAKE_CXX_ARCHIVE_FINISH}
	EXCLUDE_FROM_ALL 1
	UPDATE_COMMAND ""
)

include_directories(${TROMP_DIR}/include ${CATCH_DIR}/include)
link_directories(${TROMP_DIR}/lib ${CATCH_DIR}/lib)
