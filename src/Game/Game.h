#pragma once

#include <array>
#include <iostream>

#include "../Resources/ResourceManager.h"
#include "../Game/BattleCity/Panzer.h"
#include "../Physics/PhysicsEngine.h"
#include "Level.h"

class Panzer;
class Level;

class Game
{
public:
	Game(const glm::ivec2& windowSize);
	~Game();

	void render();
	void update(const double delta);
	void setKey(const int key, const int action);
	bool init();
	size_t getCurrentLevelWidth() const;
	size_t getCurrentLevelHeight() const;

	unsigned int stateSwitcher{ 0 };

private:
	std::array<bool, 349> m_keys;

	enum class EGameState : uint8_t
	{
		Active,
		Pause
	};

	glm::ivec2 m_windowSize;
	EGameState m_eCurrentGameState;
	std::shared_ptr<Panzer> m_pPanzer;
	std::shared_ptr<Level> m_pLevel;
};