
// Contains the necessary headers and definitions for this program
#include <stdio.h>
#include <string.h>
#include <commdlg.h>
#include "appwnd.h"
#include "res.h"

/***  Global Variables  ***/
char szName[256];
//COLORREF crColor;
HFONT hfFont;
//BOOL tfFontLoaded;
HINSTANCE hInst;	// current instance

/**********************************************************************/
BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;

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
	wc.hbrBackground = GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = "CMDLGAPMENU";	// Name of menu resource in .RC file.
	wc.lpszClassName = "CMDLG";	// Name used in call to CreateWindow.

	/* Register the window class and return success/failure code. */

	return (RegisterClass(&wc));

}


/************************************************************************/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND	hWnd;	// Main window handle.

	/* Save the instance handle in static variable, which will be used in  */
	/* many subsequence calls from this application to Windows.            */

	hInst = hInstance;

	/* Create a main window for this application instance.  */

	hWnd = CreateWindow(
		"CMDLG", 	               // See RegisterClass() call.
		"Test of machine speed",       // Text for window title bar.
		WS_OVERLAPPEDWINDOW,	       // Window style.
		CW_USEDEFAULT, 		       // Default horizontal position.
		CW_USEDEFAULT,	   	       // Default vertical position.
		CW_USEDEFAULT,	      	       // Default width.
		CW_USEDEFAULT, 		       // Default height.
		NULL,		   	       // Overlapped windows have no parent.
		NULL,	   		       // Use the window class menu.
		hInstance,  		       // This instance owns this window.
		NULL			       // Pointer not needed.
	);

	/* If window could not be created, return "failure" */

	if (!hWnd)
		return (FALSE);

	/* Make the window visible; update its client area; and return "success" */

	ShowWindow(hWnd, nCmdShow);	// Show the window
	UpdateWindow(hWnd);			// Sends WM_PAINT message
	return (TRUE);				// Returns the value from PostQuitMessage

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
			strcpy( szName, "" );           // Empty the file name string
		/*	crColor = RGB( 0, 0, 0 );       // Use black as the default color
			hfFont = 0;                     // Empty the handle to the font
			tfFontLoaded = FALSE;           // Set the font selected flag to false
		*/
		return NULL;

	case WM_PAINT:
	// Display the file name using the selected font in the selected color.

			hdc=BeginPaint(hWnd,&ps);
			/*SetTextColor( hdc, crColor );
			if( tfFontLoaded == TRUE )
				fTemp = (HFONT)SelectObject( hdc, hfFont );
			GetClientRect( hWnd, &rTemp );
			DrawText( hdc, szName, strlen( szName ), &rTemp, DT_CENTER | DT_WORDBREAK );
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
			if( hfFont != 0 )
				DeleteObject( hfFont );
			PostQuitMessage(0);
		break;

	default:			// Passes it on if unproccessed
		return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (NULL);
}