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
	//pAnimeGirlAnimatedSprite->render();
	if (m_pPanzer)
	{
		m_pPanzer->render();
	}
}

void Game::update(const uint64_t delta)
{
	//ResourceManager::getAnimatedSprite("AnimeGirlAnimatedSprite")->update(delta);
	//pAnimeGirlAnimatedSprite->update(delta);
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
	auto pDefaultShaderProgram = ResourceManager::loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
	if (!pDefaultShaderProgram)
	{
		std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
		return false;
	}
	auto pSpriteShaderProgram = ResourceManager::loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
	if (!pDefaultShaderProgram)
	{
		std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
		return false;
	}
	pDefaultShaderProgram->use();
	pDefaultShaderProgram->setInt("tex", 0);

	glm::mat4 modelMatrix_1 = glm::mat4(1.f);
	modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.0f, 0.0f));

	glm::mat4 modelMatrix_2 = glm::mat4(1.f);
	modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.0f, 0.0f));

	glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(m_windowSize.x), 0.0f, static_cast<float>(m_windowSize.y), -100.0f, 100.0f);
	pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

	pSpriteShaderProgram->use();
	pSpriteShaderProgram->setInt("tex", 0);
	pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

	/*auto tex = ResourceManager::loadTexture("BattleCityTexture", "res/textures/BattleCity_16x16.png");

	std::vector<std::string> battleCitySubTexturesNames = {
		"block", "topBlock", "bottomBlock", "leftBlock", "rightBlock", "topLeftBlock", "topRightBlock", "bottomLeftBlock", "bottomRightBlock",
		"beton", "topBeton", "bottomBeton", "leftBeton", "rightBeton", "topLeftBeton", "topRightBeton", "bottomLeftBeton", "bottomRightBeton",
		"water1", "water2", "water3", "trees", "ice", "wall", "eagle", "deadEagle", "nothing", "respawn1", "respawn2", "respawn3", "respawn4"
	};
	auto pBattleCityTextureAtlas = ResourceManager::loadTextureAtlas("BattleCityTextureAtlas", "res/textures/BattleCity_16x16.png", std::move(battleCitySubTexturesNames), 16, 16);
	auto pBattleCitySprite = ResourceManager::loadSprite("BattleCitySprite", "BattleCityTextureAtlas", "SpriteShader", 100, 100, "block");
	pBattleCitySprite->setPosition(glm::vec2(300, 100));
	auto pBattleCityAnimatedSprite = ResourceManager::loadAnimatedSprite("BattleCityAnimatedSprite", "BattleCityTextureAtlas", "SpriteShader", 100, 100, "beton");
	pBattleCityAnimatedSprite->setPosition(glm::vec2(300, 300));
	std::vector<std::pair<std::string, uint64_t>> waterState;
	waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 500000000));
	waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 500000000));
	waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 500000000));
	std::vector<std::pair<std::string, uint64_t>> eagleState;
	eagleState.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 10000000000));
	eagleState.emplace_back(std::make_pair<std::string, uint64_t>("deadEagle", 10000000000));
	pBattleCityAnimatedSprite->insertState("waterState", std::move(waterState));
	pBattleCityAnimatedSprite->insertState("eagleState", std::move(eagleState));
	pBattleCityAnimatedSprite->setState("waterState");


	std::vector<std::string> animeGirlSubTexturesNames = {
		"normal1",		"normal2",		"normal3",		"hurt1",		"hurt2",		"hurt3",
		"victory1",		"victory2",		"victory3",		"afraid1",		"afraid2",		"afraid3",
		"sad1",			"sad2",			"sad3",			"angry1",		"angry2",		"angry3",
		"depressed1",	"depressed2",	"depressed3",	"enraged1",		"enraged2",		"enraged3",
		"happy1",		"happy2",		"happy3",		"ecstatic1",	"ecstatic2",	"ecstatic3"
	};
	auto pAnimeGirlTextureAtlas = ResourceManager::loadTextureAtlas("AnimeGirlTextureAtlas", "res/textures/AnimeGirlPortrait.png", std::move(animeGirlSubTexturesNames), 106, 106);
	auto pAnimeGirlSprite = ResourceManager::loadSprite("AnimeGirlSprite", "AnimeGirlTextureAtlas", "SpriteShader", 100, 100, "hurt1");
	pAnimeGirlSprite->setPosition(glm::vec2(300, 200));
	pAnimeGirlAnimatedSprite = ResourceManager::loadAnimatedSprite("AnimeGirlAnimatedSprite", "AnimeGirlTextureAtlas", "SpriteShader", 100, 100, "sad1");
	pAnimeGirlAnimatedSprite->setPosition(glm::vec2(300, 400));
	std::vector<std::pair<std::string, uint64_t>> normalState;
	normalState.emplace_back(std::make_pair<std::string, uint64_t>("normal1", 50000000));
	normalState.emplace_back(std::make_pair<std::string, uint64_t>("normal2", 50000000));
	normalState.emplace_back(std::make_pair<std::string, uint64_t>("normal3", 50000000));
	std::vector<std::pair<std::string, uint64_t>> hurtState;
	hurtState.emplace_back(std::make_pair<std::string, uint64_t>("hurt1", 50000000));
	hurtState.emplace_back(std::make_pair<std::string, uint64_t>("hurt2", 50000000));
	hurtState.emplace_back(std::make_pair<std::string, uint64_t>("hurt3", 50000000));
	std::vector<std::pair<std::string, uint64_t>> victoryState;
	victoryState.emplace_back(std::make_pair<std::string, uint64_t>("victory1", 50000000));
	victoryState.emplace_back(std::make_pair<std::string, uint64_t>("victory2", 50000000));
	victoryState.emplace_back(std::make_pair<std::string, uint64_t>("victory3", 50000000));
	std::vector<std::pair<std::string, uint64_t>> afraidState;
	afraidState.emplace_back(std::make_pair<std::string, uint64_t>("afraid1", 50000000));
	afraidState.emplace_back(std::make_pair<std::string, uint64_t>("afraid2", 50000000));
	afraidState.emplace_back(std::make_pair<std::string, uint64_t>("afraid3", 50000000));
	std::vector<std::pair<std::string, uint64_t>> sadState;
	sadState.emplace_back(std::make_pair<std::string, uint64_t>("sad1", 50000000));
	sadState.emplace_back(std::make_pair<std::string, uint64_t>("sad2", 50000000));
	sadState.emplace_back(std::make_pair<std::string, uint64_t>("sad3", 50000000));
	std::vector<std::pair<std::string, uint64_t>> angryState;
	angryState.emplace_back(std::make_pair<std::string, uint64_t>("angry1", 50000000));
	angryState.emplace_back(std::make_pair<std::string, uint64_t>("angry2", 50000000));
	angryState.emplace_back(std::make_pair<std::string, uint64_t>("angry3", 50000000));
	std::vector<std::pair<std::string, uint64_t>> depressedState;
	depressedState.emplace_back(std::make_pair<std::string, uint64_t>("depressed1", 50000000));
	depressedState.emplace_back(std::make_pair<std::string, uint64_t>("depressed2", 50000000));
	depressedState.emplace_back(std::make_pair<std::string, uint64_t>("depressed3", 50000000));
	std::vector<std::pair<std::string, uint64_t>> enragedState;
	enragedState.emplace_back(std::make_pair<std::string, uint64_t>("enraged1", 50000000));
	enragedState.emplace_back(std::make_pair<std::string, uint64_t>("enraged2", 50000000));
	enragedState.emplace_back(std::make_pair<std::string, uint64_t>("enraged3", 50000000));
	std::vector<std::pair<std::string, uint64_t>> happyState;
	happyState.emplace_back(std::make_pair<std::string, uint64_t>("happy1", 50000000));
	happyState.emplace_back(std::make_pair<std::string, uint64_t>("happy2", 50000000));
	happyState.emplace_back(std::make_pair<std::string, uint64_t>("happy3", 50000000));
	std::vector<std::pair<std::string, uint64_t>> ecstaticState;
	ecstaticState.emplace_back(std::make_pair<std::string, uint64_t>("ecstatic1", 50000000));
	ecstaticState.emplace_back(std::make_pair<std::string, uint64_t>("ecstatic2", 50000000));
	ecstaticState.emplace_back(std::make_pair<std::string, uint64_t>("ecstatic2", 50000000));
	pAnimeGirlAnimatedSprite->insertState("normalState", std::move(normalState));
	pAnimeGirlAnimatedSprite->insertState("hurtState", std::move(hurtState));
	pAnimeGirlAnimatedSprite->insertState("victoryState", std::move(victoryState));
	pAnimeGirlAnimatedSprite->insertState("afraidState", std::move(afraidState));
	pAnimeGirlAnimatedSprite->insertState("sadState", std::move(sadState));
	pAnimeGirlAnimatedSprite->insertState("angryState", std::move(angryState));
	pAnimeGirlAnimatedSprite->insertState("depressedState", std::move(depressedState));
	pAnimeGirlAnimatedSprite->insertState("enragedState", std::move(enragedState));
	pAnimeGirlAnimatedSprite->insertState("happyState", std::move(happyState));
	pAnimeGirlAnimatedSprite->insertState("ecstaticState", std::move(ecstaticState));
	pAnimeGirlAnimatedSprite->setState("normalState");*/
	std::vector<std::string> panzerSubTexturesNames = {
		"yellowPanzer1Top1",	"yellowPanzer1Top2",	"yellowPanzer1Lef1",	"yellowPanzer1Left2",
		"yellowPanzer1Bottom1", "yellowPanzer1Bottom2", "yellowPanzer1Right1",	"yellowPanzer1Right2",
		"grayPanzer1Top1",		"grayPanzer1Top2",		"grayPanzer1Left1",		"grayPanzer1Left2",
		"grayPanzer1Bottom1",	"grayPanzer1Bottom2",	"grayPanzer1Right1",	"grayPanzer1Right2",

		"yellowPanzer2Top1",	"yellowPanzer2Top2",	"yellowPanzer2Lef1",	"yellowPanzer2Left2",
		"yellowPanzer2Bottom1", "yellowPanzer2Bottom2", "yellowPanzer2Right1",	"yellowPanzer2Right2",
		"grayPanzer2Top1",		"grayPanzer2Top2",		"grayPanzer2Left1",		"grayPanzer2Left2",
		"grayPanzer2Bottom1",	"grayPanzer2Bottom2",	"grayPanzer2Right1",	"grayPanzer2Right2",

		"yellowPanzer3Top1",	"yellowPanzer3Top2",	"yellowPanzer3Lef1",	"yellowPanzer3Left2",
		"yellowPanzer3Bottom1", "yellowPanzer3Bottom2", "yellowPanzer3Right1",	"yellowPanzer3Right2",
		"grayPanzer3Top1",		"grayPanzer3Top2",		"grayPanzer3Left1",		"grayPanzer3Left2",
		"grayPanzer3Bottom1",	"grayPanzer3Bottom2",	"grayPanzer3Right1",	"grayPanzer3Right2",

		"yellowPanzer4Top1",	"yellowPanzer4Top2",	"yellowPanzer4Lef1",	"yellowPanzer4Left2",
		"yellowPanzer4Bottom1", "yellowPanzer4Bottom2", "yellowPanzer4Right1",	"yellowPanzer4Right2",
		"grayPanzer4Top1",		"grayPanzer4Top2",		"grayPanzer4Left1",		"grayPanzer4Left2",
		"grayPanzer4Bottom1",	"grayPanzer4Bottom2",	"grayPanzer4Right1",	"grayPanzer4Right2",

		"yellowPanzer5Top1",	"yellowPanzer5Top2",	"yellowPanzer5Lef1",	"yellowPanzer5Left2",
		"yellowPanzer5Bottom1", "yellowPanzer5Bottom2", "yellowPanzer5Right1",	"yellowPanzer5Right2",
		"grayPanzer5Top1",		"grayPanzer5Top2",		"grayPanzer5Left1",		"grayPanzer5Left2",
		"grayPanzer5Bottom1",	"grayPanzer5Bottom2",	"grayPanzer5Right1",	"grayPanzer5Right2",

		"yellowPanzer6Top1",	"yellowPanzer6Top2",	"yellowPanzer6Lef1",	"yellowPanzer6Left2",
		"yellowPanzer6Bottom1", "yellowPanzer6Bottom2", "yellowPanzer6Right1",	"yellowPanzer6Right2",
		"grayPanzer6Top1",		"grayPanzer6Top2",		"grayPanzer6Left1",		"grayPanzer6Left2",
		"grayPanzer6Bottom1",	"grayPanzer6Bottom2",	"grayPanzer6Right1",	"grayPanzer6Right2",

		"yellowPanzer7Top1",	"yellowPanzer7Top2",	"yellowPanzer7Lef1",	"yellowPanzer7Left2",
		"yellowPanzer7Bottom1", "yellowPanzer7Bottom2", "yellowPanzer7Right1",	"yellowPanzer7Right2",
		"grayPanzer7Top1",		"grayPanzer7Top2",		"grayPanzer7Left1",		"grayPanzer7Left2",
		"grayPanzer7Bottom1",	"grayPanzer7Bottom2",	"grayPanzer7Right1",	"grayPanzer7Right2",

		"yellowPanzer8Top1",	"yellowPanzer8Top2",	"yellowPanzer8Lef1",	"yellowPanzer8Left2",
		"yellowPanzer8Bottom1", "yellowPanzer8Bottom2", "yellowPanzer8Right1",	"yellowPanzer8Right2",
		"grayPanzer8Top1",		"grayPanzer8Top2",		"grayPanzer8Left1",		"grayPanzer8Left2",
		"grayPanzer8Bottom1",	"grayPanzer8Bottom2",	"grayPanzer8Right1",	"grayPanzer8Right2",

		"greenPanzer1Top1",		"greenPanzer1Top2",		"greenPanzer1Lef1",		"greenPanzer1Left2",
		"greenPanzer1Bottom1",	"greenPanzer1Bottom2",	"greenPanzer1Right1",	"greenPanzer1Right2",
		"redPanzer1Top1",		"redPanzer1Top2",		"redPanzer1Lef1",		"redPanzer1Left2",
		"redPanzer1Bottom1",	"redPanzer1Bottom2",	"redPanzer1Right1",		"redPanzer1Right2",

		"greenPanzer2Top1",		"greenPanzer2Top2",		"greenPanzer2Lef1",		"greenPanzer2Left2",
		"greenPanzer2Bottom1",	"greenPanzer2Bottom2",	"greenPanzer2Right1",	"greenPanzer2Right2",
		"redPanzer2Top1",		"redPanzer2Top2",		"redPanzer2Lef1",		"redPanzer2Left2",
		"redPanzer2Bottom1",	"redPanzer2Bottom2",	"redPanzer2Right1",		"redPanzer2Right2",

		"greenPanzer3Top1",		"greenPanzer3Top2",		"greenPanzer3Lef1",		"greenPanzer3Left2",
		"greenPanzer3Bottom1",	"greenPanzer3Bottom2",	"greenPanzer3Right1",	"greenPanzer3Right2",
		"redPanzer3Top1",		"redPanzer3Top2",		"redPanzer3Lef1",		"redPanzer3Left2",
		"redPanzer3Bottom1",	"redPanzer3Bottom2",	"redPanzer3Right1",		"redPanzer3Right2",

		"greenPanzer4Top1",		"greenPanzer4Top2",		"greenPanzer4Lef1",		"greenPanzer4Left2",
		"greenPanzer4Bottom1",	"greenPanzer4Bottom2",	"greenPanzer4Right1",	"greenPanzer4Right2",
		"redPanzer4Top1",		"redPanzer4Top2",		"redPanzer4Lef1",		"redPanzer4Left2",
		"redPanzer4Bottom1",	"redPanzer4Bottom2",	"redPanzer4Right1",		"redPanzer4Right2",

		"redPanzer5Top1",		"redPanzer5Top2",		"redPanzer5Lef1",		"redPanzer5Left2",
		"redPanzer5Bottom1",	"redPanzer5Bottom2",	"redPanzer5Right1",		"redPanzer5Right2",
		"greenPanzer5Top1",		"greenPanzer5Top2",		"greenPanzer5Lef1",		"greenPanzer5Left2",
		"greenPanzer5Bottom1",	"greenPanzer5Bottom2",	"greenPanzer5Right1",	"greenPanzer5Right2",

		"redPanzer6Top1",		"redPanzer6Top2",		"redPanzer6Lef1",		"redPanzer6Left2",
		"redPanzer6Bottom1",	"redPanzer6Bottom2",	"redPanzer6Right1",		"redPanzer6Right2",
		"greenPanzer6Top1",		"greenPanzer6Top2",		"greenPanzer6Lef1",		"greenPanzer6Left2",
		"greenPanzer6Bottom1",	"greenPanzer6Bottom2",	"greenPanzer6Right1",	"greenPanzer6Right2",

		"redPanzer7Top1",		"redPanzer7Top2",		"redPanzer7Lef1",		"redPanzer7Left2",
		"redPanzer7Bottom1",	"redPanzer7Bottom2",	"redPanzer7Right1",		"redPanzer7Right2",
		"greenPanzer7Top1",		"greenPanzer7Top2",		"greenPanzer7Lef1",		"greenPanzer7Left2",
		"greenPanzer7Bottom1",	"greenPanzer7Bottom2",	"greenPanzer7Right1",	"greenPanzer7Right2",

		"redPanzer8Top1",		"redPanzer8Top2",		"redPanzer8Lef1",		"redPanzer8Left2",
		"redPanzer8Bottom1",	"redPanzer8Bottom2",	"redPanzer8Right1",		"redPanzer8Right2",
		"greenPanzer8Top1",		"greenPanzer8Top2",		"greenPanzer8Lef1",		"greenPanzer8Left2",
		"greenPanzer8Bottom1",	"greenPanzer8Bottom2",	"greenPanzer8Right1",	"greenPanzer8Right2"
	};
	auto pPanzerTextureAtlas = ResourceManager::loadTextureAtlas("PanzerTextureAtlas", "res/textures/tanks.png", std::move(panzerSubTexturesNames), 16, 16);
	auto pPanzerAnimatedSprite = ResourceManager::loadAnimatedSprite("PanzerAnimatedSprite", "PanzerTextureAtlas", "SpriteShader", 100, 100, "redPanzer3Top1");
	pPanzerAnimatedSprite->setPosition(glm::vec2(300, 400));
	std::vector<std::pair<std::string, uint64_t>> redPanzer3TopState;
	redPanzer3TopState.emplace_back(std::make_pair<std::string, uint64_t>("redPanzer3Top1", 20000000));
	redPanzer3TopState.emplace_back(std::make_pair<std::string, uint64_t>("redPanzer3Top2", 20000000));
	std::vector<std::pair<std::string, uint64_t>> redPanzer3LeftState;
	redPanzer3LeftState.emplace_back(std::make_pair<std::string, uint64_t>("redPanzer3Lef1", 20000000));
	redPanzer3LeftState.emplace_back(std::make_pair<std::string, uint64_t>("redPanzer3Left2", 20000000));
	std::vector<std::pair<std::string, uint64_t>> redPanzer3BottomState;
	redPanzer3BottomState.emplace_back(std::make_pair<std::string, uint64_t>("redPanzer3Bottom1", 20000000));
	redPanzer3BottomState.emplace_back(std::make_pair<std::string, uint64_t>("redPanzer3Bottom2", 20000000));
	std::vector<std::pair<std::string, uint64_t>> redPanzer3RightState;
	redPanzer3RightState.emplace_back(std::make_pair<std::string, uint64_t>("redPanzer3Right1", 20000000));
	redPanzer3RightState.emplace_back(std::make_pair<std::string, uint64_t>("redPanzer3Right2", 20000000));
	pPanzerAnimatedSprite->insertState("redPanzer3TopState", std::move(redPanzer3TopState));
	pPanzerAnimatedSprite->insertState("redPanzer3LeftState", std::move(redPanzer3LeftState));
	pPanzerAnimatedSprite->insertState("redPanzer3BottomState", std::move(redPanzer3BottomState));
	pPanzerAnimatedSprite->insertState("redPanzer3RightState", std::move(redPanzer3RightState));
	pPanzerAnimatedSprite->setState("redPanzer3TopState");
	m_pPanzer = std::make_unique<Panzer>(pPanzerAnimatedSprite, 0.0000001f, glm::vec2(100.f, 100.f));
	/*GLuint points_vbo = 0;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint texCoord_vbo = 0;
	glGenBuffers(1, &texCoord_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);*/

	return true;
}
