#pragma once

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <glm/vec2.hpp>
#include <unordered_set>
#include <memory>

#include "../Game/IGameObject.h"
#include "../Game/Level.h"

namespace Physics
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine() = delete;
		~PhysicsEngine() = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;

		static void init();
		static void terminate();
		static void update(const double);
		static void addDynamicGameObject(std::shared_ptr<IGameObject>);
		static void setCurrentLevel(std::shared_ptr<Level>);

	private:
		static bool hasIntersection(const std::vector<Physics::AABB>& colliders1, const glm::vec2& position1,
			const std::vector<Physics::AABB>& colliders2, const glm::vec2& position2
		);

	private:
		static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObjects;
		static std::shared_ptr<Level> m_pCurrentLevel;
	};
}
#endif // !PHYSICSENGINE_H
