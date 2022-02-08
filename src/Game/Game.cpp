#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>

#include "Game.h"

Game::Game(const glm::ivec2& windowSize) : m_eCurrentGameState(EGameState::Active), m_windowSize(windowSize)
{
	m_keys.fill(false);
}
Game::~Game()
{
}

void Game::render()
{
	if (m_pPanzer)
	{
		m_pPanzer->render();
	}
	if (m_pLevel)
	{
		m_pLevel->render();
	}
}

void Game::update(const double delta)
{
	if (m_pLevel)
	{
		m_pLevel->update(delta);
	}
	if (m_pPanzer)
	{
		if (m_keys[GLFW_KEY_W])
		{
			m_pPanzer->setOrientation(Panzer::EOrientation::Top);
			m_pPanzer->move(true);
		}
		else if (m_keys[GLFW_KEY_A])
		{
			m_pPanzer->setOrientation(Panzer::EOrientation::Left);
			m_pPanzer->move(true);
		}
		else if (m_keys[GLFW_KEY_S])
		{
			m_pPanzer->setOrientation(Panzer::EOrientation::Bottom);
			m_pPanzer->move(true);
		}
		else if (m_keys[GLFW_KEY_D])
		{
			m_pPanzer->setOrientation(Panzer::EOrientation::Right);
			m_pPanzer->move(true);
		}
		else
		{
			m_pPanzer->move(false);
		}
		m_pPanzer->update(delta);
	}
}

void Game::setKey(const int key, const int action)
{
	m_keys[key] = action;
}

bool Game::init()
{
	ResourceManager::loadJSONResources("res/BattleCity.json");

	auto pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");
	if (!pSpriteShaderProgram)
	{
		std::cerr << "Can't find shader program: " << "spriteShader" << std::endl;
		return false;
	}

	/*glm::mat4 modelMatrix_1 = glm::mat4(1.f);
	modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.0f, 0.0f));

	glm::mat4 modelMatrix_2 = glm::mat4(1.f);
	modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.0f, 0.0f));*/

	m_pLevel = std::make_unique <Level>(ResourceManager::getLevels()[1]);
	m_windowSize.x = static_cast<int>(m_pLevel->getLevelWidth());
	m_windowSize.y = static_cast<int>(m_pLevel->getLevelHeight());

	glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);

	pSpriteShaderProgram->use();
	pSpriteShaderProgram->setInt("tex", 0);
	pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

	m_pPanzer = std::make_unique<Panzer>(0.05, m_pLevel->getPlayerRespawn_1(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f);

	m_pLevel = std::make_unique <Level>(ResourceManager::getLevels()[1]);

	return true;
}

size_t Game::getCurrentLevelWidth() const
{
	return m_pLevel->getLevelWidth();
}

size_t Game::getCurrentLevelHeight() const
{
	return m_pLevel->getLevelHeight();
}
