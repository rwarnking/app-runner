///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: scene_manager.h
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef SCENEMANAGER_EXPORTS
#define SCENE_MANAGER_API __declspec(dllexport)
#else
#define SCENE_MANAGER_API __declspec(dllimport)
#endif

//////////////
// INCLUDES //
//////////////
#include <memory>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "scene.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
// Class name: SceneManager
///////////////////////////////////////////////////////////////////////////////////////////////////
class SceneManager
{

public:
	SceneManager() = default;
	SceneManager(const SceneManager& other) = delete;
	// used from the createSceneManager function
	SceneManager(SceneManager&& other) = default; 
	auto operator=(const SceneManager& other) -> SceneManager = delete;
	auto operator=(SceneManager&& other) -> SceneManager& = default;
	SCENE_MANAGER_API ~SceneManager() = default;

	///////////
	// Scene //
	///////////
	SCENE_MANAGER_API auto AddScene() -> size_t;
	SCENE_MANAGER_API void SetActiveScene(size_t scene_idx);
	SCENE_MANAGER_API auto GetActiveScene() -> Scene&;
	[[nodiscard]] SCENE_MANAGER_API auto GetActiveScene() const -> const Scene&;
	
	//////////
	// User //
	//////////
	SCENE_MANAGER_API void AddUser(float x, float y, float z, size_t scene_idx);

	/////////////
	// Objects //
	/////////////
	SCENE_MANAGER_API auto AddObject(size_t scene_idx) -> GameObject&;
	SCENE_MANAGER_API auto AddObjectToActive() -> GameObject&;
	SCENE_MANAGER_API auto AddObjectToActive(glm::vec3 pos) -> GameObject&;
	SCENE_MANAGER_API auto AddObjectToActive(float x, float , float z) -> GameObject&;
	
	///////////////////////////////////////////////////////////////////////////////////////////////
private:
	std::vector<Scene> m_scenes;
	size_t m_active_scene{ 0 };

};

extern SCENE_MANAGER_API auto createSceneManager() -> std::unique_ptr<SceneManager>;