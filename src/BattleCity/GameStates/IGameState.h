#pragma once

#include <array>

class IGameState
{
public:
	virtual ~IGameState() = default;

	virtual void render() const = 0;
	virtual void update(const double) = 0;
	virtual unsigned int getStateWidth() const = 0;
	virtual unsigned int getStateHeight() const = 0;
	virtual void processInput(const std::array<bool, 349>&) {};
};
