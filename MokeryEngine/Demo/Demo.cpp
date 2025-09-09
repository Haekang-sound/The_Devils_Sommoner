#include "pch.h"
#include "resource.h"
#include "GameProcess.h"

#ifdef _DEBUG
	#ifdef UNICODE
	#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else
	#pragma comment(linker, "/entry:WinMainCRTStartup/subsystem:console")
	#endif
#endif


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPWSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(13889);	// 메모리누수를 찾는 훌륭한 함수

	GameProcess* gameProcess = new GameProcess();
	gameProcess->Initialize(hInstance);
	gameProcess->Loop();
	gameProcess->Finalize();

	delete gameProcess;

	_CrtDumpMemoryLeaks();

	return 0;
}


