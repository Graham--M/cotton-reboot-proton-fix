#!/bin/sh
x86_64-w64-mingw32-gcc -shared -o steam_api64.dll       \
                       src/abortmsg.c                   \
                       src/dll_main.c                   \
                       src/shcore_stream.c              \
                       src/mf_impl.c                    \
                       src/steam_api64_reexport.def     \
                       -s -lshcore -luser32 -lmfplat
