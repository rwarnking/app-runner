///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: user.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\header\user.h"


//////////////
// INCLUDES //
//////////////
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////


User::User(float x, float y, float z) :
	m_pos(x, y, z),
	m_cam_pos(x, y, z),
	m_cam_look_dir(0.0F, 0.0F, 1.0F)
{
}


auto User::GetPos() const -> const glm::vec3&
{
	return m_pos;
}


auto User::GetCamPos() const -> const glm::vec3&
{
	return m_cam_pos;
}


auto User::GetCamLookDir() const -> const glm::vec3&
{
	return m_cam_look_dir;
}


void User::TurnLeft(float frametime, float angle)
{
	auto scale = (frametime / FT_60_FRAMES);
	auto up = glm::vec3(0.0F, 1.0F, 0.0F);
	m_cam_look_dir = glm::rotate(m_cam_look_dir, -angle * scale, up);
}


void User::TurnRight(float frametime, float angle)
{
	auto scale = (frametime / FT_60_FRAMES);
	auto up = glm::vec3(0.0F, 1.0F, 0.0F);
	m_cam_look_dir = glm::rotate(m_cam_look_dir, angle * scale, up);
}


void User::TurnUp(float frametime, float angle)
{
	auto scale = (frametime / FT_60_FRAMES);
	auto up = glm::vec3(0.0F, 1.0F, 0.0F);
	auto right = glm::cross(up, m_cam_look_dir);
	m_cam_look_dir = glm::rotate(m_cam_look_dir, angle * scale, right);
}


void User::TurnDown(float frametime, float angle)
{
	auto scale = (frametime / FT_60_FRAMES);
	auto up = glm::vec3(0.0F, 1.0F, 0.0F);
	auto right = glm::cross(up, m_cam_look_dir);
	m_cam_look_dir = glm::rotate(m_cam_look_dir, -angle * scale, right);
}


void User::MoveLeft(float frametime, float speed)
{
	auto up = glm::vec3(0.0F, 1.0F, 0.0F);
	auto right = glm::cross(up, m_cam_look_dir);

	auto scale = (frametime / FT_60_FRAMES) * speed;
	m_cam_pos -= right * scale;
	if (m_cam_mode != Cam_mode::FREE) {
		m_pos -= right * scale;
	}
}


void User::MoveRight(float frametime, float speed)
{
	auto up = glm::vec3(0.0F, 1.0F, 0.0F);
	auto right = glm::cross(up, m_cam_look_dir);
	
	auto scale = (frametime / FT_60_FRAMES) * speed;
	m_cam_pos += right * scale;
	if (m_cam_mode != Cam_mode::FREE) {
		m_pos += right * scale;
	}
}


void User::MoveUp(float frametime, float speed)
{
	auto up = glm::vec3(0.0F, 1.0F, 0.0F);
	auto right = glm::cross(up, m_cam_look_dir);
	up = glm::cross(m_cam_look_dir, right);
	
	auto scale = (frametime / FT_60_FRAMES) * speed;
	m_cam_pos += up * scale;
	if (m_cam_mode != Cam_mode::FREE) {
		m_pos += up * scale;
	}
}


void User::MoveDown(float frametime, float speed)
{
	auto up = glm::vec3(0.0F, 1.0F, 0.0F);
	auto right = glm::cross(up, m_cam_look_dir);
	up = glm::cross(m_cam_look_dir, right);

	auto scale = (frametime / FT_60_FRAMES) * speed;
	m_cam_pos -= up * scale;
	if (m_cam_mode != Cam_mode::FREE) {
		m_pos -= up * scale;
	}
}


void User::MoveForward(float frametime, float speed)
{
	auto scale = (frametime / FT_60_FRAMES) * speed;
	m_cam_pos += m_cam_look_dir * scale;
	if (m_cam_mode != Cam_mode::FREE) {
		m_pos += m_cam_look_dir * scale;
	}
}


void User::MoveBackward(float frametime, float speed)
{
	auto scale = (frametime / FT_60_FRAMES) * speed;
	m_cam_pos -= m_cam_look_dir * scale;
	if (m_cam_mode != Cam_mode::FREE) {
		m_pos -= m_cam_look_dir * scale;
	}
}
