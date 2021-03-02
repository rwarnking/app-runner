///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: window_manager.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "../header/window_manager.h"


//////////////
// INCLUDES //
//////////////
#include <windowsx.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "header/logic_less_is_more.h"


WindowManager::WindowManager() :
	m_hwnd(nullptr),
	m_hinstance(nullptr),
	m_applicationName(L"Application Name")
{
}


WindowManager::WindowManager(const std::wstring& app_titel) : 
	m_hwnd(nullptr),
	m_hinstance(nullptr),
	m_applicationName(app_titel)
{
}


auto WindowManager::CreateNewWindow(
	logic::Logic* logic,
	int window_width, int window_height, const BOOL fullscreen
) -> bool
{
	auto result{ true };


	// Create a reference to this instance
	m_hinstance = GetModuleHandle(nullptr);

	WNDCLASSEX wc;
	// Define default values for the window settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);						// NOLINT
	wc.hIconSm = wc.hIcon; 
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);					// NOLINT
	wc.hbrBackground = HBRUSH(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_applicationName.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);

	// Reserve space to store the instance pointer
	wc.cbWndExtra = sizeof(logic::Logic*);

	RegisterClassEx(&wc);

	int pos_x{ 0 };
	int pos_y{ 0 };

	// Determine the size of the window. In fullscreen mode, the maximum size is chosen and
	// the winow is placed in the upper left corner of the screen. Otherwise, a predefined
	// size is chosen and the window is centred on the screen.
	// https://gamedev.stackexchange.com/questions/46172/go-to-fullscreen-and-back-in-directx
	if (fullscreen == TRUE)
	{
		window_width = GetSystemMetrics(SM_CXSCREEN);
		window_height = GetSystemMetrics(SM_CYSCREEN);

		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = DWORD(window_width);
		dmScreenSettings.dmPelsHeight = DWORD(window_height);
		constexpr DWORD dmBitsPerPel{ 32UL };
		dmScreenSettings.dmBitsPerPel = dmBitsPerPel;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		result = (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL);
	}
	else
	{
		pos_x = (GetSystemMetrics(SM_CXSCREEN) - window_width) / 2;
		pos_y = (GetSystemMetrics(SM_CYSCREEN) - window_height) / 2;
	}


	// Create the window and store a handle to it
	m_hwnd = CreateWindowEx(
		WS_EX_APPWINDOW, m_applicationName.c_str(), m_applicationName.c_str(),
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		pos_x, pos_y, window_width, window_height, nullptr, nullptr, m_hinstance, nullptr
	);

	// Bring the window up on the screen and set it as the main focus.
	// Return types can be ignored since these only indicate if something was changed
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// https://stackoverflow.com/questions/18161680/
	// Store instance pointer
	SetWindowLongPtrW(m_hwnd, 0, reinterpret_cast<LONG_PTR>(logic));

	const int cursor_pos_x = pos_x + window_width / 2;
	const int cursor_pos_y = pos_y + window_height / 2;
	result &= SetCursorPos(cursor_pos_x, cursor_pos_y) == TRUE;
	ShowCursor(FALSE);

	// Raw input (WM_INPUT) setup
	// https://docs.microsoft.com/en-us/windows/win32/inputdev/using-raw-input
	constexpr USHORT HID_USAGE_PAGE_GENERIC = 0x01;
	constexpr USHORT HID_USAGE_GENERIC_MOUSE = 0x02;
	constexpr USHORT HID_USAGE_GENERIC_KEYBOARD = 0x06;

	std::array<RAWINPUTDEVICE, 2> Rid{};
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	Rid[0].dwFlags = RIDEV_INPUTSINK;
	Rid[0].hwndTarget = m_hwnd;

	Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;
	Rid[1].dwFlags = RIDEV_INPUTSINK;    // adds keyboard and also ignores legacy keyboard messages
	Rid[1].hwndTarget = m_hwnd;

	result &= RegisterRawInputDevices(Rid.data(), 2, sizeof(Rid[0])) == TRUE;

	return result;
}


auto WindowManager::GetWindow() -> const HWND&
{
	return m_hwnd;
}


auto WindowManager::ChangeWindow(
	int window_width, int window_height, const BOOL fullscreen
) -> bool
{
	auto result{ true };

	int pos_x{ 0 };
	int pos_y{ 0 };

	if (fullscreen == FALSE) {
		pos_x = (GetSystemMetrics(SM_CXSCREEN) - window_width) / 2;
		pos_y = (GetSystemMetrics(SM_CYSCREEN) - window_height) / 2;

		result &= SetWindowPos(m_hwnd, nullptr, pos_x, pos_y, window_width, window_height, SWP_NOZORDER) == TRUE;
		result &= UpdateWindow(m_hwnd) == TRUE;
	}

	return result;
}


auto CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) -> LRESULT
{
	switch (umessage) {
		// http://www.cplusplus.com/forum/beginner/11226/
		// https://docs.microsoft.com/de-de/windows/win32/inputdev/raw-input?redirectedfrom=MSDN
		//case WM_MOUSEMOVE:
		//{
		//}
		case WM_INPUT:
		{
			UINT dwSize{ 0 };
			GetRawInputData(HRAWINPUT(lparam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));

			std::vector<BYTE> lpb(dwSize);
			GetRawInputData(HRAWINPUT(lparam), RID_INPUT, lpb.data(), &dwSize, sizeof(RAWINPUTHEADER));

			auto *raw = reinterpret_cast<RAWINPUT*>(lpb.data());

			if (raw->header.dwType == RIM_TYPEMOUSE) {
				if ((raw->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE) == MOUSE_MOVE_ABSOLUTE) {
					// TODO(rwarnking)
					return 0;
				}
				LONG xPosRelative = raw->data.mouse.lLastX;
				LONG yPosRelative = raw->data.mouse.lLastY;
				auto *logic = reinterpret_cast<logic::Logic*>(GetWindowLongPtrW(hwnd, 0));
				logic->MouseMove(xPosRelative, yPosRelative);
			} 
			// Keyboard events
			else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
				if (raw->data.keyboard.Flags == RI_KEY_MAKE) {
					auto* logic = reinterpret_cast<logic::Logic*>(GetWindowLongPtrW(hwnd, 0));
					logic->KeyReleased(raw->data.keyboard.VKey);
				}
			}
			return 0;
		} 
		/*
		case WM_LBUTTONDOWN:   wmLButtonDown(   hwnd, wp, lp );  break;
		case WM_LBUTTONUP:     wmLButtonUp(     hwnd, wp, lp );  break;
		case WM_LBUTTONDBLCLK: wmLButtonDblClk( hwnd, wp, lp );  break;
		*/
		// Check if the window is being destroyed.
		case WM_DESTROY:
		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		// Pass all other messages to the message handler.
		default:
		{
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
	}
}
