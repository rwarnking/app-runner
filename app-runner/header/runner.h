///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: runner.h
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <memory>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "header/scene_manager.h"						// NOLINT
#include "header/ubrotengine_dx11.h"					// NOLINT
#include "header/logic_less_is_more.h"					// NOLINT
#include "timer.h"
#include "window_manager.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
// Class name: Runner
///////////////////////////////////////////////////////////////////////////////////////////////////
class Runner
{

public:
	Runner() = default;
	Runner(const Runner& other) = delete;
	Runner(Runner&& other) noexcept = delete;
	auto operator=(const Runner& other)->Runner = delete;
	auto operator=(Runner&& other)->Runner & = default;
	~Runner() = default;

	auto Init() -> bool;
	void Shutdown();
	void Run();

private:
	void PrintError(HRESULT error);
	void PrintError(HWND hwnd, HRESULT error);

	std::unique_ptr<Timer> m_timer;
	std::unique_ptr<WindowManager> m_window_mgr;
	std::unique_ptr<SceneManager> m_scene_mgr;
	std::unique_ptr<logic::Logic> m_logic;
	std::unique_ptr<graphics::Engine> m_engine;

};
