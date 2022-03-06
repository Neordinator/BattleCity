#pragma once

#include "../GameObjects/IGameObject.h"

#include <array>
#include <memory>

namespace Render
{
	class Sprite;
}

class BetonWall : public IGameObject
{
public:

	enum class EBetonWallType : uint8_t
	{
		All,
		Top,
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	enum class EBlockState : uint8_t
	{
		Enabled = 0,
		Destroyed
	};
	enum class EBlockLocation : uint8_t
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

	/*template<typename Other, typename Target>
	BrickWall(std::shared_ptr<Other> const& other, Target* p);*/
	BetonWall(const EBetonWallType, const glm::vec2&, const glm::vec2&, const float, const float);

	//std::shared_ptr<BrickWall> operator=(BrickWall*);

	virtual void render() const override;
	virtual void update(const double delta) override;

private:
	void renderBlock(const EBlockLocation) const;

	std::array<EBlockState, 4> m_pCurrentBlockState;
	std::shared_ptr<Render::Sprite> m_sprite;
	std::array<glm::vec2, 4> m_blockOffsets;
};