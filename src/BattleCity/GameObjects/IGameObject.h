#pragma once

#include <glm/vec2.hpp>

#include "../../Physics/PhysicsEngine.h"

class IGameObject
{
public:
	enum class EObjectType
	{
		BetonWall,
		Border,
		Brickwall,
		Bullet,
		Eagle,
		Ice,
		Panzer,
		Trees,
		Water,

		Unknown
	};
	IGameObject(const EObjectType, const glm::vec2 &, const glm::vec2 &, const float, const float);
	virtual ~IGameObject();

	virtual void render() const = 0;
	virtual void update(const double) {};
	virtual glm::vec2& getCurrentPosition();
	virtual glm::vec2& getCurrentDirection();
	virtual double getCurrentVelocity();
	virtual void setVelocity(const double);

public:
	const std::vector<Physics::Collider>& getColliders() const;
	const glm::vec2& getSIze() const;
	EObjectType getObjectType() const;
	virtual bool collides(const EObjectType);
	virtual void onCollision() {}

protected:
	glm::vec2 m_size;
	glm::vec2 m_position;
	glm::vec2 m_direction;
	EObjectType m_objectType;
	double m_velocity;
	float m_rotation;
	float m_layer;
	std::vector<Physics::Collider> m_colliders;
};
