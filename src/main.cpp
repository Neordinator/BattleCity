// СТОРОННИЕ
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

// ИЗ КОРОБКИ
#include <iostream>
#include <chrono>

// СОБСТВЕННЫЕ
//#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"

GLfloat point[] = {
	0.0f, 50.0f, 0.0f,
	50.0f, -50.0f, 0.0f,
	-50.0f, -50.0f, 0.0f
};
GLfloat colors[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};
GLfloat texCoord[] = {
	0.5f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f
};

glm::vec2 windowSize(640, 480);

unsigned int stateSwitcher = 0;

/*int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;*/

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
	/*WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);*/
	windowSize.x = width;
	windowSize.y = height;
	glViewport(0, 0, windowSize.x, windowSize.y);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		++stateSwitcher;
		if (stateSwitcher > 9)
		{
			stateSwitcher ^= stateSwitcher;
		}
	}
}

int main(int argc, char** argv)
{
	// Initialize the Library
	if (!glfwInit())
	{
		std::cout << "glfwInit failed!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
	//GLFWwindow* pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Void 0.01", nullptr, nullptr);
	GLFWwindow* pWindow = glfwCreateWindow(windowSize.x, windowSize.y, "Void 0.01", nullptr, nullptr);
	if (!pWindow)
	{
		std::cout << "glfwCreateWindow failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
	glfwSetKeyCallback(pWindow, glfwKeyCallback);

	// Make the window's context current
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGL())
	{
		std::cout << "Can not load GLAD!" << std::endl;
	}
	std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	//std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

	glClearColor(1, 1, 0, 1);

	{
		ResourceManager resourceManager(argv[0]);

		auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
		if (!pDefaultShaderProgram)
		{
			std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
			return -1;
		}
		auto pSpriteShaderProgram = resourceManager.loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
		if (!pDefaultShaderProgram)
		{
			std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
			return -1;
		}

		auto tex = resourceManager.loadTexture("BattleCityTexture", "res/textures/BattleCity_16x16.png");

		std::vector<std::string> battleCitySubTexturesNames = {
			"block", "topBlock", "bottomBlock", "leftBlock", "rightBlock", "topLeftBlock", "topRightBlock", "bottomLeftBlock", "bottomRightBlock",
			"beton", "topBeton", "bottomBeton", "leftBeton", "rightBeton", "topLeftBeton", "topRightBeton", "bottomLeftBeton", "bottomRightBeton",
			"water1", "water2", "water3", "trees", "ice", "wall", "eagle", "deadEagle", "nothing", "respawn1", "respawn2", "respawn3", "respawn4"
		};
		auto pBattleCityTextureAtlas = resourceManager.loadTextureAtlas("BattleCityTextureAtlas", "res/textures/BattleCity_16x16.png", std::move(battleCitySubTexturesNames), 16, 16);
		auto pBattleCitySprite = resourceManager.loadSprite("BattleCitySprite", "BattleCityTextureAtlas", "SpriteShader", 100, 100, "block");
		pBattleCitySprite->setPosition(glm::vec2(300, 100));
		auto pBattleCityAnimatedSprite = resourceManager.loadAnimatedSprite("BattleCityAnimatedSprite", "BattleCityTextureAtlas", "SpriteShader", 100, 100, "beton");
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
		auto pAnimeGirlTextureAtlas = resourceManager.loadTextureAtlas("AnimeGirlTextureAtlas", "res/textures/AnimeGirlPortrait.png", std::move(animeGirlSubTexturesNames), 106, 106);
		auto pAnimeGirlSprite = resourceManager.loadSprite("AnimeGirlSprite", "AnimeGirlTextureAtlas", "SpriteShader", 100, 100, "hurt1");
		pAnimeGirlSprite->setPosition(glm::vec2(300, 200));
		auto pAnimeGirlAnimatedSprite = resourceManager.loadAnimatedSprite("AnimeGirlAnimatedSprite", "AnimeGirlTextureAtlas", "SpriteShader", 100, 100, "sad1");
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
		pAnimeGirlAnimatedSprite->setState("normalState");



		GLuint points_vbo = 0;
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
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		pDefaultShaderProgram->use();
		pDefaultShaderProgram->setInt("tex", 0);

		glm::mat4 modelMatrix_1 = glm::mat4(1.f);
		modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.0f, 0.0f));

		glm::mat4 modelMatrix_2 = glm::mat4(1.f);
		modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.0f, 0.0f));

		glm::mat4 projectionMatrix = glm::ortho(0.0f, windowSize.x, 0.0f, windowSize.y, -100.0f, 100.0f);

		pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

		pSpriteShaderProgram->use();
		pSpriteShaderProgram->setInt("tex", 0);
		pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

		auto lastTime = std::chrono::high_resolution_clock::now();
		// Loop until the user closes the window
		while (!glfwWindowShouldClose(pWindow))
		{
			switch (stateSwitcher)
			{
			case 0:
				pAnimeGirlAnimatedSprite->setState("normalState");
				break;
			case 1:
				pAnimeGirlAnimatedSprite->setState("hurtState");
				break;
			case 2:
				pAnimeGirlAnimatedSprite->setState("victoryState");
				break;
			case 3:
				pAnimeGirlAnimatedSprite->setState("afraidState");
				break;
			case 4:
				pAnimeGirlAnimatedSprite->setState("sadState");
				break;
			case 5:
				pAnimeGirlAnimatedSprite->setState("angryState");
				break;
			case 6:
				pAnimeGirlAnimatedSprite->setState("depressedState");
				break;
			case 7:
				pAnimeGirlAnimatedSprite->setState("enragedState");
				break;
			case 8:
				pAnimeGirlAnimatedSprite->setState("happyState");
				break;
			case 9:
				pAnimeGirlAnimatedSprite->setState("ecstaticState");
				break;

			}
			auto currentTime = std::chrono::high_resolution_clock::now();
			uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
			lastTime = currentTime;
			pBattleCityAnimatedSprite->update(duration);
			pAnimeGirlAnimatedSprite->update(duration);
			// Render here
			glClear(GL_COLOR_BUFFER_BIT);

			pDefaultShaderProgram->use();
			glBindVertexArray(vao);
			tex->bind();

			pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			pBattleCitySprite->render();
			pBattleCityAnimatedSprite->render();
			pAnimeGirlAnimatedSprite->render();

			// Swap front and back buffers
			glfwSwapBuffers(pWindow);

			// Poll for and process events
			glfwPollEvents();
		}
	}//область видимости для вызова деструктора ResourceManager перед уничтожением контекста OpenGL
	glfwTerminate();
	return 0;
}
