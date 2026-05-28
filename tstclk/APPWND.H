#ifndef H_APPWND_H
#define H_APPWND_H

#define STRICT
#include <windows.h>

long FAR PASCAL _export MainWndProc(HWND, unsigned, WORD, LONG);

struct AppWnd;

struct AppWnd {
    HWND hWnd;
    HWND hBtnClose;
    HINSTANCE hInstance;
    WORD (*run)(struct AppWnd*);

    // Event handlers (C++ Builder 5 VCL style TNotifyEvent)
    void (*OnCreate)(struct AppWnd* Sender, LPCREATESTRUCT CreateStruct);
    void (*OnPaint)(struct AppWnd* Sender);
    void (*OnSize)(struct AppWnd* Sender, WORD ResizeType, WORD Width, WORD Height);
    void (*OnCommand)(struct AppWnd* Sender, WORD Cmd, HWND hwndCtl);
    void (*OnDestroy)(struct AppWnd* Sender);
};

BOOL AppWnd_create(struct AppWnd* wnd, HINSTANCE hInstance, int _cmd);
WORD AppWnd_run(struct AppWnd* wnd);

#endif

