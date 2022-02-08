#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>

#include <array>
#include <iostream>

#include "../Physics/PhysicsEngine.h"
#include "../Game/BattleCity/Panzer.h"
#include "Level.h"

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