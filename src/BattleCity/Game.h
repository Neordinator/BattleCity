#pragma once

#include <glm/vec2.hpp>
#include <array>
#include <memory>

class IGameState;

namespace Render
{
	class ShaderProgram;
}

class Game
{
public:
	enum class EGameMode
	{
		OnePlayer,
		TwoPlayers
	};
	Game(const glm::uvec2& windowSize);
	~Game();

	void render();
	void update(const double delta);
	void setKey(const int key, const int action);
	bool init();
	unsigned int getCurrentWidth() const;
	unsigned int getCurrentHeight() const;
	void setWindowSize(const glm::uvec2&);
	void nextLevel(const EGameMode);
	void updateViewport();
	void startNewLevel(const size_t, const EGameMode);

	unsigned int stateSwitcher{ 0 };

private:
	enum class EGameState : uint8_t
	{
		StartScreen,
		LevelStart,
		Level,
		Pause,
		Scores,
		GameOver
	};


	std::array<bool, 349> m_keys;

	glm::ivec2 m_windowSize;
	EGameState m_eCurrentGameState;
	std::shared_ptr<Render::ShaderProgram> m_pSpriteShaderProgram;
	std::shared_ptr<IGameState> m_pCurrentGameState;
	size_t m_currentLevelIndex;
};