#include "BetonWall.h"

class IGameObject;

namespace Render
{
	class Sprite;
}
/*template<typename Other, typename Target>
BrickWall::BrickWall(std::shared_ptr<Other> const& other, Target* p)
{
	Target i;
	std::shared_ptr<Target> sp(std::shared_ptr<Other>(), &i);
	assert(sp.use_count() == 0);
	assert(sp.get() == &i);
}*/
BetonWall::BetonWall(const EBetonWallType eBetonWallType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(IGameObject::EObjectType::BetonWall, position, size, rotation, layer)
	, m_pCurrentBlockState({ EBlockState::Destroyed, EBlockState::Destroyed, EBlockState::Destroyed, EBlockState::Destroyed })
	, m_sprite(ResourceManager::getSprite("betonWall"))
	, m_blockOffsets({ glm::vec2(0, m_size.y / 2.f), glm::vec2(m_size.x / 2.f, m_size.y / 2.f), glm::vec2(0, 0), glm::vec2(m_size.x / 2.f, 0) })
{

    switch (eBetonWallType)
    {
    case EBetonWallType::All:
		m_pCurrentBlockState.fill(EBlockState::Enabled);
		m_colliders.emplace_back(glm::vec2(0), m_size);
		break;
	case EBetonWallType::Top:
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] = EBlockState::Enabled;
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), m_size);
		break;
	case EBetonWallType::Bottom:
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] = EBlockState::Enabled;
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x, m_size.y / 2));
		break;
	case EBetonWallType::Left:
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] = EBlockState::Enabled;
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y));
		break;
	case EBetonWallType::Right:
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] = EBlockState::Enabled;
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), m_size);
		break;
	case EBetonWallType::TopLeft:
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::TopLeft)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), glm::vec2(m_size.x / 2, m_size.y));/*возможно тут ошибка*/
		break;
	case EBetonWallType::TopRight:
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::TopRight)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, m_size.y / 2), m_size);
		break;
	case EBetonWallType::BottomLeft:
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomLeft)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y / 2));
		break;
	case EBetonWallType::BottomRight:
		m_pCurrentBlockState[static_cast<size_t>(EBlockLocation::BottomRight)] = EBlockState::Enabled;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), glm::vec2(m_size.x, m_size.y / 2)); /*возможно тут ошибка*/
		break;
    }
}

/*std::shared_ptr<BrickWall> BrickWall::operator=(BrickWall* other)
{
	return std::make_shared<BrickWall>(std::move(other));
}*/

void BetonWall::renderBlock(const EBlockLocation eBlockLocation) const
{
	static const std::array<glm::vec2, 4> offsets = {
		glm::vec2(0, m_size.y / 2.f), glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
		glm::vec2(0, 0), glm::vec2(m_size.x / 2.f, 0)
	};
	const EBlockState state = m_pCurrentBlockState[static_cast<size_t>(eBlockLocation)];
	if (state != EBlockState::Destroyed)
	{
		m_sprite->render(m_position + offsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation, m_layer);
	}
}

void BetonWall::render() const
{
	renderBlock(EBlockLocation::TopLeft);
	renderBlock(EBlockLocation::TopRight);
	renderBlock(EBlockLocation::BottomLeft);
	renderBlock(EBlockLocation::BottomRight);
}

void BetonWall::update(const double delta)
{
}
