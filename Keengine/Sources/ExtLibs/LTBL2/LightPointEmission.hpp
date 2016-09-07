#ifndef LIGHTPOINTEMISSION_HPP
#define LIGHTPOINTEMISSION_HPP

#include <assert.h>
#include <memory>

#include "LTBL_QuadtreeOccupant.hpp"

namespace ltbl 
{
	
class LightPointEmission : public QuadtreeOccupant 
{
	public:
		typedef std::shared_ptr<LightPointEmission> Ptr;

		sf::Sprite _emissionSprite;
		sf::Vector2f _localCastCenter;

		float _sourceRadius;

		float _shadowOverExtendMultiplier;

		bool _use;

		LightPointEmission()
			: _localCastCenter(0.0f, 0.0f), _sourceRadius(8.0f), _shadowOverExtendMultiplier(1.4f), _use(true)
		{}

		sf::FloatRect getAABB() const {
			return _emissionSprite.getGlobalBounds();
		}

		void render(const sf::View &view, sf::RenderTexture &lightTempTexture, sf::RenderTexture &emissionTempTexture, sf::RenderTexture &antumbraTempTexture, const std::vector<QuadtreeOccupant*> &shapes, sf::Shader &unshadowShader, sf::Shader &lightOverShapeShader);
};

} // namespace ltbl

#endif // LIGHTPOINTEMISSION_HPP