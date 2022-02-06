#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <glm/vec2.hpp>

#include "BattleCity/BrickWall.h"
#include "BattleCity/BetonWall.h"
#include "BattleCity/Water.h"
#include "BattleCity/Trees.h"
#include "BattleCity/Eagle.h"
#include "BattleCity/Ice.h"
#include "IGameObject.h"

class IGameObject;
class BrickWall;

class Level
{
public:
	Level(const std::vector<std::string>& levelDescription);

	void render() const;
	void update(const uint64_t delta);
	friend std::shared_ptr<IGameObject> createGameObjectFromDescription(const char, const glm::vec2&, const glm::vec2&, const float);

private:
	unsigned int m_width;
	unsigned int m_height;

	std::vector<std::shared_ptr<IGameObject>> m_mapObjects;
};