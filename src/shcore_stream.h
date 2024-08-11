
#pragma once

#include <windows.h>
#include <oleidl.h>

STDAPI ImplCreateRandomAccessStreamOnFile(_In_ PCWSTR filePath,
                                          _In_ DWORD accessMode,
                                          _In_ REFIID riid,
                                          _COM_Outptr_ void **ppv);
