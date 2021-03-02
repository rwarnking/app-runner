///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: user.h
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
#include <array>
#include <glm/vec3.hpp>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////


///////////////
// CONSTANTS //
///////////////
constexpr float FT_60_FRAMES = 16.0F;
constexpr float TURN_ANGLE = 0.1F;
constexpr float MOVE_SPEED = 0.1F;


///////////////////////////////////////////////////////////////////////////////////////////////////
// Class name: User
///////////////////////////////////////////////////////////////////////////////////////////////////
class User
{

public:
	User() = default;
	User(float x, float y, float z);
	User(const User& other) = delete;
	User(User &&other) = default;
	auto operator=(const User& other) -> User = delete;
	auto operator=(User&& other) -> User& = default;
	~User() = default;

	[[nodiscard]] SCENE_MANAGER_API auto GetPos() const -> const glm::vec3&;
	[[nodiscard]] SCENE_MANAGER_API auto GetCamPos() const -> const glm::vec3&;
	[[nodiscard]] SCENE_MANAGER_API auto GetCamLookDir() const -> const glm::vec3&;

	SCENE_MANAGER_API void TurnLeft(float frametime, float angle = TURN_ANGLE);
	SCENE_MANAGER_API void TurnRight(float frametime, float angle = TURN_ANGLE);
	SCENE_MANAGER_API void TurnUp(float frametime, float angle = TURN_ANGLE);
	SCENE_MANAGER_API void TurnDown(float frametime, float angle = TURN_ANGLE);

	SCENE_MANAGER_API void MoveUp(float frametime, float speed = MOVE_SPEED);
	SCENE_MANAGER_API void MoveDown(float frametime, float speed = MOVE_SPEED);
	SCENE_MANAGER_API void MoveLeft(float frametime, float speed = MOVE_SPEED);
	SCENE_MANAGER_API void MoveRight(float frametime, float speed = MOVE_SPEED);
	SCENE_MANAGER_API void MoveForward(float frametime, float speed = MOVE_SPEED);
	SCENE_MANAGER_API void MoveBackward(float frametime, float speed = MOVE_SPEED);

private:
	enum class Cam_mode
	{
		FIRST_PERSON = 0,
		THIRD_PERSON = 1,
		FREE = 2
	};

	glm::vec3 m_pos{ 0.0F, 0.0F, 0.0F };
	glm::vec3 m_cam_pos{ 0.0F, 0.0F, 0.0F };
	glm::vec3 m_cam_look_dir{ 0.0F, 0.0F, 1.0F };
	Cam_mode m_cam_mode{ Cam_mode::FREE };

};