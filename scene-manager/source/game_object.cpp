///////////////////////////////////////////////////////////////////////////////////////////////////
// Filename: game_object.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\header\game_object.h"


GameObject::GameObject(GameObject &&other) noexcept: 
	m_model_idx(other.m_model_idx),
	m_texture_idx(other.m_texture_idx),
	m_pos(other.m_pos)
{
}


void GameObject::SetModelIdx(size_t idx)
{
	m_model_idx = idx;
}


auto GameObject::GetModelIdx() const -> size_t
{
	return m_model_idx;
}


void GameObject::SetTextureIdx(size_t idx)
{
	m_texture_idx = idx;
}


auto GameObject::GetTextureIdx() const -> size_t
{
	return m_texture_idx;
}


void GameObject::SetPosition(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}


auto GameObject::GetPosition() const -> glm::vec3
{
	return m_pos;
}
