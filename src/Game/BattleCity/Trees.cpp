#include "Trees.h"


/*template<typename Other, typename Target>
BrickWall::BrickWall(std::shared_ptr<Other> const& other, Target* p)
{
	Target i;
	std::shared_ptr<Target> sp(std::shared_ptr<Other>(), &i);
	assert(sp.use_count() == 0);
	assert(sp.get() == &i);
}*/
Trees::Trees( const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: IGameObject(IGameObject::EObjectType::Trees, position, size, rotation, layer)
	, m_sprite(ResourceManager::getSprite("trees"))
	, m_blockOffsets({ glm::vec2(0, m_size.y / 2.f), glm::vec2(m_size.x / 2.f, m_size.y / 2.f), glm::vec2(0, 0), glm::vec2(m_size.x / 2.f, 0) })
{

}

/*std::shared_ptr<BrickWall> BrickWall::operator=(BrickWall* other)
{
	return std::make_shared<BrickWall>(std::move(other));
}*/

void Trees::renderBlock(const EBlockLocation eBlockLocation) const
{
	m_sprite->render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation, m_layer);
}

void Trees::render() const
{
	renderBlock(EBlockLocation::TopLeft);
	renderBlock(EBlockLocation::TopRight);
	renderBlock(EBlockLocation::BottomLeft);
	renderBlock(EBlockLocation::BottomRight);
}
