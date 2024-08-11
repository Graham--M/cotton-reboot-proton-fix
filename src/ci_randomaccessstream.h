
#pragma once

#include <windows.h>
#include <oleidl.h>
#include <winstring.h>
#include <inspectable.h>

typedef interface CIInputStream CIInputStream;
typedef interface CIOutputStream CIOutputStream;
typedef interface CIRandomAccessStream CIRandomAccessStream;

#ifndef GUID_IUnknown
#define GUID_IUnknown \
        {0x00000000, 0x0000, 0x0000, {0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}}
#endif

#ifndef GUID_IInspectable
#define GUID_IInspectable \
        {0xaf86e2e0, 0xb12d, 0x4c6a, {0x9c, 0x5a, 0xd7, 0xaa, 0x65, 0x10, 0x1e, 0x90}}
#endif

#ifndef GUID_RandomAccessStream
#define GUID_RandomAccessStream \
        {0x905a0fe1, 0xbc53, 0x11df, {0x8c, 0x49, 0x00, 0x1e, 0x4f, 0xc6, 0x86, 0xda}}
#endif

typedef struct CIRandomAccessStreamVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        CIRandomAccessStream *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        CIRandomAccessStream *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        CIRandomAccessStream *This);

    /*** IInspectable methods ***/
    HRESULT (STDMETHODCALLTYPE *GetIids)(
        CIRandomAccessStream *This,
        ULONG *iidCount,
        IID **iids);

    HRESULT (STDMETHODCALLTYPE *GetRuntimeClassName)(
        CIRandomAccessStream *This,
        HSTRING *className);

    HRESULT (STDMETHODCALLTYPE *GetTrustLevel)(
        CIRandomAccessStream *This,
        TrustLevel *trustLevel);

    /*** IRandomAccessStream methods ***/
    HRESULT (STDMETHODCALLTYPE *get_Size)(
        CIRandomAccessStream *This,
        UINT64 *value);

    HRESULT (STDMETHODCALLTYPE *put_Size)(
        CIRandomAccessStream *This,
        UINT64 value);

    HRESULT (STDMETHODCALLTYPE *GetInputStreamAt)(
        CIRandomAccessStream *This,
        UINT64 position,
        CIInputStream **stream);

    HRESULT (STDMETHODCALLTYPE *GetOutputStreamAt)(
        CIRandomAccessStream *This,
        UINT64 position,
        CIOutputStream **stream);

    HRESULT (STDMETHODCALLTYPE *get_Position)(
        CIRandomAccessStream *This,
        UINT64 *value);

    HRESULT (STDMETHODCALLTYPE *Seek)(
        CIRandomAccessStream *This,
        UINT64 position);

    HRESULT (STDMETHODCALLTYPE *CloneStream)(
        CIRandomAccessStream *This,
        CIRandomAccessStream **stream);

    HRESULT (STDMETHODCALLTYPE *get_CanRead)(
        CIRandomAccessStream *This,
        boolean *value);

    HRESULT (STDMETHODCALLTYPE *get_CanWrite)(
        CIRandomAccessStream *This,
        boolean *value);

    END_INTERFACE
} CIRandomAccessStreamVtbl;

interface CIRandomAccessStream {
    CONST_VTBL CIRandomAccessStreamVtbl* lpVtbl;
};

/*** IUnknown methods ***/
static inline HRESULT CIRandomAccessStream_QueryInterface(CIRandomAccessStream* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG CIRandomAccessStream_AddRef(CIRandomAccessStream* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG CIRandomAccessStream_Release(CIRandomAccessStream* This) {
    return This->lpVtbl->Release(This);
}
/*** IInspectable methods ***/
static inline HRESULT CIRandomAccessStream_GetIids(CIRandomAccessStream* This,ULONG *iidCount,IID **iids) {
    return This->lpVtbl->GetIids(This,iidCount,iids);
}
static inline HRESULT CIRandomAccessStream_GetRuntimeClassName(CIRandomAccessStream* This,HSTRING *className) {
    return This->lpVtbl->GetRuntimeClassName(This,className);
}
static inline HRESULT CIRandomAccessStream_GetTrustLevel(CIRandomAccessStream* This,TrustLevel *trustLevel) {
    return This->lpVtbl->GetTrustLevel(This,trustLevel);
}
/*** IRandomAccessStream methods ***/
static inline HRESULT CIRandomAccessStream_get_Size(CIRandomAccessStream* This,UINT64 *value) {
    return This->lpVtbl->get_Size(This,value);
}
static inline HRESULT CIRandomAccessStream_put_Size(CIRandomAccessStream* This,UINT64 value) {
    return This->lpVtbl->put_Size(This,value);
}
static inline HRESULT CIRandomAccessStream_GetInputStreamAt(CIRandomAccessStream* This,UINT64 position,CIInputStream **stream) {
    return This->lpVtbl->GetInputStreamAt(This,position,stream);
}
static inline HRESULT CIRandomAccessStream_GetOutputStreamAt(CIRandomAccessStream* This,UINT64 position,CIOutputStream **stream) {
    return This->lpVtbl->GetOutputStreamAt(This,position,stream);
}
static inline HRESULT CIRandomAccessStream_get_Position(CIRandomAccessStream* This,UINT64 *value) {
    return This->lpVtbl->get_Position(This,value);
}
static inline HRESULT CIRandomAccessStream_Seek(CIRandomAccessStream* This,UINT64 position) {
    return This->lpVtbl->Seek(This,position);
}
static inline HRESULT CIRandomAccessStream_CloneStream(CIRandomAccessStream* This,CIRandomAccessStream **stream) {
    return This->lpVtbl->CloneStream(This,stream);
}
static inline HRESULT CIRandomAccessStream_get_CanRead(CIRandomAccessStream* This,boolean *value) {
    return This->lpVtbl->get_CanRead(This,value);
}
static inline HRESULT CIRandomAccessStream_get_CanWrite(CIRandomAccessStream* This,boolean *value) {
    return This->lpVtbl->get_CanWrite(This,value);
}
