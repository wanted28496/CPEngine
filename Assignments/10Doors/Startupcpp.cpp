#include"Engine.h"
#include"10Doors.h"
#include"GLib.h"

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>
#endif // _DEBUG

#include<assert.h>
#include<iostream>
#include<Windows.h>

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow) {
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "10 Doors", -1, 800, 600);

	if (bSuccess) {
		if (Engine::__Init__()) {
			if (Doors::Start()) {
				Engine::__Run__();

				Doors::OnExit();

			}
			Engine::__TerminateProgram__();
		}
	}

	GLib::Shutdown();

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}