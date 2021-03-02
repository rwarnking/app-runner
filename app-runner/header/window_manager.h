///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: window_manager.h
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN


//////////////
// INCLUDES //
//////////////
#include <string>
#include <windows.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "header/logic_less_is_more.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
// Class name: WindowManager
/// This class manages the app loop, renderer and scenes. 
/// It also initializes the application's window and stores a handle to it.
///////////////////////////////////////////////////////////////////////////////////////////////////
class WindowManager
{

public: 
	WindowManager();
	explicit WindowManager(const std::wstring& app_titel);
	WindowManager(const WindowManager& other) = delete;
	WindowManager(WindowManager&& other) noexcept = delete;
	auto operator=(const WindowManager& other) -> WindowManager = delete;
	auto operator=(WindowManager&& other) -> WindowManager & = default;
	~WindowManager() = default;

	auto CreateNewWindow(
		logic::Logic* logic, int window_width, int window_height, BOOL fullscreen
	) -> bool;
	auto GetWindow() -> const HWND&;
	auto ChangeWindow(int window_width, int window_height, BOOL fullscreen) -> bool;

private:
	HWND m_hwnd;
	HINSTANCE m_hinstance;
	std::wstring m_applicationName;

};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
/**
 * This function is called by Windows for window messages, the name if which was passed
 * to the settings in \c InitializeWindows
 * @param hwnd
 * @param umessage
 * @param wparam
 * @param lparam
 */
static auto CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) -> LRESULT; // NOLINT
