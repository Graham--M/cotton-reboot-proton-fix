
#include "abortmsg.h"
#include <windows.h>
#include <stdlib.h>

void abortmsg(const char *msg) {
    MessageBox(NULL, msg, "Fatal Error", MB_OK);
    abort();
}
