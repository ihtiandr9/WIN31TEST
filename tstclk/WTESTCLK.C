#include "appwnd.h"

#pragma argsused
/**************************************************************/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;			// message
	if (!hPrevInstance)	// Other instances of app running?
	if (!InitApplication(hInstance))	// Initialize shared things
		return (FALSE);	// Exits if unable to initialize

	/* Perform initializations that apply to a specific instance */

	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	/* Acquire and dispatch messages until a WM_QUIT message is received. */

	while (GetMessage(&msg,	// message structure
		NULL,	// handle of window receiving the message
		NULL,	// lowest message to examine
		NULL))	// highest message to examine
	{
	TranslateMessage(&msg);	// Translates virtual key codes
	DispatchMessage(&msg);	// Dispatches message to window
	}
	return (msg.wParam);	// Returns the value from PostQuitMessage
}

// End of file cmdlg.