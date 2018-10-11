#include <Windows.h>

// Inject injection handler here trigger page fault initialize us. unlink us. return execution

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID) {
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
