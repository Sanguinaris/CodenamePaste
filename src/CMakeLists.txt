set(HACK_SOURCES    MainEntry.cpp
					Hack.cpp
                    Utils/MathHelper.cpp
                    Managers/Offsets/OffsetManager.cpp
                    Managers/Interfaces/InterfaceManager.cpp
					Managers/Hooking/HookingManager.cpp
					Managers/Modules/Module.cpp
					Managers/Modules/ModuleManager.cpp
					Managers/NetVars/NetVarManager.cpp)

set(HACK_HEADERS ../include/Hack.h
				 ../include/Utils/MathHelper.h
                 ../include/Utils/QAngle.h
                 ../include/Utils/Vector.h
                 ../include/Utils/VMTManager.h
                 ../include/Managers/IManager.h
                 ../include/Managers/Offsets/OffsetManager.h
                 ../include/Managers/Interfaces/InterfaceManager.h
				 ../include/Managers/Hooking/HookingManager.h
				 ../include/Managers/Modules/IModule.h
				 ../include/Managers/Modules/Module.h
				 ../include/Managers/Modules/ModuleManager.h
				 ../include/Managers/NetVars/NetVarManager.h)

set(CSGO_INTERFACES ../include/Interfaces/VClient018.h ../include/Interfaces/VClientEntityList003.h
			../include/Interfaces/VEngineClient014.h ../include/Interfaces/VClientMode.h)

set(CSGO_CLASSES	../include/Classes/NetVarStuff/ClientClass.h
					../include/Classes/NetVarStuff/RecvProp.h
					../include/Classes/NetVarStuff/RecvTable.h
					../include/Classes/CUserCmd.h
					../include/Classes/CBaseEntity.h Classes/CBaseEntity.cpp)

set(CSGO_HOOKS		Hooks/hkCreateMove.cpp ../include/Hooks/hkCreateMove.h
					Hooks/hkFrameStageNotify.cpp ../include/Hooks/hkFrameStageNotify.h)

set(CSGO_MODULES    Modules/AntiFlash.cpp	../include/Modules/AntiFlash.h
					Modules/BunnyHop.cpp	../include/Modules/BunnyHop.h
					Modules/Radar.cpp		../include/Modules/Radar.h)

add_library(ProjectPaste SHARED ${HACK_HEADERS} ${CSGO_INTERFACES} ${CSGO_HOOKS} ${CSGO_CLASSES} ${CSGO_MODULES} ${HACK_SOURCES})
target_compile_definitions(ProjectPaste PRIVATE WIN32_LEAN_AND_MEAN)
target_link_libraries(ProjectPaste psapi)

set_target_properties(ProjectPaste PROPERTIES
	C_STANDARD 11
	C_STANDARD_REQUIRED YES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	FOLDER HACK
)

install(TARGETS ProjectPaste RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)
