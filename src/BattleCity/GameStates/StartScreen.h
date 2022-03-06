#include "IGameState.h"
#include "../../Renderer/SpriteAnimator.h"

#include <memory>
#include <vector>
#include <string>
#include <glm/vec2.hpp>

namespace Render
{
	class Sprite;
}

class Game;

class StartScreen : public IGameState
{
public:
	StartScreen(const std::vector<std::string>& startScreenDescription, Game*);

	static constexpr unsigned int BLOCK_SIZE = 8;
	static constexpr unsigned int STARTSCREEN_WIDTH = 15 * BLOCK_SIZE * 2;
	static constexpr unsigned int STARTSCREEN_HEIGHT = 14 * BLOCK_SIZE * 2;
	static constexpr unsigned int MENU_WIDTH = 128;
	static constexpr unsigned int MENU_HEIGHT = 64;
	static constexpr unsigned int PANZER_SIZE = BLOCK_SIZE * 2;

	virtual void render() const override;
	virtual void update(const double) override;
	virtual void processInput(const std::array<bool, 349>&) override;
	virtual unsigned int getStateWidth() const override;
	virtual unsigned int getStateHeight() const override;

private:
	Game* m_pGame;
	int m_currentMenuSelection;
	bool m_keyReleased;
	std::vector<std::pair<std::shared_ptr<Render::Sprite>, glm::vec2>> m_sprites;
	std::pair<std::shared_ptr<Render::Sprite>, glm::vec2> m_menuSprite;
	std::pair<std::shared_ptr<Render::Sprite>, glm::vec2> m_panzerSprite;
	Render::SpriteAnimator m_panzerSpriteAnimator;
};