#pragma once

#include <array>
#include <iostream>

#include "../Resources/ResourceManager.h"
#include "../Game/BattleCity/Panzer.h"
#include "Level.h"

class Panzer;
class Level;

class Game
{
public:
	Game(const glm::ivec2& windowSize);
	~Game();

	void render();
	void update(const uint64_t delta);
	void setKey(const int key, const int action);
	bool init();

	unsigned int stateSwitcher{ 0 };

private:
	std::array<bool, 349> m_keys;

	enum class EGameState
	{
		Active,
		Pause
	};

	glm::ivec2 m_windowSize;
	EGameState m_eCurrentGameState;
	std::unique_ptr<Panzer> m_pPanzer;
	std::unique_ptr<Level> m_pLevel;
};