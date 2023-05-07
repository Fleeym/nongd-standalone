#include "includes.hpp"
#include "CustomSongWidget.hpp"

DWORD WINAPI thread_func(void* hModule) {
    MH_Initialize();
    MH_CreateHook(
        reinterpret_cast<void*>(gd::base + 0x685B0),
        reinterpret_cast<void*>(CustomSongWidget_initH),
        reinterpret_cast<void**>(&CustomSongWidget_initO)
    );
    MH_CreateHook(
        reinterpret_cast<void*>(gd::base + 0x69280),
        reinterpret_cast<void*>(CustomSongWidget_updateSongObjectH),
        reinterpret_cast<void**>(&CustomSongWidget_updateSongObjectO)
    );

    MH_EnableHook(MH_ALL_HOOKS);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        auto h = CreateThread(0, 0, thread_func, handle, 0, 0);
        if (h)
            CloseHandle(h);
        else
            return FALSE;
    }
    return TRUE;
}