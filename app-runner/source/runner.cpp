///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: runner.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "../header/runner.h"


//////////////
// INCLUDES //
//////////////
#include <fstream>
#include <vector>

#include <sstream>
#include <iomanip>
///////////////////////
// MY CLASS INCLUDES //
///////////////////////


#define ERROR_FILE_OPEN                    _HRESULT_TYPEDEF_(0xA0000001L)
#define ERROR_REZISE                       _HRESULT_TYPEDEF_(0xA0000002L)
#define SETTINGS                           _HRESULT_TYPEDEF_(0xA0010000L)
#define SAVEGAME                           _HRESULT_TYPEDEF_(0xA0020000L)
#define WINDOWMGR                          _HRESULT_TYPEDEF_(0xA0030000L)


auto Runner::Init() -> bool
{
	m_timer = std::make_unique<Timer>();
	m_timer->Initialize();


	m_logic = logic::createLogic();
	if (!m_logic->InitSettings()) {
		PrintError(ERROR_FILE_OPEN | SETTINGS);
		return false;
	}


	m_window_mgr = std::make_unique<WindowManager>(m_logic->GetAppName());


	const auto& g_sett = m_logic->GetGraphicSettings();
	if (!m_window_mgr->CreateNewWindow(
			m_logic.get(),
			int(g_sett.window_width), int(g_sett.window_height), g_sett.fullscreen
		)
	) {
		PrintError(WINDOWMGR | ERROR_REZISE);
		return false;
	}


	m_scene_mgr = createSceneManager();


	m_engine = graphics::createEngine();
	auto& hwnd = m_window_mgr->GetWindow();
	auto result = m_engine->RendererInit(hwnd, g_sett);
	if (FAILED(result)) {
		PrintError(m_window_mgr->GetWindow(), result);
		return false;
	}


	if (!m_logic->InitMenuScene(*m_scene_mgr, *m_engine)) {
		PrintError(m_window_mgr->GetWindow(), ERROR_FILE_OPEN | SAVEGAME);
		return false;
	}

	return true;
}


void Runner::Shutdown()
{
	m_engine->Shutdown();
}


void Runner::Run()
{
	MSG msg;
	auto result{ S_OK };

	// TODO(rwarnking) remove this
	std::vector<int> frames;

	while (!m_logic->CloseApp())
	{
		// http://www.directxtutorial.com/Lesson.aspx?lessonid=9-1-4
		// Check to see if any messages are waiting in the queue
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			// Translate the message and dispatch it to WindowProc()
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		m_timer->Frame();

		//////////////////
		// Logic Update //
		//////////////////
		constexpr int MS_PER_S = 1000;
		frames.push_back(int(MS_PER_S / m_timer->GetTime()));
		if (!m_logic->Update(*m_scene_mgr, *m_engine, m_timer->GetTime())) {
			PrintError(m_window_mgr->GetWindow(), ERROR_FILE_OPEN | SAVEGAME);
			return;
		}

		///////////////////
		// Window Update //
		///////////////////
		if (m_logic->WindowChanged()) {
			const auto& g_sett = m_logic->GetGraphicSettings();
			result = m_engine->Refresh(g_sett);
			if (FAILED(result))
			{
				PrintError(m_window_mgr->GetWindow(), result);
				return;
			}

			if (!m_window_mgr->ChangeWindow(
					int(g_sett.window_width), int(g_sett.window_height), g_sett.fullscreen
				)
			) {
				PrintError(m_window_mgr->GetWindow(), ERROR_REZISE | WINDOWMGR);
				return;
			}
		}

		///////////////
		// Rendering //
		///////////////
		result = m_engine->RenderScene(m_scene_mgr->GetActiveScene());
		if (FAILED(result))
		{
			PrintError(m_window_mgr->GetWindow(), result);
			return;
		}
	}
	
	std::ofstream fout;

	// Open the file to write to
	fout.open("frames.txt");
	for (auto f : frames) {
		fout << f << "\n";
	}
	fout.close();

	const auto& hwnd = m_window_mgr->GetWindow();
	MessageBox(hwnd, L"Closing project", L"Error", MB_OK);
}


void Runner::PrintError(HRESULT error)
{
	throw("Error at startup" + error);
}


void Runner::PrintError(HWND hwnd, HRESULT error)
{
	std::wstring error_str{};
	switch (error)
	{
		case ERROR_FILE_OPEN | SAVEGAME:
			error_str = std::wstring(L"Error while opening savegame.");
			break;
		case ERROR_FILE_OPEN | SETTINGS:
			error_str = std::wstring(L"Error while opening settings.");
			break;		
		case ERROR_REZISE | WINDOWMGR:
			error_str = std::wstring(L"Error while resizeing window.");
			break;
		case E_INVALIDARG:
			error_str = std::wstring(L"Engine: An invalid parameter was passed to the returning function. HRESULT: ");
			break;
		default:
			error_str = std::wstring(L"An Error occurred. HRESULT: ");
			break;
	}

#ifdef UNICODE
	typedef std::wostringstream tstringstream;
#else
	typedef std::ostringstream tstringstream;
#endif
	tstringstream stros;
	stros << error_str << L"0x" << std::uppercase << std::setfill(L'0') << std::setw(4) << std::hex << error;

	MessageBox(hwnd, stros.str().c_str(), L"Error", MB_OK);
}