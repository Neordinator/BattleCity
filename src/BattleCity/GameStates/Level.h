#pragma once

#include "IGameState.h"
#include "../Game.h"

#include <vector>
#include <string>
#include <memory>
#include <set>
#include <glm/vec2.hpp>


class IGameObject;
class Panzer;

class Level : public IGameState
{
public:
	Level(const std::vector<std::string>&, const Game::EGameMode);

	virtual void render() const override;
	virtual void update(const double delta) override;
	friend std::shared_ptr<IGameObject> createGameObjectFromDescription(const char, const glm::vec2&, const glm::vec2&, const float);
	virtual unsigned int getStateWidth() const override;
	virtual unsigned int getStateHeight() const override;
	virtual void processInput(const std::array<bool, 349>&) override;
	void initLevel();

	const glm::ivec2& getPlayerRespawn_1() const { return m_playerRespawn_1; }
	const glm::ivec2& getPlayerRespawn_2() const { return m_playerRespawn_2; }
	const glm::ivec2& getEnemyRespawn_1() const { return m_enemyRespawn_1; }
	const glm::ivec2& getEnemyRespawn_2() const { return m_enemyRespawn_2; }
	const glm::ivec2& getEnemyRespawn_3() const { return m_enemyRespawn_3; }

	std::vector<std::shared_ptr<IGameObject>> getObjectsInArea(const glm::vec2&, const glm::vec2&);

public:
	static constexpr unsigned int BLOCK_SIZE = 16;

private:
	size_t m_widthBlocks;
	size_t m_heightBlocks;
	unsigned int m_widthPixels;
	unsigned int m_heightPixels;

	glm::ivec2 m_playerRespawn_1;
	glm::ivec2 m_playerRespawn_2;
	glm::ivec2 m_enemyRespawn_1;
	glm::ivec2 m_enemyRespawn_2;
	glm::ivec2 m_enemyRespawn_3;

	std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
	std::shared_ptr<Panzer> m_pPanzer1;
	std::shared_ptr<Panzer> m_pPanzer2;
	std::set<std::shared_ptr<Panzer>> m_EnemyPanzers;
	Game::EGameMode m_eGameMode;
};