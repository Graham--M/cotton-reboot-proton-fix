
#define COBJMACROS

#include "abortmsg.h"
#include "shcore_stream.h"
#include "ci_randomaccessstream.h"
#include <objbase.h>
#include <shobjidl.h>
#include <shlwapi.h>
#include <stdlib.h>


// -----------------------------------------------------------------------------
// RandomAccessStream Implementation
// -----------------------------------------------------------------------------

const IID kIID_IUnknown = GUID_IUnknown;
const IID kIID_IInspectable = GUID_IInspectable;
const IID kIID_RandomAccessStream = GUID_RandomAccessStream;

const CIRandomAccessStreamVtbl kRandomAccessStreamVtbl;

struct RAStream {
    CIRandomAccessStreamVtbl const *vtbl;
    LONG refcount;
    IStream *shstream;
};

//
// IUnknown methods
//

static HRESULT WINAPI rastream_QueryInterface(CIRandomAccessStream *iface, REFIID riid, void **out) {
    struct RAStream *stream = (struct RAStream *) iface;

    if (IsEqualIID(riid, &kIID_IUnknown) ||
        IsEqualIID(riid, &kIID_IInspectable) ||
        IsEqualIID(riid, &kIID_RandomAccessStream)) {
        *out = iface;
        CIRandomAccessStream_AddRef(iface);
        return S_OK;
    }

    // Hack to let us unwrap the IStream
    const IID kIID_IStream = {0x0000000c, 0x0000, 0x0000, {0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46}};
    if (IsEqualIID(riid, &kIID_IStream)) {
        IStream_AddRef(stream->shstream);
        *out = stream->shstream;
        return S_OK;
    }

    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI rastream_AddRef(CIRandomAccessStream *iface) {
    struct RAStream *stream = (struct RAStream *) iface;
    ULONG refcount = InterlockedIncrement(&stream->refcount);
    return refcount;
}

static ULONG WINAPI rastream_Release(CIRandomAccessStream *iface) {
    struct RAStream *stream = (struct RAStream *) iface;
    ULONG refcount = InterlockedDecrement(&stream->refcount);

    if (!refcount) {
        IStream_Release(stream->shstream);
        free(stream);
    }

    return refcount;
}

//
// IInspectable methods
//

static HRESULT WINAPI rastream_GetIids(CIRandomAccessStream *iface, ULONG *iidCount, IID **iids) {
    *iidCount = 1;
    *iids = (IID *)&kIID_RandomAccessStream;
    return S_OK;
}

static HRESULT WINAPI rastream_GetRuntimeClassName(CIRandomAccessStream *iface, HSTRING *className) {
    abortmsg("Called RandomAccessStream::GetRuntimeClassName() Stub!");
    return E_NOTIMPL;
}

static HRESULT WINAPI rastream_GetTrustLevel(CIRandomAccessStream *iface, TrustLevel *trustLevel) {
    abortmsg("Called RandomAccessStream::GetTrustLevel() Stub!");
    return E_NOTIMPL;
}

//
// IRandomAccessStream methods
//

static HRESULT WINAPI rastream_get_Size(CIRandomAccessStream *iface, UINT64 *value) {
    abortmsg("Called RandomAccessStream::get_Size() Stub!");
    return E_NOTIMPL;
}

static HRESULT WINAPI rastream_put_Size(CIRandomAccessStream *iface, UINT64 value) {
    abortmsg("Called RandomAccessStream::put_Size() Stub!");
    return E_NOTIMPL;
}

static HRESULT WINAPI rastream_GetInputStreamAt(CIRandomAccessStream *iface, UINT64 position, CIInputStream **stream) {
    abortmsg("Called RandomAccessStream::GetInputStreamAt() Stub!");
    return E_NOTIMPL;
}

static HRESULT WINAPI rastream_GetOutputStreamAt(CIRandomAccessStream *iface, UINT64 position, CIOutputStream **stream) {
    abortmsg("Called RandomAccessStream::GetOutputStreamAt() Stub!");
    return E_NOTIMPL;
}

static HRESULT WINAPI rastream_get_Position(CIRandomAccessStream *iface, UINT64 *position) {
    abortmsg("Called RandomAccessStream::get_Position() Stub!");
    return E_NOTIMPL;
}

static HRESULT WINAPI rastream_Seek(CIRandomAccessStream *iface, UINT64 position) {
    abortmsg("Called RandomAccessStream::Seek() Stub!");
    return E_NOTIMPL;
}

static HRESULT WINAPI rastream_CloneStream(CIRandomAccessStream *iface, CIRandomAccessStream **out) {
    abortmsg("Called RandomAccessStream::CloneStream() Stub!");
    return E_NOTIMPL;
}

static HRESULT WINAPI rastream_get_CanRead(CIRandomAccessStream *iface, boolean *value) {
    abortmsg("Called RandomAccessStream::get_CanRead() Stub!");
    return E_NOTIMPL;
}

static HRESULT WINAPI rastream_get_CanWrite(CIRandomAccessStream *iface, boolean *value) {
    abortmsg("Called RandomAccessStream::get_CanWrite() Stub!");
    return E_NOTIMPL;
}

const CIRandomAccessStreamVtbl kRandomAccessStreamVtbl = {
    rastream_QueryInterface,
    rastream_AddRef,
    rastream_Release,
    rastream_GetIids,
    rastream_GetRuntimeClassName,
    rastream_GetTrustLevel,
    rastream_get_Size,
    rastream_put_Size,
    rastream_GetInputStreamAt,
    rastream_GetOutputStreamAt,
    rastream_get_Position,
    rastream_Seek,
    rastream_CloneStream,
    rastream_get_CanRead,
    rastream_get_CanWrite
};

// -----------------------------------------------------------------------------
// ImplCreateRandomAccessStreamOnFile
// -----------------------------------------------------------------------------

STDAPI ImplCreateRandomAccessStreamOnFile(_In_ PCWSTR filePath,
                                          _In_ DWORD accessMode,
                                          _In_ REFIID riid,
                                          _COM_Outptr_ void **ppv) {
    if (!IsEqualIID(riid, &kIID_RandomAccessStream))
        abortmsg("ImplCreateRandomAccessStreamOnFile: unrecognized GUID");
    DWORD mode = accessMode ? STGM_READWRITE : STGM_READ;

    IStream *shstream;
    HRESULT hr = SHCreateStreamOnFileEx(filePath, mode, 0, 0, NULL, &shstream);
    if (hr != S_OK) {
        abortmsg("ImplCreateRandomAccessStreamOnFile: Failed to create underlying stream");
        return hr;
    }

    struct RAStream *stream = NULL;
    stream = (struct RAStream *) malloc(sizeof(struct RAStream));

    if (!stream) {
        IStream_Release(shstream);
        return E_OUTOFMEMORY;
    }

    stream->vtbl = &kRandomAccessStreamVtbl;
    stream->refcount = 1;
    stream->shstream = shstream;

    *ppv = stream;
    return S_OK;
}
