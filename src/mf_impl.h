
#pragma once
#include <oleidl.h>

typedef interface IMFByteStream IMFByteStream;

HRESULT WINAPI ImplMFCreateMFByteStreamOnStreamEx(IUnknown *stream, IMFByteStream **bytestream);
