#include <Windows.h>


/*
		Function definition of the Window Procedure for our window
*/
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	/*
		Register the windows class

		wchar_t is string literal is used here.
		See: https://docs.microsoft.com/en-us/windows/win32/learnwin32/working-with-strings
	*/
	const wchar_t CLASS_NAME[] = L"Baby Steps Window";

	/*
		Use WNDCLASS data structure to register window class with the Operating System
		See: https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa
	*/
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc; // Pointer to the app-defined function: Window Procedure
	wc.hInstance = hInstance;    // handle to the application instance
	wc.lpszClassName = CLASS_NAME; // Window class name (Must be unique)

	/*
		Pass the address of the WNDCLASS to the RegisterClass function to
		register it with the Operating System
	*/
	RegisterClass(&wc);

	/*
		Create the window by calling CreateWindowEx function

		hWnd is the handle to the created window (defined as typedef HANDLE HWND; in Windows.h)
	*/
	HWND hWnd = CreateWindowEx(
		0,						// Window Styles: See: https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles
		CLASS_NAME,				// Window class we defined above
		L"Baby steps towards Windows API", // Title bar text
		WS_OVERLAPPEDWINDOW,		// Window Style (You can combine style values with pipe | )

		// Window Size: Using Defaults here
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,					// Parent Window HWND
		NULL,					// Menu HWND
		hInstance,				// A handle to an instance. This is the base address of the module in memory
		NULL					// Additional App data
	);

	// If Window creation failed CreateWindowEX will return NULL
	if (hWnd == NULL) {
		return 0;
	}

	/*
		Display the window according to the nCmdShow args
		see: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
	*/
	ShowWindow(hWnd, nCmdShow);

	/*
		The Message Loop

		For each thread that creates a window, the operating system creates a queue for window messages.
		Loop and receive all these messages and dispatch them to the correct window procedure

		MSG structure is filled with the info about the message, if a message is successfully pulled from the queue.
		See: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage
	*/

	MSG msg;
	//		Pull a message from the queue(from Head) while queue isn't empty
	while (GetMessage(&msg, NULL, 0, 0)) {
		/*
			TranslateMessage translates virtual-key messages into character messages.
			The character messages are posted to the calling thread's message queue and can be read by the GetMessage
			or PeekMessage function.
		*/
		TranslateMessage(&msg);
		/*
			Dispatches a message to a window procedure. In this case its WindowProc() function defined above
		*/
		DispatchMessage(&msg);

		/*
			Calling PostQuitMessage(0) function Pushes WM_QUIT message to the queue and 
			causes your app to exit and break out of the message loop.
		*/ 
	}

	return 0;
}

/*
	Windows procedure
	hwnd: Handle to the Window
	uMsg: Code of the received message
	wParam and lParam: Additional data passed with the message
*/
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Uses a switch to switch between the received messages
	switch (uMsg)
	{
	case WM_DESTROY:			// On App close
		PostQuitMessage(0);
		return 0;
	/*
		Called when window's client area needs repainting

		See: https://docs.microsoft.com/en-us/windows/win32/gdi/wm-paint
	*/
	case WM_PAINT:				
	{
		PAINTSTRUCT ps;
	//	Beginpaint fills the ps struct with received WM_PAINT message information
		HDC hdc = BeginPaint(hwnd, &ps); 

	/*
		Fills the given rectangle specified in the ps PAINTSTRUCT
		See: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-fillrect
	*/

		/*
			Create a solid RebeccaPurple color brush to paint the client area of the window
			See: https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createsolidbrush
		*/
		HBRUSH hBrush = CreateSolidBrush(RGB(102, 51, 153));
		FillRect(hdc, &ps.rcPaint, hBrush);

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	/*
		Calls the default Windows Procedure
		see: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-defwindowproca
	*/
	return DefWindowProc(hwnd, uMsg, wParam, lParam); 
}



