#pragma once

#include <memory>
#include <array>

#include "../IGameObject.h"
#include "../../src/Resources/ResourceManager.h"

class BrickWall : public IGameObject
{
public:

	enum class EBrickWallType : uint8_t
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
	enum class EBrickState : uint8_t
	{
		All = 0,
		TopLeft,
		TopRight,
		Top,
		BottomLeft,
		Left,
		TopRight_BottomLeft,
		Top_BottomLeft,
		BottomRight,
		TopLeft_BottomRight,
		Right,
		Top_BottomRight,
		Bottom,
		TopLeft_Bottom,
		TopRight_Bottom,
		Destroyed
	};
	enum class EBrickLocation : uint8_t
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

	/*template<typename Other, typename Target>
	BrickWall(std::shared_ptr<Other> const& other, Target* p);*/
	BrickWall(const EBrickWallType, const glm::vec2&, const glm::vec2&, const float, const float);

	//std::shared_ptr<BrickWall> operator=(BrickWall*);

	virtual void render() const override;
	virtual void update(const double delta) override;

private:
	void renderBrick(const EBrickLocation) const;

	std::array<EBrickState, 4> m_pCurrentBrickState;
	std::array<std::shared_ptr<Render::Sprite>, 15> m_sprites;
	std::array<glm::vec2, 4> m_blockOffsets;
};