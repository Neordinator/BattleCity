#pragma once

#include <memory>
#include <array>

#include "../IGameObject.h"
#include "../../Renderer/Sprite.h"

namespace Render
{
	class Sprite;
}
class Eagle : public IGameObject
{
public:
	enum class EEagleState : uint8_t
	{
		Alive = 0,
		Dead
	};
	Eagle(const glm::vec2&, const glm::vec2&, const float, const float);

	virtual void render() const override;
	void update(const double) override;

private:
	std::array<std::shared_ptr<Render::Sprite>, 2> m_sprite;
	EEagleState m_eCurrentState;
};