#include "Panzer.h"

Panzer::Panzer(std::shared_ptr<Render::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position) : m_eOrientation(EOrientation::Top),
	m_pSprite(pSprite), m_move(false), m_velocity(velocity), m_position(position), m_moveOffset(glm::vec2(0.f, 1.f))
{
	m_pSprite->setPosition(m_position);
}

void Panzer::render() const
{
	m_pSprite->render();
}

void Panzer::setOrientation(const EOrientation eOrientation)
{
	if (m_eOrientation == eOrientation)
	{
		return;
	}
	m_eOrientation = eOrientation;
	switch (m_eOrientation)
	{
	case Panzer::EOrientation::Top:
		m_pSprite->setState("panzerTopState");
		m_moveOffset.x = 0.f;
		m_moveOffset.y = 1.f;
		break;
	case Panzer::EOrientation::Bottom:
		m_pSprite->setState("panzerBottomState");
		m_moveOffset.x = 0.f;
		m_moveOffset.y = -1.f;
		break;
	case Panzer::EOrientation::Left:
		m_pSprite->setState("panzerLeftState");
		m_moveOffset.x = -1.f;
		m_moveOffset.y = 0.f;
		break;
	case Panzer::EOrientation::Right:
		m_pSprite->setState("panzerRightState");
		m_moveOffset.x = 1.f;
		m_moveOffset.y = 0.f;
		break;
	default:
		break;
	}
}

void Panzer::move(const bool move)
{
	m_move = move;
}

void Panzer::update(const uint64_t delta)
{
	if (m_move)
	{
		m_position += delta * m_velocity * m_moveOffset;
		m_pSprite->setPosition(m_position);
		m_pSprite->update(delta);
	}
}
