#pragma once

#include <memory>
#include <array>

#include "../IGameObject.h"
#include "../../Renderer/Sprite.h"

namespace Render
{
	class Sprite;
}
class Border : public IGameObject
{
public:
	Border(const glm::vec2&, const glm::vec2&, const float, const float);

	virtual void render() const override;

private:
	std::shared_ptr<Render::Sprite> m_sprite;
};