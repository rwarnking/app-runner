///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: scene.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\header\scene.h"


//////////////
// INCLUDES //
//////////////


///////////////////////
// MY CLASS INCLUDES //
///////////////////////


Scene::Scene(Scene&& other) noexcept :
	m_tiles(std::move(other.m_tiles)),
	m_users(std::move(other.m_users))
{
}


auto Scene::AddObject(const std::tuple<int, int>& tile_idx) -> GameObject&
{
	auto res = m_tiles.insert({ tile_idx, Tile() }).first;
	return res->second.AddObject();
}



auto Scene::AddObjectFromPos(const glm::vec3 pos) -> GameObject&
{
	int x = int(pos.x) / Tile::WIDTH_X;
	int z = int(pos.z) / Tile::LENGHT_Z;
	auto tile_idx = std::make_tuple(x, z);
	auto res = m_tiles.insert({ tile_idx, Tile() }).first;
	return res->second.AddObject();
}


auto Scene::AddObjectFromCoords(const float x, const float y, const float z) -> GameObject&
{
	return AddObjectFromPos(glm::vec3(x, y, z));
}


auto Scene::GetObjects(const std::tuple<int, int>& tile_idx) const -> const std::vector<GameObject>&
{
	auto res = m_tiles.find(tile_idx);
	assert(res != m_tiles.end() && "Did you forget to add this tile?");
	return res->second.GetObjects();
}


auto Scene::GetObject(const std::tuple<int, int>& tile_idx, size_t object_idx) -> GameObject&
{
	return m_tiles.find(tile_idx)->second.GetObject(object_idx);
}


void Scene::AddUser(float x, float y, float z)
{
	m_users.emplace_back(x, y, z);
}


auto Scene::GetUser(size_t idx) -> User&
{
	return m_users[idx];
}


auto Scene::GetUser(size_t idx) const -> const User&
{
	return m_users[idx];
}


auto Scene::GetTiles() const -> const std::map<std::tuple<int, int>, Tile>&
{
	return m_tiles;
}
