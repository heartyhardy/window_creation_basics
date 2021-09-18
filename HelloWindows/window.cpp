#include <Windows.h>

// Define Windows Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// WinMain
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	
	const wchar_t CLASS_NAME[] = L"My Window Class";

	//Build from WinClass
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"My Window",
		WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL) {
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);


	// Message loop
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// Define WindowProc
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// Switch to messages
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HBRUSH hBrush = CreateSolidBrush(RGB(102, 51, 153));
		HBRUSH hPatternBrush = CreateHatchBrush(HS_CROSS, RGB(125, 125, 175));
		HFONT hFont;
		RECT r;


		TCHAR text[] = L"C++: Oh! It works!";
		int txtArraySize = ARRAYSIZE(text);

		GetClientRect(hwnd, &r);

		HDC hdc = BeginPaint(hwnd, &ps);
		
		// Create font
		hFont = CreateFont(64, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
		
		// Set Font
		SelectObject(hdc, hFont);

		// Set Font color and Background color
		SetTextColor(hdc, RGB(255, 180, 63));
		SetBkColor(hdc, RGB(102, 51, 153));

		// Fill background with pattern brush
		FillRect(hdc, &ps.rcPaint, hPatternBrush);

		// Draw text with specified font and text
		DrawText(hdc, text, txtArraySize, &r, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		EndPaint(hwnd, &ps);
	}
	return 0;

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}