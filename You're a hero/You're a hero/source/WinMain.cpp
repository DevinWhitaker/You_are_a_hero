#include <windows.h>	//	Needed for Windows Applications.
#include <tchar.h>
#include "Game.h"

#if _DEBUG
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#endif

#if _DUMP
//#include <dbghelp.h>	//	Used for Dump File
//#pragma comment(lib, "dbghelp.lib")

//	Handler function that writes out a dump file
LONG WINAPI Handler(_EXCEPTION_POINTERS * exPointers)
{
	HANDLE theFile = CreateFileA("myDumpFile.mdmp", 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (theFile != INVALID_HANDLE_VALUE)
	{
		_MINIDUMP_EXCEPTION_INFORMATION exInfo;
		exInfo.ClientPointers = NULL;
		exInfo.ThreadId = GetCurrentThreadId();
		exInfo.ExceptionPointers = exPointers;
		
		// Write The Minidump
		MiniDumpWriteDump(GetCurrentProcess(),
			GetCurrentProcessId(),
			theFile,
			MiniDumpNormal,
			&exInfo,
			NULL,
			NULL);
		MessageBoxA(0, "myDumpFile.mdmp", "MiniDump was saved",MB_OK);

	}


	return EXCEPTION_EXECUTE_HANDLER;
}
#endif

const TCHAR* g_szWINDOW_CLASS_NAME	= _T("You're a hero?");			//	Window Class Name.

const TCHAR* g_szWINDOW_TITLE		= _T("You're a hero?");			//	Window Title.
const int	g_nWINDOW_WIDTH			= 800;							//	Window Width.
const int	g_nWINDOW_HEIGHT		= 600;							//	Window Height.

//	Windowed or Full screen depending on project setting
#ifdef _DEBUG
	const BOOL	g_bIS_WINDOWED			= TRUE;						
#else
	const BOOL	g_bIS_WINDOWED			= FALSE;
#endif

	static Game* pGamePtr(nullptr);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//	This is the main message handler of the system.
	switch(msg)
	{
		//	To skip ALT pop up menu (system menu)
		case WM_SYSKEYUP:
		case WM_SYSCHAR:
			return(0);
		break;
		
		//	Handle ALT+F4
		case WM_CLOSE:
		{
			// Sends us a WM_DESTROY
			DestroyWindow(hWnd);			
		}
		break;

		//	and lose/gain focus
		case WM_ACTIVATE:
		{
			//	gaining focus
			if (LOWORD(wParam) != WA_INACTIVE)
			{
				// unpause game code here
				if(pGamePtr)
				{
					pGamePtr->Pause(false);
				}
			}
			else // losing focus
			{
				// pause game code here
				pGamePtr->Pause(true);
			}
		}
		break;

		case WM_CREATE: 
		{
			//	Do initialization here
			return(0);
		}
		break;

		case WM_DESTROY: 
		{
			//	Kill the application			
			PostQuitMessage(0);
			return(0);
		}
		break;
	}

	//	Process any messages that we didn't take care of 
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//	Checks to see if the game was already running in another window.
BOOL CheckIfAlreadyRunning(void)
{
	//	Find a window of the same window class name and window title
	HWND hWnd = FindWindow(g_szWINDOW_CLASS_NAME, g_szWINDOW_TITLE);

	//	If one was found
	if (hWnd)
	{
		//	If it was minimized
		if (IsIconic(hWnd))
		{
			//	restore it
			ShowWindow(hWnd, SW_RESTORE);
		}

		//	Bring it to the front
		SetForegroundWindow(hWnd);

		return TRUE;
	}

	//	No other copies found running
	return FALSE;
}


BOOL RegisterWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX	winClassEx;	//	This will describe the window class we will create.

	//	First fill in the window class structure
	winClassEx.cbSize			= sizeof(winClassEx);
	winClassEx.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClassEx.lpfnWndProc		= WindowProc;
	winClassEx.cbClsExtra		= 0;
	winClassEx.cbWndExtra		= 0;
	winClassEx.hInstance		= hInstance;
	winClassEx.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINLOGO) );
	winClassEx.hIconSm			= winClassEx.hIcon;
	winClassEx.hIconSm			= NULL;
	winClassEx.hCursor			= LoadCursor(NULL, IDC_ARROW);
	winClassEx.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClassEx.lpszMenuName		= NULL; 
	winClassEx.lpszClassName	= g_szWINDOW_CLASS_NAME;

	//	Register the window class
	return RegisterClassEx(&winClassEx);
}

//	Creates and sizes the window appropriately depending on if 
//	the application is windowed or full screen.
HWND MakeWindow(HINSTANCE hInstance)
{
	// Setup window style flags
	DWORD dwWindowStyleFlags = WS_VISIBLE;

	if (g_bIS_WINDOWED)
	{
		dwWindowStyleFlags |= WS_OVERLAPPEDWINDOW;
	}
	else
	{
		dwWindowStyleFlags |= WS_POPUP;
		ShowCursor(FALSE);	// Stop showing the mouse cursor
	}

	// Setup the desired client area size
	RECT rWindow;
	rWindow.left	= 0;
	rWindow.top		= 0;
	rWindow.right	= g_nWINDOW_WIDTH;
	rWindow.bottom	= g_nWINDOW_HEIGHT;

	// Get the dimensions of a window that will have a client rect that
	// will really be the resolution we're looking for.
	AdjustWindowRectEx(&rWindow, 
						dwWindowStyleFlags,
						FALSE, 
						WS_EX_APPWINDOW);
	
	// Calculate the width/height of that window's dimensions
	int nWindowWidth	= rWindow.right - rWindow.left;
	int nWindowHeight	= rWindow.bottom - rWindow.top;


	//	Create the window
	return CreateWindowEx(WS_EX_APPWINDOW,											//	Extended Style flags.
						  g_szWINDOW_CLASS_NAME,									//	Window Class Name.
						  g_szWINDOW_TITLE,											//	Title of the Window.
						  dwWindowStyleFlags,										//	Window Style Flags.
						  (GetSystemMetrics(SM_CXSCREEN)/2) - (nWindowWidth/2),		//	Window Start Point (x, y). 
						  (GetSystemMetrics(SM_CYSCREEN)/2) - (nWindowHeight/2),	//		-Does the math to center the window over the desktop.
						  nWindowWidth,												//	Width of Window.
						  nWindowHeight,											//	Height of Window.
						  NULL,														//	Handle to parent window.
						  NULL,														//	Handle to menu.
						  hInstance,												//	Application Instance.
						  NULL);													//	Creation parameters.
}

//////////////////////////
//		WinMain			//
//////////////////////////

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;	//	Generic message.
	HWND	hWnd;	//	Main Window Handle.

#if _DUMP
	//	if in release mode set the exception filter to write out a dump file
#ifndef _DEBUG
	SetUnhandledExceptionFilter(Handler);
#endif
#endif

	// Don't let more than one instance of the application exist
	if (!hPrevInstance)
	{
		if (CheckIfAlreadyRunning())
			return FALSE;
	}

	//	Register the window class
	if (!RegisterWindowClass(hInstance))
		return 0;

	//	Create the window
	hWnd = MakeWindow(hInstance);

	if (!hWnd)
		return 0;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

#if _DEBUG
	///////////////////////////////////////////////////////////
	//Allow console window for debuging
	//Code By:
	//http://justcheckingonall.wordpress.com/2008/08/29/console-window-win32-app/
	///////////////////////////////////////////////////////////
	AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;
	////////////////////////////////////////////////////////////
#endif

	//////////////////////////////////////////
	//	Initialize Game here
	//////////////////////////////////////////
	Game cGameInstance;
	cGameInstance.Initialize();
	pGamePtr = &cGameInstance;
	//////////////////////////////////////////

	//	Enter main event loop
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{ 
			//	Test if this is a quit
			if (msg.message == WM_QUIT)
				break;
		
			//	Translate any accelerator keys
			TranslateMessage(&msg);

			//	Send the message to the window proc
			DispatchMessage(&msg);
		}
		
		//////////////////////////////////
		//	Put Game Logic Here
		//////////////////////////////////
		cGameInstance.Run();
		//////////////////////////////////
	}

	/////////////////////////////////////////
	//	Shutdown Game Here
	/////////////////////////////////////////
	cGameInstance.Shutdown();
	/////////////////////////////////////////
	
	
	//	Unregister the window class
	UnregisterClass(g_szWINDOW_CLASS_NAME, hInstance);
	
	//	Return to Windows like this.
	return (int)(msg.wParam);
}