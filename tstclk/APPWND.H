
#define STRICT

#include <windows.h>

long FAR PASCAL _export MainWndProc(HWND, unsigned, WORD, LONG);

struct AppWnd{
   HWND hWnd;
   HINSTANCE hInstance;
   WORD (*run)(struct AppWnd*);
};

BOOL AppWnd_create(struct AppWnd* wnd, HINSTANCE hInstance, int _cmd);
WORD AppWnd_run(struct AppWnd* wnd);

