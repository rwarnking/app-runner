///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: app-runner.cpp
// Defines the entrypoint for this application.
///////////////////////////////////////////////////////////////////////////////////////////////////


#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>
#include <cstdlib> 
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "framework.h"
#include "app-runner.h"
#include "header/runner.h"


auto WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,  // NOLINT
    _In_ int nShowCmd
) -> int
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // Test a specific location
    //_CrtSetBreakAlloc(0x00A81D18);
    //int * q = new int;

    auto result{ true };

    auto runner = std::make_unique<Runner>();
    result = runner->Init();
    if (result) {
        runner->Run();
    }

    runner->Shutdown();
    runner = nullptr;

    return 0;
}
