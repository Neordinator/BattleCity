#include "Bullet.h"

Bullet::Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer)
	: IGameObject(position, size, 0.f, layer)
	, m_pSprite_top(ResourceManager::getSprite("bullet_top")), m_pSprite_bottom(ResourceManager::getSprite("bullet_bottom"))
	, m_pSprite_left(ResourceManager::getSprite("bullet_left")), m_pSprite_right(ResourceManager::getSprite("bullet_right"))
	, m_eOrientation(EOrientation::Top)
	, m_isActive(false)
{
	setVelocity(velocity);
	m_colliders.emplace_back(glm::vec2(0), m_size);
}

void Bullet::render() const
{
	switch (m_eOrientation)
	{
	case EOrientation::Top:
		m_pSprite_top->render(m_position, m_size, m_rotation, m_layer);
		break;
	case EOrientation::Bottom:
		m_pSprite_bottom->render(m_position, m_size, m_rotation, m_layer);
		break;
	case EOrientation::Left:
		m_pSprite_left->render(m_position, m_size, m_rotation, m_layer);
		break;
	case EOrientation::Right:
		m_pSprite_right->render(m_position, m_size, m_rotation, m_layer);
		break;
	default:
		break;
	}
}

bool Bullet::isActive() const
{
	return m_isActive;
}

void Bullet::fire(const glm::vec2& position, const glm::vec2& direction)
{
	m_position = position;
	m_direction = direction;
	if (m_direction.x == 0.f)
	{
		m_eOrientation = (m_direction.y < 0) ? EOrientation::Bottom : EOrientation::Top;
	}
	else
	{
		m_eOrientation = (m_direction.x < 0) ? EOrientation::Left : EOrientation::Right;
	}
	m_isActive = true;
}
