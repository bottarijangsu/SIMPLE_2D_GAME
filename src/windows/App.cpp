#include "App.h"
#include"mainData.h"

wchar_t* utf8_to_utf16(const char* str);
void showMessageBox(const char* title, const char* msg);

HINSTANCE hInstance = NULL;
HWND hWnd = NULL;
HDC hDC = NULL;
LPCTSTR windowClassName;

bool isFullscreen;
bool runWnd;
void exitProgram()
{
	runWnd = false;
}

bool createWindow(int width, int height, int bits, bool fullscreen);
void destroyWindow();

void resizeWindow(int width, int height);
void resizeWindow(int width, int height)
{
	wndSize.width = width;
	wndSize.height = height;

	if (devSize.width / devSize.height < wndSize.width / wndSize.height)
	{
		viewport.origin.y = 0;
		viewport.size.height = wndSize.height;
		viewport.size.width = viewport.size.height * devSize.width / devSize.height;
		viewport.origin.x = (wndSize.width - viewport.size.width) / 2;
	}
	else if (devSize.width / devSize.height > wndSize.width / wndSize.height)
	{
		viewport.origin.x = 0;
		viewport.size.width = wndSize.width;
		viewport.size.height = viewport.size.width * devSize.height / devSize.width;
		viewport.origin.y = (wndSize.height - viewport.size.height) / 2;
	}
	else
	{
		viewport.origin.x = viewport.origin.y = 0;
		viewport.size.width = wndSize.width;
		viewport.size.height = wndSize.height;
	}
}

void setCurrentMonitor(RECT& rt)
{
	GetWindowRect(hWnd, &rt);
	HMONITOR hMonintor = MonitorFromRect(&rt, MONITOR_DEFAULTTONEAREST);
	MONITORINFO mi;
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(hMonintor, &mi);
	if (mi.dwFlags == MONITORINFOF_PRIMARY)
	{
		rt.left = 0;
		rt.top = 0;
		rt.right = GetSystemMetrics(SM_CXSCREEN);
		rt.bottom = GetSystemMetrics(SM_CYSCREEN);
	}
	else
	{
		memcpy(&rt, &mi.rcWork, sizeof(RECT));
	}
}

RECT rtPrev;
void goFullscreen()
{
	isFullscreen = !isFullscreen;
	if (isFullscreen)
	{
		GetWindowRect(hWnd, &rtPrev);
		RECT rt;
		setCurrentMonitor(rt);
		int x = rt.left, y = rt.top;
		int w = rt.right - rt.left, h = rt.bottom - rt.top;
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
		SetWindowPos(hWnd, HWND_TOPMOST, x, y, w, h, SWP_SHOWWINDOW);
	}
	else
	{
		int x = rtPrev.left, y = rtPrev.top;
		int w = rtPrev.right - rtPrev.left, h = rtPrev.bottom - rtPrev.top;
		SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, x, y, w, h, SWP_SHOWWINDOW);
	}
}

iPoint converCoordinate(int x, int y)
{
	RECT rt;
	GetClientRect(hWnd, &rt);

	x -= rt.left;
	y -= rt.top;
	return iPointMake((x - viewport.origin.x) * devSize.width / viewport.size.width,
			(y - viewport.origin.y) * devSize.height / viewport.size.height);
}

static bool bCursor;
static Texture* texCursor;
static iPoint cursor;
static bool mouseBegan;
void loadCursor()
{
	bCursor = false;
	texCursor = MOUSE_CURSOR();
	cursor = iPointZero;
	mouseBegan = false;
}

void freeCursor()
{
	freeImage(texCursor);
}

bool updateCursor(bool inClient)
{
	if (bCursor == inClient)
		return false;

	bCursor = inClient;
	ShowCursor(bCursor ? FALSE : TRUE);

	return true;
}

void drawCursor()
{
	if (bCursor)
	{
		if (texCursor == NULL)
			return;
		float scale = (mouseBegan ? 0.5f : 1.0f);
		drawImage(texCursor, cursor.x-texCursor->width/2, cursor.y-texCursor->height/2, texCursor->width * scale, texCursor->height * scale,
				0);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdList, int nCmd)
{
	monitorSize.width = GetSystemMetrics(SM_CXSCREEN);
	monitorSize.height = GetSystemMetrics(SM_CYSCREEN);
	devSize.width = DEV_WIDTH;
	devSize.height = DEV_HEIGHT;

	wndSize.height = DEV_HEIGHT/2;
	wndSize.width = DEV_WIDTH/2;

	wndSize.height += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME) * 2;
	wndSize.width += GetSystemMetrics(SM_CXFRAME) * 2;
	resizeWindow(wndSize.width, wndSize.height);

	isFullscreen = false;
	loadLib(devSize);

	if (!createWindow(wndSize.width, wndSize.height, 32, isFullscreen))
	{
		showMessageBox("FAILED", "CREATE WINDOW FAILED");
		destroyWindow();
		return 0;
	}


	RECT rt;
	GetWindowRect(hWnd, &rt);
	int wndX = monitorSize.width / 2 - wndSize.width / 2;
	int wndY = monitorSize.height / 2 - wndSize.height / 2;
	MoveWindow(hWnd, wndX, wndY, wndSize.width, wndSize.height, TRUE);

	if (!startGLEW())
	{
		showMessageBox("FAILED", "GLEW START FAILED");
		destroyWindow();
		return 0;
	}

	initOpenGL();

	loadCursor();

	loadGame();

	runWnd = true;
	MSG msg;
	while (runWnd)
	{
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			drawLib(hDC, drawGame);
			SwapBuffers(hDC);
		}
	}
	freeLib();
	freeCursor();

	destroyWindow();

	return 0;
}

#include "../res/resource.h"
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool createWindow(int width, int height, int bits, bool fullscreen)
{
	hInstance = GetModuleHandle(NULL);
	windowClassName = TEXT("WORN");

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	//wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_APPICON),IMAGE_ICON,0,0,LR_DEFAULTSIZE|LR_DEFAULTCOLOR|LR_SHARED);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = windowClassName;
	if (!RegisterClass(&wc))
	{
		showMessageBox("FAILED", "Register WNDCLASS");
		destroyWindow();
		return false;
	}

	DWORD dwExStyle;
	DWORD dwStyle;
	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	RECT rect;
	rect.left = 0;
	rect.right = width;
	rect.top = 0;
	rect.bottom = height;
	AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);

	hWnd = CreateWindowEx(dwExStyle, windowClassName, windowClassName,
			dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL, hInstance,
			NULL);
	if (!hWnd)
	{
		showMessageBox("FAILED", "CreateWindowEx");
		destroyWindow();
		return false;
	}
	hDC = GetDC(hWnd);
	if (!setupOpenGL(true, hDC))
	{
		destroyWindow();
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	return true;
}

void destroyWindow()
{
	if (isFullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	setupOpenGL(false, hDC);

	if (hDC)
		ReleaseDC(hWnd, hDC);
	if (hWnd)
		DestroyWindow(hWnd);
	UnregisterClass(windowClassName, hInstance);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	///////////////////////////////////////////////////////////////
	// WINDOW MESSAGE
	///////////////////////////////////////////////////////////////
	case WM_CREATE:
		break;
	case WM_DESTROY:
		break;
	case WM_CLOSE:
	{

		//showPopExit(true);
		runWnd = false;
		return 0;
	}

		///////////////////////////////////////////////////////////////
		// WINDOW RESIZE
		///////////////////////////////////////////////////////////////
	case WM_SIZING:
		resizeWindow(LOWORD(lParam), HIWORD(lParam));
		reshapeOpenGL();

		break;

	case WM_SIZE:
		resizeWindow(LOWORD(lParam), HIWORD(lParam));
		reshapeOpenGL();

		break;

		///////////////////////////////////////////////////////////////
		// MOUSE POINT
		///////////////////////////////////////////////////////////////
	case WM_LBUTTONDOWN:
	{
		cursor = converCoordinate(LOWORD(lParam), HIWORD(lParam));
		keyGame(iKeyStateBegan, cursor);

		mouseBegan = true;
		break;
	}
	case WM_MOUSEMOVE:
	{
		cursor = converCoordinate(LOWORD(lParam), HIWORD(lParam));

#if (__os__==os_window || __os__==os_mac || __os__==os_linux)
		keyGame(iKeyStateMoved, cursor);
#endif

		break;
	}
	case WM_LBUTTONUP:
	{
		cursor = converCoordinate(LOWORD(lParam), HIWORD(lParam));
		keyGame(iKeyStateEnded, cursor);

		mouseBegan = false;
		break;
	}
	case WM_SETCURSOR:
	{
		if (updateCursor(LOWORD(lParam) == HTCLIENT))
			return 0;
		break;
	}

	case WM_KEYDOWN:
		keyLib(iKeyStateBegan, wParam);
		break;
	case WM_KEYUP:
		keyLib(iKeyStateEnded, wParam);
		break;

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

wchar_t* utf8_to_utf16(const char* str)
{
	int length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wchar_t* s = (wchar_t*) malloc(sizeof(wchar_t) * length);
	MultiByteToWideChar(CP_UTF8, 0, str, strlen(str) + 1, s, length);
	return s;
}

void showMessageBox(const char* title, const char* msg)
{
	wchar_t* wTitle = utf8_to_utf16(title);
	wchar_t* wMsg = utf8_to_utf16(msg);
	MessageBox(NULL, wMsg, wTitle, MB_OK);
	free(wTitle);
	free(wMsg);
}

HGLRC hRC = NULL;
bool setupOpenGL(bool setup, HDC hDC)
{
	if (setup)
	{
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0x00, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int pixelformat = ChoosePixelFormat(hDC, &pfd);
		if (!pixelformat)
			return false;
		if (!SetPixelFormat(hDC, pixelformat, &pfd))
			return false;

		hRC = wglCreateContext(hDC);
		if (!hRC)
			return false;
		if (!wglMakeCurrent(hDC, hRC))
			return false;
	}
	else
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRC);
	}

	return true;
}

bool startGLEW()
{
	glewExperimental = TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
		return false;

	return true;
}

