include(ExternalProject)
include(ProcessorCount)
ProcessorCount(N)
set(CATCH_DIR ${CMAKE_BINARY_DIR}/catch)

if(BUILD_OFFLINE)
	set_property(DIRECTORY PROPERTY EP_UPDATE_DISCONNECTED TRUE)
endif()

ExternalProject_Add(catch
	URL https://github.com/catchorg/Catch2/releases/download/v2.4.1/catch.hpp
	URL_HASH SHA512=10921f7ebc03643e0e6c21c3566f3968bf19fd5eb9b23a4a84150eebbbf0c5e8bcd12c31ac6d6e7ee91adcfd7c1a6f9bb6bed3b01d3736b569cefd0db98bea15
	DOWNLOAD_NO_EXTRACT TRUE
	DOWNLOAD_DIR ${CATCH_DIR}
	CONFIGURE_COMMAND ""
	UPDATE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	EXCLUDE_FROM_ALL 1
	UPDATE_COMMAND ""
)

include_directories(${CATCH_DIR})
