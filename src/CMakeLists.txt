set(HACK_SOURCES    MainEntry.cpp
                    Utils/MathHelper.cpp
                    Utils/QAngle.cpp
                    Utils/Vector.cpp
                    Managers/Offsets/OffsetManager.cpp)

set(HACK_HEADERS ../include/Utils/MathHelper.h
                 ../include/Utils/QAngle.h
                 ../include/Utils/Vector.h
                 ../include/Utils/VMTManager.h
                 ../include/Manager/IManager.h
                 ../include/Manager/Offsets/OffsetManager.h)

add_library(ProjectPaste SHARED ${HACK_SOURCES})
target_compile_definitions(ProjectPaste PRIVATE WIN32_LEAN_AND_MEAN)

set_target_properties(ProjectPaste PROPERTIES
	C_STANDARD 11
	C_STANDARD_REQUIRED YES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	FOLDER HACK
)

install(TARGETS ProjectPaste RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)
