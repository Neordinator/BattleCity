#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream>
#include <chrono>

#include "BattleCity/Game.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Physics/PhysicsEngine.h"

static constexpr unsigned int SCALE = 3;
static constexpr unsigned int BLOCK_SIZE = 16;
glm::uvec2 g_windowSize(SCALE * 16 * BLOCK_SIZE, SCALE * 15 * BLOCK_SIZE);
std::unique_ptr<Game> gBattleCity = std::make_unique<Game>(g_windowSize);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
	g_windowSize.x = width;
	g_windowSize.y = height;
	gBattleCity->setWindowSize(g_windowSize);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		++gBattleCity->stateSwitcher;
		if (gBattleCity->stateSwitcher > 9)
		{
			gBattleCity->stateSwitcher ^= gBattleCity->stateSwitcher;
		}
	}
	gBattleCity->setKey(key, action);
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
	GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Void 0.01", nullptr, nullptr);
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
	std::cout << "Render: " << Render::Renderer::getRendererStr() << std::endl;
	std::cout << "OpenGL version: " << Render::Renderer::getVersionStr() << std::endl;

	Render::Renderer::setClearColor(0, 0, 0, 1);
	Render::Renderer::setDepthTest(true);

	{
		ResourceManager::setExecutablePath(argv[0]);
		Physics::PhysicsEngine::init();
		gBattleCity->init();

		glfwSetWindowSize(pWindow, static_cast<int>(3 * gBattleCity->getCurrentWidth()), static_cast<int>(3 * gBattleCity->getCurrentHeight()));

		auto lastTime = std::chrono::high_resolution_clock::now();
		// Loop until the user closes the window
		while (!glfwWindowShouldClose(pWindow))
		{
			// Poll for and process events
			glfwPollEvents();

			auto currentTime = std::chrono::high_resolution_clock::now();
			double duration = std::chrono::duration<double, std::milli>(currentTime - lastTime).count();
			lastTime = currentTime;
			//pBattleCityAnimatedSprite->update(duration);
			//pAnimeGirlAnimatedSprite->update(duration);
			gBattleCity->update(duration);
			Physics::PhysicsEngine::update(duration);
			// Render here
			Render::Renderer::clear();

			//pDefaultShaderProgram->use();
			//glBindVertexArray(vao);
			//tex->bind();

			//pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			//pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
			//glDrawArrays(GL_TRIANGLES, 0, 3);

			//pBattleCitySprite->render();
			//pBattleCityAnimatedSprite->render();
			//pAnimeGirlAnimatedSprite->render();
			gBattleCity->render();

			// Swap front and back buffers
			glfwSwapBuffers(pWindow);
		}
		gBattleCity = nullptr;
		ResourceManager::unloadAllResources();
	}//область видимости для вызова деструктора ResourceManager перед уничтожением контекста OpenGL
	glfwTerminate();
	return 0;
}
