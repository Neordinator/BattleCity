#pragma once

#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <glm/vec2.hpp>

#include <vector>
#include <memory>

namespace Physics
{
	struct AABB /*Axis Aligned Bounding Box*/
	{
	public:
		AABB(const glm::vec2 _bottomLeft, const glm::vec2 _topRight) : bottomLeft(_bottomLeft), topRight(_topRight)
		{}
		glm::vec2 bottomLeft;
		glm::vec2 topRight;
	};
}

class IGameObject
{
public:
	IGameObject(const glm::vec2&, const glm::vec2&, const float, const float);
	virtual ~IGameObject();

	virtual void render() const = 0;
	virtual void update(const double) {};
	virtual glm::vec2& getCurrentPosition();
	virtual glm::vec2& getCurrentDirection();
	virtual double getCurrentVelocity();
	virtual void setVelocity(const double);

public:
	const std::vector<Physics::AABB>& getColliders() const;
	const glm::vec2& getSIze() const;

protected:
	glm::vec2 m_size;
	glm::vec2 m_position;
	glm::vec2 m_direction;
	double m_velocity;
	float m_rotation;
	float m_layer;
	std::vector<Physics::AABB> m_colliders;
};
#endif // !IGAMEOBJECT_H
