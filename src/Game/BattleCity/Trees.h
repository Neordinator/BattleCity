#pragma once

#include <memory>
#include <array>

#include "../IGameObject.h"
#include "../../Renderer/Sprite.h"

namespace Render
{
	class Sprite;
}
class Trees : public IGameObject
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
	Trees(const glm::vec2&, const glm::vec2&, const float, const float);

	//std::shared_ptr<BrickWall> operator=(BrickWall*);

	virtual void render() const override;

private:
	void renderBlock(const EBlockLocation) const;

	std::shared_ptr<Render::Sprite> m_sprite;
	std::array<glm::vec2, 4> m_blockOffsets;
};