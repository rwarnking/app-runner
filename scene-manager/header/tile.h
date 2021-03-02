///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: tile.h
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


//////////////
// INCLUDES //
//////////////
#include <vector>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
//#include "graphics/model.h"
//#include "ecs/manager.h"
//#include "io/loader.h"
#include "game_object.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
// Class name: Tile
///////////////////////////////////////////////////////////////////////////////////////////////////
class Tile
{

public:
	Tile() = default;
	Tile(const Tile& other) = delete;
	Tile(Tile &&other) noexcept;
	auto operator=(const Tile& other) -> Tile = delete;
	auto operator=(Tile&& other) -> Tile& = default;
	~Tile() = default;

	auto AddObject() -> GameObject&;

	[[nodiscard]] auto GetObjects() const -> const std::vector<GameObject>&;
	auto GetObject(size_t object_idx) -> GameObject&;

	static const int WIDTH_X{ 1000 };
	static const int LENGHT_Z{ 1000 };
	
private:
	int m_terrain_idx{ -1 };
	std::vector<GameObject> m_objects;

};
