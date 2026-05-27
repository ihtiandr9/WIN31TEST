
#include <stdio.h>
#include <string.h>
#include <commdlg.h>
#include "appwnd.h"
#include "res.h"

static HINSTANCE hInst = 0;	// current instance
static int nCmdShow;
/**********************************************************************/
// { Forward declarations
WORD AppWnd_run(struct AppWnd* wnd);
// }
/**********************************************************************/
BOOL AppWnd_register(HINSTANCE hInstance)
{
	WNDCLASS  wc;

    if(hInst)
        return TRUE;

    hInst = hInstance;

	// Fill in window class structure with parameters that describe the
	// main window.

	wc.style = CS_HREDRAW | CS_VREDRAW;	// Class style(s).
	wc.lpfnWndProc = (long (FAR PASCAL*)())MainWndProc;	// Function to retrieve messages for
														// windows of this class.
	wc.cbClsExtra = 0;	// No per-class extra data.
	wc.cbWndExtra = 0;	// No per-window extra data.
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
    HFONT fTemp;	// Placeholder for the original font
    RECT rTemp;     // Client are needed by DrawText()
    HDC hdc;        // HDC for Window
    PAINTSTRUCT ps;	// Paint Struct for BeginPaint call

    switch (message) {
        case WM_CREATE: // Initialize Global vars
            break;

        case WM_PAINT:
            // Display the file name using the selected font in the selected color.

            hdc=BeginPaint(hWnd, &ps);
            GetClientRect( hWnd, &rTemp );
            rTemp.right  = 75;
            rTemp.bottom = 20;
            DrawText( hdc, "Hello world", 11, &rTemp, DT_CENTER );
            /*SetTextColor( hdc, crColor );
              if( tfFontLoaded == TRUE )
              fTemp = (HFONT)SelectObject( hdc, hfFont );
              
              if( tfFontLoaded == TRUE )
              SelectObject( hdc, fTemp );
              */
            EndPaint(hWnd,&ps);
            break;

        case WM_COMMAND:	// message: command from application menu
            switch(wParam)
            {
                case CM_EXIT:
                    DestroyWindow(hWnd);
                    break;


                case CM_U_HELPABOUT:
                    MessageBox(hWnd,szCMDLGAPAbout,"About CMDLG",MB_OK);
                    break;

                default:
                    break;
            }
            break;

        case WM_QUIT:
        case WM_DESTROY:	// message: window being destroyed
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
    nCmdShow = _cmd;
    wnd->run = AppWnd_run;

    AppWnd_register(hInstance);
    
	/* Create a main window for this application instance.  */
	hWnd = CreateWindow(
		"TESTCLK", 	               // See RegisterClass() call.
		"Test of machine speed",       // Text for window title bar.
		WS_OVERLAPPEDWINDOW,	       // Window style.
		CW_USEDEFAULT, 		       // Default horizontal position.
		CW_USEDEFAULT,	   	       // Default vertical position.
		CW_USEDEFAULT,	      	       // Default width.
		CW_USEDEFAULT, 		       // Default height.
		NULL,		   	       // Overlapped windows have no parent.
		NULL,	   		       // Use the window class menu.
		hInst,  		       // This instance owns this window.
		NULL			       // Pointer not needed.
	);

	/* If window could not be created, return "failure" */

	if (!hWnd)
		return (FALSE);

	/* Make the window visible; update its client area; and return "success" */

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
