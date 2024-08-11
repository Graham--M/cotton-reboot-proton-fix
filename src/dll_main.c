
#include "shcore_stream.h"
#include "mf_impl.h"

#include <windows.h>
#include <oleidl.h>

__declspec(dllimport)
STDAPI CreateRandomAccessStreamOnFile(_In_ PCWSTR filePath, _In_ DWORD accessMode, _In_ REFIID riid, _COM_Outptr_ void **ppv);

__declspec(dllexport) void __cdecl __HorribleHackKeepSymbolsDoNotCall() {
    // Guarantee that shcore.dll is linked in at load by referencing a symbol.
    // No idea if LoadLibrary() works in DllMain() and you're not supposed
    // to call it there in Windows.
    CreateRandomAccessStreamOnFile(0, 0, 0, 0);
}

int patch_dll(const char *dllname, const char *symbol, void *addr) {
    HMODULE hmodule = GetModuleHandleA(dllname);
    if (!hmodule) abort();
    FARPROC target = GetProcAddress(hmodule, symbol);
    if (!target) abort();

    DWORD old_protect;
    if (!VirtualProtect(target, 12, PAGE_EXECUTE_READWRITE, &old_protect))
        abort();

    // movabs rax,0x0000000000000000
    // jmp rax
    unsigned char buffer[12] = {0x48,0xb8,0,0,0,0,0,0,0,0,0xff,0xe0};

    // Write the new jump address to the opcode
    unsigned long long addr_buf = (unsigned long long) addr;
    unsigned char *p = (unsigned char *) &addr_buf;
    for (unsigned i = 0; i < 8; i++)
        buffer[i + 2] = p[i];

    // And write in the new instructions
    p = (unsigned char *) target;
    for (unsigned i = 0; i < 12; i++)
        p[i] = buffer[i];

    if (!VirtualProtect(target, 12, old_protect, &old_protect))
        abort();

    if (!FlushInstructionCache(GetCurrentProcess(), target, 12))
        abort();

    return 0;
}

#if BUILD_FOR_DEBUGGER
#define WAIT_FOR_DEBUGER() MessageBox(NULL, "Pausing for debugger attachment", "Info", MB_OK)
#else
#define WAIT_FOR_DEBUGER()
#endif

BOOL APIENTRY DllMain(HMODULE hModule,  DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call)  {
    case DLL_PROCESS_ATTACH:
      WAIT_FOR_DEBUGER();
      patch_dll("shcore", "CreateRandomAccessStreamOnFile",
                &ImplCreateRandomAccessStreamOnFile);

      patch_dll("mfplat", "MFCreateMFByteStreamOnStreamEx",
                &ImplMFCreateMFByteStreamOnStreamEx);
      break;
    case DLL_PROCESS_DETACH:
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    }
    return TRUE;
}
