#include "IGameObject.h"

namespace Physics
{
	class PhysicsEngine;
	class AABB;
}

IGameObject::IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: m_position(position), m_size(size), m_rotation(rotation), m_layer(layer), m_direction(0, 1.f), m_velocity(0.f)
{
}

IGameObject::~IGameObject(){}

glm::vec2& IGameObject::getCurrentPosition()
{
	return m_position;
}
glm::vec2& IGameObject::getCurrentDirection()
{
	return m_direction;
}
double IGameObject::getCurrentVelocity()
{
	return m_velocity;
}
void IGameObject::setVelocity(const double velocity)
{
	m_velocity = velocity;
}

const std::vector<Physics::AABB>& IGameObject::getColliders() const
{
	return m_colliders;
}

const glm::vec2& IGameObject::getSIze() const
{
	return m_size;
}