#pragma once

#include <glm/vec2.hpp>

class IGameObject
{
public:
	IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual ~IGameObject();

	virtual void render() const = 0;
	virtual void update(const double delta) {};
	virtual glm::vec2& getCurrentPosition();
	virtual glm::vec2& getCurrentDirection();
	virtual double getCurrentVelocity();
	virtual void setVelocity(const double velocity);

protected:
	glm::vec2 m_size;
	glm::vec2 m_position;
	glm::vec2 m_direction;
	double m_velocity;
	float m_rotation;
	float m_layer;
};

