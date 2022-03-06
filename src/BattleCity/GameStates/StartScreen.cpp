#include "StartScreen.h"

#include <iostream>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"
#include "../Game.h"

std::shared_ptr<Render::Sprite> getSpriteForDescription(const char description)
{
	switch (description)
	{
	case '0':
		return ResourceManager::getSprite("brickWall_all");
	case '1':
		return ResourceManager::getSprite("brickWall_topLeft");
	case '2':
		return ResourceManager::getSprite("brickWall_topRight");
	case '3':
		return ResourceManager::getSprite("brickWall_top");
	case '4':
		return ResourceManager::getSprite("brickWall_bottomLeft");
	case '5':
		return ResourceManager::getSprite("brickWall_left");
	case '6':
		return ResourceManager::getSprite("brickWall_topRight_bottomLeft");
	case '7':
		return ResourceManager::getSprite("brickWall_top_bottomLeft");
	case '8':
		return ResourceManager::getSprite("brickWall_bottomRight");
	case '9':
		return ResourceManager::getSprite("brickWall_topLeft_bottomRight");
	case 'A':
		return ResourceManager::getSprite("brickWall_right");
	case 'B':
		return ResourceManager::getSprite("brickWall_top_bottomRight");
	case 'C':
		return ResourceManager::getSprite("brickWall_bottom");
	case 'D':
		return ResourceManager::getSprite("brickWall_topLeft_bottom");
	case 'E':
		return ResourceManager::getSprite("brickWall_topRight_bottom");
	case 'F':
		return nullptr;
	default:
		std::cerr << "Unknown Start Screen description: " << description << std::endl;
		break;
	}
	return nullptr;
}

StartScreen::StartScreen(const std::vector<std::string>& startScreenDescription, Game* pGame)
	: m_pGame(pGame)
	, m_currentMenuSelection(0)
	, m_keyReleased(true)
	, m_menuSprite(std::make_pair(ResourceManager::getSprite("menu"), glm::vec2(11 * BLOCK_SIZE, STARTSCREEN_HEIGHT - startScreenDescription.size() * BLOCK_SIZE - MENU_HEIGHT - 5 * BLOCK_SIZE)))
	, m_panzerSprite(std::make_pair(ResourceManager::getSprite("yellowPanzer1_right"), glm::vec2(8 * BLOCK_SIZE, m_menuSprite.second.y + 6 * BLOCK_SIZE - m_currentMenuSelection * 2 * BLOCK_SIZE)))
	, m_panzerSpriteAnimator(m_panzerSprite.first)
{
	if (startScreenDescription.empty())
	{
		std::cerr << "Empty level description" << std::endl;
	}
	auto leftOffsetPixels = 4 * BLOCK_SIZE;
	auto bottomOffset = STARTSCREEN_HEIGHT - 4 * BLOCK_SIZE;

	unsigned int currentBottomOffset = bottomOffset;
	for (const std::string& currentRow : startScreenDescription)
	{
		unsigned int currentLeftOffset = leftOffsetPixels;
		for (const char currentElement : currentRow)
		{
			m_sprites.emplace_back(std::make_pair(getSpriteForDescription(currentElement), glm::vec2(currentLeftOffset, currentBottomOffset)));
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}
}

void StartScreen::render() const
{
	for (const auto& current : m_sprites)
	{
		if (current.first)
		{
			current.first->render(current.second, glm::vec2(BLOCK_SIZE), 0.f);
		}
	}
	m_menuSprite.first->render(m_menuSprite.second, glm::vec2(MENU_WIDTH, MENU_HEIGHT), 0.f);
	m_panzerSprite.first->render(glm::vec2(m_panzerSprite.second.x, m_panzerSprite.second.y - m_currentMenuSelection * 2 * BLOCK_SIZE), glm::vec2(PANZER_SIZE), 0.f, 0.f, m_panzerSpriteAnimator.getCurrentFrame());
}

void StartScreen::update(const double delta)
{
	m_panzerSpriteAnimator.update(delta);
}

void StartScreen::processInput(const std::array<bool, 349>& keys)
{
	if (!keys[GLFW_KEY_W] && !keys[GLFW_KEY_S])
	{
		m_keyReleased = true;
	}
	if (m_keyReleased)
	{
		if (keys[GLFW_KEY_W])
		{
			m_keyReleased = false;
			--m_currentMenuSelection;
			if (m_currentMenuSelection < 0)
			{
				m_currentMenuSelection = 2;
			}
		}
		else if (keys[GLFW_KEY_S])
		{
			m_keyReleased = false;
			++m_currentMenuSelection;
			if (m_currentMenuSelection > 2)
			{
				m_currentMenuSelection = 0;
			}
		}
	}
	if (keys[GLFW_KEY_ENTER])
	{
		switch (m_currentMenuSelection)
		{
		case 0:
			m_pGame->startNewLevel(0, Game::EGameMode::OnePlayer);
			break;
		case 1:
			m_pGame->startNewLevel(0, Game::EGameMode::TwoPlayers);
			break;
		default:
			break;
		}
	}
}

unsigned int StartScreen::getStateWidth() const
{
	return STARTSCREEN_WIDTH;
}

unsigned int StartScreen::getStateHeight() const
{
	return STARTSCREEN_HEIGHT;
}