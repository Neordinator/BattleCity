#pragma once

#include "../GameObjects/IGameObject.h"

#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

#include <glm/vec2.hpp>
#include <memory>

namespace Render
{
	class Sprite;
}

class Bullet;
class AIComponent;

class Panzer : public IGameObject
{
public:
	enum class EPanzerType : uint8_t
	{
		Yellow1,	Yellow2,	Yellow3,	Yellow4,	Yellow5,	Yellow6,	Yellow7,	Yellow8,
		Gray1,		Gray2,		Gray3,		Gray4,		Gray5,		Gray6,		Gray7,		Gray8,
		Green1,		Green2,		Green3,		Green4,		Green5,		Green6,		Green7,		Green8,
		Red1,		Red2,		Red3,		Red4,		Red5,		Red6,		Red7,		Red8
	};
	inline static std::string PanzerTypeToSpriteString[] = {
		"yellowPanzer1",	"yellowPanzer2",	"yellowPanzer3",	"yellowPanzer4",	"yellowPanzer5",	"yellowPanzer6",	"yellowPanzer7",	"yellowPanzer8",
		"grayPanzer1",		"grayPanzer2",		"grayPanzer3",		"grayPanzer4",		"grayPanzer5",		"grayPanzer6",		"grayPanzer7",		"grayPanzer8",
		"greenPanzer1",		"greenPanzer2",		"greenPanzer3",		"greenPanzer4",		"greenPanzer5",		"greenPanzer6",		"greenPanzer7",		"greenPanzer8",
		"redPanzer1",		"redPanzer2",		"redPanzer3",		"redPanzer4",		"redPanzer5",		"redPanzer6",		"redPanzer7",		"redPanzer8"
	};
	/*inline static std::string PanzerTypeToSpriteString[] = {
		"yellowPanzer1_top",
		"yellowPanzer1_left",
		"yellowPanzer1_bottom",
		"yellowPanzer1_right",
		"yellowPanzer2_top",
		"yellowPanzer2_left",
		"yellowPanzer2_bottom",
		"yellowPanzer2_right",
		"yellowPanzer3_top",
		"yellowPanzer3_left",
		"yellowPanzer3_bottom",
		"yellowPanzer3_right",
		"yellowPanzer4_top",
		"yellowPanzer4_left",
		"yellowPanzer4_bottom",
		"yellowPanzer4_right",
		"yellowPanzer5_top",
		"yellowPanzer5_left",
		"yellowPanzer5_bottom",
		"yellowPanzer5_right",
		"yellowPanzer6_top",
		"yellowPanzer6_left",
		"yellowPanzer6_bottom",
		"yellowPanzer6_right",
		"yellowPanzer7_top",
		"yellowPanzer7_left",
		"yellowPanzer7_bottom",
		"yellowPanzer7_right",
		"yellowPanzer8_top",
		"yellowPanzer8_left",
		"yellowPanzer8_bottom",
		"yellowPanzer8_right",
		"grayPanzer1_top",
		"grayPanzer1_left",
		"grayPanzer1_bottom",
		"grayPanzer1_right",
		"grayPanzer2_top",
		"grayPanzer2_left",
		"grayPanzer2_bottom",
		"grayPanzer2_right",
		"grayPanzer3_top",
		"grayPanzer3_left",
		"grayPanzer3_bottom",
		"grayPanzer3_right",
		"grayPanzer4_top",
		"grayPanzer4_left",
		"grayPanzer4_bottom",
		"grayPanzer4_right",
		"grayPanzer5_top",
		"grayPanzer5_left",
		"grayPanzer5_bottom",
		"grayPanzer5_right",
		"grayPanzer6_top",
		"grayPanzer6_left",
		"grayPanzer6_bottom",
		"grayPanzer6_right",
		"grayPanzer7_top",
		"grayPanzer7_left",
		"grayPanzer7_bottom",
		"grayPanzer7_right",
		"grayPanzer8_top",
		"grayPanzer8_left",
		"grayPanzer8_bottom",
		"grayPanzer8_right",
		"greenPanzer1_top",
		"greenPanzer1_left",
		"greenPanzer1_bottom",
		"greenPanzer1_right",
		"greenPanzer2_top",
		"greenPanzer2_left",
		"greenPanzer2_bottom",
		"greenPanzer2_right",
		"greenPanzer3_top",
		"greenPanzer3_left",
		"greenPanzer3_bottom",
		"greenPanzer3_right",
		"greenPanzer4_top",
		"greenPanzer4_left",
		"greenPanzer4_bottom",
		"greenPanzer4_right",
		"greenPanzer5_top",
		"greenPanzer5_left",
		"greenPanzer5_bottom",
		"greenPanzer5_right",
		"greenPanzer6_top",
		"greenPanzer6_left",
		"greenPanzer6_bottom",
		"greenPanzer6_right",
		"greenPanzer7_top",
		"greenPanzer7_left",
		"greenPanzer7_bottom",
		"greenPanzer7_right",
		"greenPanzer8_top",
		"greenPanzer8_left",
		"greenPanzer8_bottom",
		"greenPanzer8_right",
		"redPanzer1_top",
		"redPanzer1_left",
		"redPanzer1_bottom",
		"redPanzer1_right",
		"redPanzer2_top",
		"redPanzer2_left",
		"redPanzer2_bottom",
		"redPanzer2_right",
		"redPanzer3_top",
		"redPanzer3_left",
		"redPanzer3_bottom",
		"redPanzer3_right",
		"redPanzer4_top",
		"redPanzer4_left",
		"redPanzer4_bottom",
		"redPanzer4_right",
		"redPanzer5_top",
		"redPanzer5_left",
		"redPanzer5_bottom",
		"redPanzer5_right",
		"redPanzer6_top",
		"redPanzer6_left",
		"redPanzer6_bottom",
		"redPanzer6_right",
		"redPanzer7_top",
		"redPanzer7_left",
		"redPanzer7_bottom",
		"redPanzer7_right",
		"redPanzer8_top",
		"redPanzer8_left",
		"redPanzer8_bottom",
		"redPanzer8_right"
	};*/
	enum class EOrientation : uint8_t
	{
		Top,
		Bottom,
		Left,
		Right
	};

public:
	Panzer(const Panzer::EPanzerType, const bool, const bool, const EOrientation, const double, const glm::vec2&, const glm::vec2&, const float);

public:
	void render() const override;
	void setOrientation(const EOrientation);
	void update(const double) override;
	double getMaxVelocity() const;
	void setVelocity(const double) override;
	void fire();

private:
	EOrientation m_eOrientation;
	std::shared_ptr<Bullet> m_pCurrentBullet;
	std::shared_ptr<Render::Sprite> m_pSprite_top;
	std::shared_ptr<Render::Sprite> m_pSprite_bottom;
	std::shared_ptr<Render::Sprite> m_pSprite_left;
	std::shared_ptr<Render::Sprite> m_pSprite_right;
	Render::SpriteAnimator m_spriteAnimator_top;
	Render::SpriteAnimator m_spriteAnimator_bottom;
	Render::SpriteAnimator m_spriteAnimator_left;
	Render::SpriteAnimator m_spriteAnimator_right;

	std::shared_ptr<Render::Sprite> m_pSprite_respawn;
	Render::SpriteAnimator m_spriteAnimator_respawn;

	std::shared_ptr<Render::Sprite> m_pSprite_shield;
	Render::SpriteAnimator m_spriteAnimator_shield;

	Timer m_respawnTimer;
	Timer m_shieldTimer;

	bool m_isSpawning;
	bool m_hasShield;
	bool m_bShieldOnSpawn;
	double m_maxVelocity;

	std::unique_ptr<AIComponent> m_pAIComponent;

	static const std::string& getPanzerSpriteFromEnum(const EPanzerType);
};