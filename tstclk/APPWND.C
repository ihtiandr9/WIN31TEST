
#include <stdio.h>
#include <string.h>
#include <commdlg.h>
#include "appwnd.h"
#include "res.h"

static HINSTANCE hInst = 0;	// current instance
static int nCmdShow;
static HWND hBtnClose;
/**********************************************************************/
// { Forward declarations
WORD AppWnd_run(struct AppWnd* wnd);
// }
/**********************************************************************/
// Default event handlers (replicate original behavior)

static void AppWnd_OnCreate(struct AppWnd* Sender, LPCREATESTRUCT CreateStruct)
{
    RECT rc;
    GetClientRect(Sender->hWnd, &rc);
    hBtnClose = CreateWindow(
        "BUTTON", "&Close",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        (rc.right - 80) / 2, (rc.bottom - 30) / 2,
        80, 30,
        Sender->hWnd,
        (HMENU)CM_EXIT,
        CreateStruct->hInstance,
        NULL
    );
}

static void AppWnd_OnPaint(struct AppWnd* Sender)
{
    RECT rTemp;
    HDC hdc;
    PAINTSTRUCT ps;

    hdc = BeginPaint(Sender->hWnd, &ps);
    GetClientRect(Sender->hWnd, &rTemp);
    rTemp.right  = 75;
    rTemp.bottom = 20;
    DrawText(hdc, "Hello world", 11, &rTemp, DT_CENTER);
    EndPaint(Sender->hWnd, &ps);
}

static void AppWnd_OnCommand(struct AppWnd* Sender, WORD Cmd, HWND hwndCtl)
{
    switch (Cmd)
    {
        case CM_EXIT:
            DestroyWindow(Sender->hWnd);
            break;

        case CM_U_HELPABOUT:
            MessageBox(Sender->hWnd, szCMDLGAPAbout, "About CMDLG", MB_OK);
            break;

        default:
            break;
    }
}

static void AppWnd_OnDestroy(struct AppWnd* Sender)
{
    PostQuitMessage(0);
}

BOOL AppWnd_register(HINSTANCE hInstance)
{
    WNDCLASS  wc;

    if (hInst)
        return TRUE;

    hInst = hInstance;

    // Fill in window class structure with parameters that describe the
    // main window.

    wc.style = CS_HREDRAW | CS_VREDRAW;	// Class style(s).
    wc.lpfnWndProc = (long (FAR PASCAL*)())MainWndProc;	// Function to retrieve messages for
                                                        // windows of this class.
    wc.cbClsExtra = 0;	// No per-class extra data.
    wc.cbWndExtra = sizeof(LONG);	// Per-window extra data for AppWnd* pointer
    wc.hInstance = hInstance;	// Application that owns the class.
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(GRAY_BRUSH);
    wc.lpszMenuName = "TESTCLKMENU";	// Name of menu resource in .RC file.
    wc.lpszClassName = "TESTCLK";	// Name used in call to CreateWindow.

    /* Register the window class and return success/failure code. */

    return (RegisterClass(&wc));

}


/****************************************************************************
	FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)
****************************************************************************/
long FAR PASCAL _export MainWndProc(HWND hWnd, unsigned message,
                                    WORD wParam, LONG lParam)
{
    struct AppWnd* wnd;

    switch (message)
    {
        case WM_CREATE:	// Initialize window: store AppWnd*, call OnCreate
        {
            LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
            wnd = (struct AppWnd*)lpcs->lpCreateParams;
            SetWindowLong(hWnd, 0, (LONG)wnd);
            wnd->hWnd = hWnd;
            if (wnd->OnCreate)
                wnd->OnCreate(wnd, lpcs);
            return 0;
        }

        default:
            break;
    }

    wnd = (struct AppWnd*)GetWindowLong(hWnd, 0);
    if (!wnd)
        return DefWindowProc(hWnd, message, wParam, lParam);

    switch (message)
    {
        case WM_PAINT:
            if (wnd->OnPaint)
                wnd->OnPaint(wnd);
            else
                return DefWindowProc(hWnd, message, wParam, lParam);
            break;

        case WM_COMMAND:	// message: command from application menu
            if (wnd->OnCommand)
                wnd->OnCommand(wnd, wParam, (HWND)LOWORD(lParam));
            else
                return DefWindowProc(hWnd, message, wParam, lParam);
            break;

        case WM_DESTROY:	// message: window being destroyed
            if (wnd->OnDestroy)
                wnd->OnDestroy(wnd);
            PostQuitMessage(0);
            break;

        default:			// Passes it on if unproccessed
            return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (NULL);
}

BOOL AppWnd_create(struct AppWnd* wnd, HINSTANCE hInstance, int _cmd)
{

    HWND hWnd;

    // Set default event handlers
    wnd->OnCreate  = AppWnd_OnCreate;
    wnd->OnPaint   = AppWnd_OnPaint;
    wnd->OnCommand = AppWnd_OnCommand;
    wnd->OnDestroy = AppWnd_OnDestroy;

    nCmdShow = _cmd;
    wnd->run = AppWnd_run;

    AppWnd_register(hInstance);

    /* Create a main window for this application instance.  */
    hWnd = CreateWindow(
        "TESTCLK", 	                   // See RegisterClass() call.
        "Test of machine speed",       // Text for window title bar.
        WS_OVERLAPPEDWINDOW,	       // Window style.
        CW_USEDEFAULT, 		       // Default horizontal position.
        CW_USEDEFAULT,	   	       // Default vertical position.
        CW_USEDEFAULT,	      	       // Default width.
        CW_USEDEFAULT, 		       // Default height.
        NULL,		   	       // Overlapped windows have no parent.
        NULL,	   		       // Use the window class menu.
        hInst,  		       // This instance owns this window.
        wnd			       // Pointer to AppWnd (lpCreateParams)
    );

    /* If window could not be created, return "failure" */

    if (!hWnd)
        return (FALSE);

    wnd->hWnd = hWnd;
    return (TRUE);				// Returns the value from PostQuitMessage

}

WORD AppWnd_run(struct AppWnd* wnd)
{
    HWND hWnd = wnd->hWnd;
    MSG msg;

    ShowWindow(hWnd, nCmdShow);	// Show the window
    UpdateWindow(hWnd);			// Sends WM_PAINT message
    while (GetMessage(&msg,	    // message structure
                NULL,	        // handle of window receiving the message
                NULL,	        // lowest message to examine
                NULL))	        // highest message to examine
    {
 /* Acquire and dispatch messages until a WM_QUIT message is received. */

        TranslateMessage(&msg);	// Translates virtual key codes
        DispatchMessage(&msg);	// Dispatches message to window
    }
    return (msg.wParam);
}
