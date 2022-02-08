#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

#include <glm/vec2.hpp>

#include "BattleCity/BrickWall.h"
#include "BattleCity/BetonWall.h"
#include "BattleCity/Water.h"
#include "BattleCity/Trees.h"
#include "BattleCity/Eagle.h"
#include "BattleCity/Ice.h"
#include "BattleCity/Border.h"

class Level
{
public:
	Level(const std::vector<std::string>& levelDescription);

	void render() const;
	void update(const double delta);
	friend std::shared_ptr<IGameObject> createGameObjectFromDescription(const char, const glm::vec2&, const glm::vec2&, const float);
	size_t getLevelWidth() const;
	size_t getLevelHeight() const;

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
};