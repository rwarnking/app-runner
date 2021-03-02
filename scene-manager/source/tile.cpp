///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: tile.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\header\tile.h"


//////////////
// INCLUDES //
//////////////


///////////////////////
// MY CLASS INCLUDES //
///////////////////////


Tile::Tile(Tile&& other) noexcept :
	m_terrain_idx(other.m_terrain_idx),
	m_objects(std::move(other.m_objects))
{
}


// https://stackoverflow.com/questions/2275076/is-stdvector-copying-the-objects-with-a-push-back
// https://stackoverflow.com/questions/23948442/emplace-back-does-not-behave-as-expected/23948499#23948499
// https://stackoverflow.com/questions/26740523/vector-push-back-calling-copy-constructor-more-than-once
auto Tile::AddObject() -> GameObject&
{
	m_objects.emplace_back();
	return m_objects.back();
}


auto Tile::GetObjects() const -> const std::vector<GameObject>&
{
	return m_objects;
}


auto Tile::GetObject(size_t object_idx) -> GameObject&
{
	return m_objects[object_idx];
}
