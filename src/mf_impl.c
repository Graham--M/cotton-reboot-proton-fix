
#define COBJMACROS

#include "abortmsg.h"
#include "mf_impl.h"
#include <unknwn.h>

HRESULT WINAPI MFCreateMFByteStreamOnStream(IStream *stream, IMFByteStream **bytestream);

HRESULT WINAPI ImplMFCreateMFByteStreamOnStreamEx(IUnknown *stream, IMFByteStream **bytestream) {
    const IID kIID_IStream = {0x0000000c, 0x0000, 0x0000, {0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46}};

    // Try get the internal IStream we wrapped up
    IStream *istream = NULL;
    HRESULT hr = IUnknown_QueryInterface(stream, &kIID_IStream, (void **)&istream);
    if (hr != S_OK) {
        abortmsg("ImplMFCreateMFByteStreamOnStreamEx called with unsupported stream");
        return hr;
    }

    IMFByteStream *mfstream = NULL;
    hr = MFCreateMFByteStreamOnStream(istream, &mfstream);
    if (hr != S_OK) {
        abortmsg("ImplMFCreateMFByteStreamOnStreamEx failed to create MFByteStream");
        IStream_Release(istream);
        return hr;
    }

    *bytestream = mfstream;
    return S_OK;
}
