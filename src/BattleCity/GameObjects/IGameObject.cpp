#include "IGameObject.h"
#include "../../Physics/PhysicsEngine.h"

IGameObject::IGameObject(const EObjectType objectType, const glm::vec2 &position, const glm::vec2 &size, const float rotation, const float layer)
	: m_pOwner(nullptr), m_position(position), m_targetPosition(position), m_size(size)
	, m_rotation(rotation), m_layer(layer), m_objectType(objectType), m_direction(0, 1.f), m_velocity(0.f)
{
}

IGameObject::~IGameObject(){}

void IGameObject::setOwner(IGameObject* pOwner)
{
	m_pOwner = pOwner;
}

IGameObject* IGameObject::getOwner() const
{
	return m_pOwner;
}

glm::vec2& IGameObject::getCurrentPosition()
{
	return m_position;
}
glm::vec2& IGameObject::getCurrentDirection()
{
	return m_direction;
}
glm::vec2& IGameObject::getTargetPosition()
{
	return m_targetPosition;
}
double IGameObject::getCurrentVelocity()
{
	return m_velocity;
}
void IGameObject::setVelocity(const double velocity)
{
	m_velocity = velocity;
}

const std::vector<Physics::Collider>& IGameObject::getColliders() const
{
	return m_colliders;
}

const glm::vec2& IGameObject::getSIze() const
{
	return m_size;
}

IGameObject::EObjectType IGameObject::getObjectType() const
{
	return m_objectType;
}
bool IGameObject::collides(const EObjectType objectType)
{
	return true;
}