#include "appwnd.h"

#pragma argsused
/**************************************************************/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
    struct AppWnd main;

    if (!hPrevInstance)	// Other instances of app running?
    {
        //if (!InitApplication(hInstance))	// Initialize shared things
        //	return (FALSE);	// Exits if unable to initialize

        AppWnd_create(&main, hInstance, nCmdShow);
        return main.run(&main);
    }else
        return -1;
}

