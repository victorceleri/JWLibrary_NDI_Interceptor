#pragma once
#ifndef MFHOOK_H
#define MFHOOK_H

#include <mfapi.h>
#include <mfidl.h>

extern HRESULT(WINAPI* OriginalMFCreateMediaSession)(DWORD, IMFAttributes*, IMFMediaSession**);

void InstallMFHook();

#endif // MFHOOK_H
