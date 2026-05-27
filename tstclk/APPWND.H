
#define STRICT

#include <windows.h>

long FAR PASCAL _export MainWndProc(HWND, unsigned, WORD, LONG);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
