cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME VoidEngine)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/System/Timer.h
	src/System/Timer.cpp
	src/Physics/PhysicsEngine.h
	src/Physics/PhysicsEngine.cpp
	src/Renderer/VertexBuffer.h
	src/Renderer/VertexBuffer.cpp
	src/Renderer/IndexBuffer.h
	src/Renderer/IndexBuffer.cpp
	src/Renderer/VertexBufferLayout.h
	src/Renderer/VertexBufferLayout.cpp
	src/Renderer/VertexArray.h
	src/Renderer/VertexArray.cpp
	src/Renderer/Renderer.h
	src/Renderer/Renderer.cpp
	src/Renderer/ShaderProgram.h
	src/Renderer/ShaderProgram.cpp
	src/Renderer/Texture2D.h
	src/Renderer/Texture2D.cpp
	src/Renderer/Sprite.h
	src/Renderer/Sprite.cpp
	src/Renderer/SpriteAnimator.h
	src/Renderer/SpriteAnimator.cpp
	src/Resources/ResourceManager.h
	src/Resources/ResourceManager.cpp
	src/BattleCity/GameObjects/IGameObject.h
	src/BattleCity/GameObjects/IGameObject.cpp
	src/BattleCity/GameObjects/Panzer.h
	src/BattleCity/GameObjects/Panzer.cpp
	src/BattleCity/GameObjects/Bullet.h
	src/BattleCity/GameObjects/Bullet.cpp
	src/BattleCity/GameObjects/BrickWall.h
	src/BattleCity/GameObjects/BrickWall.cpp
	src/BattleCity/GameObjects/BetonWall.h
	src/BattleCity/GameObjects/BetonWall.cpp
	src/BattleCity/GameObjects/Eagle.h
	src/BattleCity/GameObjects/Eagle.cpp
	src/BattleCity/GameObjects/Water.h
	src/BattleCity/GameObjects/Water.cpp
	src/BattleCity/GameObjects/Trees.h
	src/BattleCity/GameObjects/Trees.cpp
	src/BattleCity/GameObjects/Ice.h
	src/BattleCity/GameObjects/Ice.cpp
	src/BattleCity/GameObjects/Border.h
	src/BattleCity/GameObjects/Border.cpp
	src/Resources/stb_image.h

	src/BattleCity/Game.h
	src/BattleCity/Game.cpp
	
	src/BattleCity/AIComponent.h
	src/BattleCity/AIComponent.cpp
	
	src/BattleCity/GameStates/IGameState.h
	src/BattleCity/GameStates/StartScreen.h
	src/BattleCity/GameStates/StartScreen.cpp
	src/BattleCity/GameStates/Level.h
	src/BattleCity/GameStates/Level.cpp
)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

include_directories(external/rapidjson/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)