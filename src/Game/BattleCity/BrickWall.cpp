#include "BrickWall.h"

#include "../IGameObject.h"
#include "../../src/Resources/ResourceManager.h"

/*template<typename Other, typename Target>
BrickWall::BrickWall(std::shared_ptr<Other> const& other, Target* p)
{
	Target i;
	std::shared_ptr<Target> sp(std::shared_ptr<Other>(), &i);
	assert(sp.use_count() == 0);
	assert(sp.get() == &i);
}*/
BrickWall::BrickWall(const EBrickWallType eBrickWallType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(IGameObject::EObjectType::Brickwall, position, size, rotation, layer)
	, m_pCurrentBrickState({ EBrickState::Destroyed, EBrickState::Destroyed, EBrickState::Destroyed, EBrickState::Destroyed })
	, m_blockOffsets({glm::vec2(0, m_size.y / 2.f), glm::vec2(m_size.x / 2.f, m_size.y / 2.f), glm::vec2(0, 0), glm::vec2(m_size.x / 2.f, 0) })
{
	m_sprites[static_cast<size_t>(EBrickState::All)] = ResourceManager::getSprite("brickWall_all");
    m_sprites[static_cast<size_t>(EBrickState::TopLeft)] = ResourceManager::getSprite("brickWall_topLeft");
    m_sprites[static_cast<size_t>(EBrickState::TopRight)] = ResourceManager::getSprite("brickWall_topRight");
    m_sprites[static_cast<size_t>(EBrickState::Top)] = ResourceManager::getSprite("brickWall_top");
    m_sprites[static_cast<size_t>(EBrickState::BottomLeft)] = ResourceManager::getSprite("brickWall_bottomLeft");
    m_sprites[static_cast<size_t>(EBrickState::Left)] = ResourceManager::getSprite("brickWall_left");
    m_sprites[static_cast<size_t>(EBrickState::TopRight_BottomLeft)] = ResourceManager::getSprite("brickWall_topRight_bottomLeft");
    m_sprites[static_cast<size_t>(EBrickState::Top_BottomLeft)] = ResourceManager::getSprite("brickWall_top_bottomLeft");
    m_sprites[static_cast<size_t>(EBrickState::BottomRight)] = ResourceManager::getSprite("brickWall_bottomRight");
    m_sprites[static_cast<size_t>(EBrickState::TopLeft_BottomRight)] = ResourceManager::getSprite("brickWall_topLeft_bottomRight");
    m_sprites[static_cast<size_t>(EBrickState::Right)] = ResourceManager::getSprite("brickWall_right");
    m_sprites[static_cast<size_t>(EBrickState::Top_BottomRight)] = ResourceManager::getSprite("brickWall_top_bottomRight");
    m_sprites[static_cast<size_t>(EBrickState::Bottom)] = ResourceManager::getSprite("brickWall_bottom");
    m_sprites[static_cast<size_t>(EBrickState::TopLeft_Bottom)] = ResourceManager::getSprite("brickWall_topLeft_bottom");
    m_sprites[static_cast<size_t>(EBrickState::TopRight_Bottom)] = ResourceManager::getSprite("brickWall_topRight_bottom");

    switch (eBrickWallType)
    {
    case EBrickWallType::All:
		m_pCurrentBrickState.fill(EBrickState::All);
		m_colliders.emplace_back(glm::vec2(0), m_size);
		break;
	case EBrickWallType::Top:
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0, m_size.y / 2), m_size);
		break;
	case EBrickWallType::Bottom:
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y / 2));
		break;
	case EBrickWallType::Left:
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y));
		break;
	case EBrickWallType::Right:
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), m_size);
		break;
	case EBrickWallType::TopLeft:
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), m_size);
		break;
	case EBrickWallType::TopRight:
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, m_size.y / 2), m_size);
		break;
	case EBrickWallType::BottomLeft:
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(0), glm::vec2(m_size.x / 2, m_size.y / 2));
		break;
	case EBrickWallType::BottomRight:
		m_pCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders.emplace_back(glm::vec2(m_size.x / 2, 0), glm::vec2(m_size.x, m_size.y / 2));
		break;
    }
}

/*std::shared_ptr<BrickWall> BrickWall::operator=(BrickWall* other)
{
	return std::make_shared<BrickWall>(std::move(other));
}*/

void BrickWall::renderBrick(const EBrickLocation eBrickLocation) const
{
	const EBrickState state = m_pCurrentBrickState[static_cast<size_t>(eBrickLocation)];
	if (state != EBrickState::Destroyed)
	{
		m_sprites[static_cast<size_t>(state)]->render(m_position + m_blockOffsets[static_cast<size_t>(eBrickLocation)], m_size / 2.f, m_rotation, m_layer);
	}
}

void BrickWall::render() const
{
	renderBrick(EBrickLocation::TopLeft);
	renderBrick(EBrickLocation::TopRight);
	renderBrick(EBrickLocation::BottomLeft);
	renderBrick(EBrickLocation::BottomRight);
}

void BrickWall::update(const double delta)
{
}
