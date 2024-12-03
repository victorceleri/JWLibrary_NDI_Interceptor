#include "MFHook.h"
#include <Windows.h>
#include <detours.h>
#include <iostream>

// Definição única
HRESULT(WINAPI* OriginalMFCreateMediaSession)(DWORD, IMFAttributes*, IMFMediaSession**) = nullptr;

static HRESULT WINAPI HookedMFCreateMediaSession(DWORD dwFlags, IMFAttributes* pConfiguration, IMFMediaSession** ppMediaSession) {
    std::cout << "[Hooked] MFCreateMediaSession called!" << std::endl;

    HRESULT hr = OriginalMFCreateMediaSession(dwFlags, pConfiguration, ppMediaSession);
    if (SUCCEEDED(hr)) {
        std::cout << "[Hooked] Media Session created successfully!" << std::endl;
    }
    return hr;
}

void InstallMFHook() {
    HMODULE mfcore = GetModuleHandle(L"MFCORE.dll");
    if (mfcore) {
        OriginalMFCreateMediaSession = (HRESULT(WINAPI*)(DWORD, IMFAttributes*, IMFMediaSession**))GetProcAddress(mfcore, "MFCreateMediaSession");
        if (OriginalMFCreateMediaSession) {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&(PVOID&)OriginalMFCreateMediaSession, HookedMFCreateMediaSession);
            DetourTransactionCommit();
        }
    }
}
