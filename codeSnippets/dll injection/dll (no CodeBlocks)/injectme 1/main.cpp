#include "main.h"

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH: // attach to process // return FALSE to fail DLL load


            MessageBox(NULL, "DLL_PROCESS_ATTACH", "DLL_PROCESS_ATTACH", MB_ICONERROR | MB_OK);

            break;

        case DLL_PROCESS_DETACH: // detach from process


            MessageBox(NULL, "DLL_PROCESS_DETACH", "DLL_PROCESS_DETACH", MB_ICONERROR | MB_OK);

            break;

        case DLL_THREAD_ATTACH: // attach to thread

            MessageBox(NULL, "DLL_THREAD_ATTACH", "DLL_THREAD_ATTACH", MB_ICONERROR | MB_OK);


            break;

        case DLL_THREAD_DETACH: // detach from thread

            MessageBox(NULL, "DLL_THREAD_DETACH", "DLL_THREAD_DETACH", MB_ICONERROR | MB_OK);

            break;
    }
    return TRUE; // succesful
}

