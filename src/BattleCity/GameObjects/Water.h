#pragma once

#include "../GameObjects/IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

#include <array>
#include <memory>

namespace Render
{
	class Sprite;
}

class Water : public IGameObject
{
public:

	enum class EBlockLocation : uint8_t
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

	/*template<typename Other, typename Target>
	BrickWall(std::shared_ptr<Other> const& other, Target* p);*/
	Water(const glm::vec2&, const glm::vec2&, const float, const float);

	//std::shared_ptr<BrickWall> operator=(BrickWall*);

	virtual void render() const override;
	void update(const double) override;
	virtual bool collides(const EObjectType) override;

private:
	void renderBlock(const EBlockLocation) const;

	std::shared_ptr<Render::Sprite> m_sprite;
	Render::SpriteAnimator m_spriteAnimator;
	std::array<glm::vec2, 4> m_blockOffsets;
};