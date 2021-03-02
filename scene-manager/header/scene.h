///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: scene.h
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
#include <map>
#include <tuple>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "tile.h"
#include "user.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
// Class name: Scene
/// The scene class manages all components of a renderable scene, including entities and cameras.
///////////////////////////////////////////////////////////////////////////////////////////////////
class Scene
{

public:
	Scene() = default;
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) noexcept;
	auto operator=(const Scene& other) -> Scene = delete;
	auto operator=(Scene&& other) -> Scene & = default;
	~Scene() = default;

	auto AddObject(const std::tuple<int, int>& tile_idx = std::make_tuple(0, 0)) -> GameObject&;
	auto AddObjectFromPos(glm::vec3 pos) -> GameObject&;
	auto AddObjectFromCoords(const float x, const float y, const float z) -> GameObject&;

	[[nodiscard]] SCENE_MANAGER_API auto GetObjects(
		const std::tuple<int, int>& tile_idx
	) const -> const std::vector<GameObject>&;

	auto GetObject(const std::tuple<int, int>& tile_idx, size_t object_idx) -> GameObject&;

	void AddUser(float x, float y, float z);

	SCENE_MANAGER_API auto GetUser(size_t idx) -> User&;
	[[nodiscard]] SCENE_MANAGER_API auto GetUser(size_t idx) const -> const User&;

	[[nodiscard]] SCENE_MANAGER_API auto GetTiles() const -> const std::map<std::tuple<int, int>, Tile>&;

private:
	std::map<std::tuple<int, int>, Tile> m_tiles;
	std::vector<User> m_users;

};
