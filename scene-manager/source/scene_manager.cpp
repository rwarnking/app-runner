///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: scene_manager.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "../header/scene_manager.h"


//////////////
// INCLUDES //
//////////////


///////////////////////
// MY CLASS INCLUDES //
///////////////////////


SCENE_MANAGER_API auto createSceneManager() -> std::unique_ptr<SceneManager>
{
	return std::make_unique<SceneManager>(SceneManager());
}


auto SceneManager::AddScene() -> size_t
{
	m_scenes.emplace_back();
	return m_scenes.size() - 1;
}


void SceneManager::SetActiveScene(size_t scene_idx)
{
	assert(scene_idx < m_scenes.size() && "Did you forget to add the scene?");
	m_active_scene = scene_idx;
}


// Since the function for setting m_active_scene asserts that the 
// idx is never bigger then the array we dont need additional tests here.
auto SceneManager::GetActiveScene() -> Scene&
{
	return m_scenes.at(m_active_scene);
}


auto SceneManager::GetActiveScene() const -> const Scene&
{
	return m_scenes.at(m_active_scene);
}


auto SceneManager::AddObject(const size_t scene_idx) -> GameObject&
{
	assert(scene_idx < m_scenes.size() && "Did you forget to add this scene?");
	return m_scenes.at(scene_idx).AddObject();
}


auto SceneManager::AddObjectToActive() -> GameObject&
{
	return m_scenes.at(m_active_scene).AddObject();
}


auto SceneManager::AddObjectToActive(glm::vec3 pos) -> GameObject&
{
	return m_scenes.at(m_active_scene).AddObjectFromPos(pos);
}


auto SceneManager::AddObjectToActive(float x, float y, float z) -> GameObject&
{
	return m_scenes.at(m_active_scene).AddObjectFromCoords(x, y, z);
}


void SceneManager::AddUser(float x, float y, float z, const size_t scene_idx)
{
	assert(scene_idx < m_scenes.size() && "Did you forget to add this scene?");
	m_scenes.at(scene_idx).AddUser(x, y, z);
}
