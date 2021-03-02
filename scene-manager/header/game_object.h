///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: game_object.h
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


//////////////
// INCLUDES //
//////////////
#include <glm/vec3.hpp>
#include <string>
#include <tuple>
#include <vector>


#ifdef SCENEMANAGER_EXPORTS
#define SCENE_MANAGER_API __declspec(dllexport)
#else
#define SCENE_MANAGER_API __declspec(dllimport)
#endif

///////////////////////
// MY CLASS INCLUDES //
///////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// Class name: GameObject
///////////////////////////////////////////////////////////////////////////////////////////////////
class GameObject
{
public:

	GameObject() = default;
	GameObject(const GameObject &other) = delete;
	GameObject(GameObject&& other) noexcept;
	//GameObject(const GameObject&& other) = default;
	auto operator=(const GameObject &other) -> GameObject = delete;
	auto operator=(GameObject&& other) -> GameObject& = default;
	~GameObject() = default;

	SCENE_MANAGER_API void SetModelIdx(size_t idx);
	[[nodiscard]] SCENE_MANAGER_API auto GetModelIdx() const -> size_t;

	SCENE_MANAGER_API void SetTextureIdx(size_t idx);
	[[nodiscard]] SCENE_MANAGER_API auto GetTextureIdx() const -> size_t;

	SCENE_MANAGER_API void SetPosition(float x, float y, float z);
	[[nodiscard]] SCENE_MANAGER_API auto GetPosition() const -> glm::vec3;

private:
	// TODO(rwarnking) use a type of componentsystem to store these elements
	// This would allow for a modular buildup of gameobjects
	size_t m_model_idx{ 0 };
	size_t m_texture_idx{ 0 };
	glm::vec3 m_pos{ 0, 0, 0 };
};
