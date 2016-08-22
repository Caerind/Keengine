#ifndef LIGHTSYSTEM_HPP
#define LIGHTSYSTEM_HPP

#include <assert.h>
#include <iostream>
#include <unordered_set>

#include "LTBL_DynamicQuadtree.hpp"
#include "LightPointEmission.hpp"
#include "LightDirectionEmission.hpp"
#include "LightShape.hpp"

namespace ltbl 
{
	
class LightSystem : sf::NonCopyable 
{
	public:
		struct Penumbra 
		{
			sf::Vector2f _source;
			sf::Vector2f _lightEdge;
			sf::Vector2f _darkEdge;
			float _lightBrightness;
			float _darkBrightness;

			float _distance;
		};

	public:
		float _directionEmissionRange;
		float _directionEmissionRadiusMultiplier;
		sf::Color _ambientColor;

		LightSystem();

		void create(const sf::FloatRect &rootRegion, const sf::Vector2u &imageSize, const sf::Texture &penumbraTexture, sf::Shader &unshadowShader, sf::Shader &lightOverShapeShader);

		void render(sf::RenderTarget& target);

		LightShape::Ptr createShape();
		void removeShape(const std::shared_ptr<LightShape> &lightShape);
	
		LightPointEmission::Ptr createLightPoint();
		void removeLight(LightPointEmission::Ptr pointEmissionLight);

		LightDirectionEmission::Ptr createLightDirection();
		void removeLight(LightDirectionEmission::Ptr directionEmissionLight);

		void trimLightPointEmissionQuadtree();
		void trimShapeQuadtree();

		friend class LightPointEmission;
		friend class LightDirectionEmission;
		friend class LightShape;

	private:
		void updateTextureSize(sf::Vector2u const& size);

		static void clear(sf::RenderTarget& target, sf::Color const& color);

		static void getPenumbrasPoint(std::vector<Penumbra> &penumbras, std::vector<int> &innerBoundaryIndices, std::vector<sf::Vector2f> &innerBoundaryVectors, std::vector<int> &outerBoundaryIndices, std::vector<sf::Vector2f> &outerBoundaryVectors, const sf::ConvexShape &shape, const sf::Vector2f &sourceCenter, float sourceRadius);
		static void getPenumbrasDirection(std::vector<Penumbra> &penumbras, std::vector<int> &innerBoundaryIndices, std::vector<sf::Vector2f> &innerBoundaryVectors, std::vector<int> &outerBoundaryIndices, std::vector<sf::Vector2f> &outerBoundaryVectors, const sf::ConvexShape &shape, const sf::Vector2f &sourceDirection, float sourceRadius, float sourceDistance);

	private:
		sf::RenderTexture _lightTempTexture, _emissionTempTexture, _antumbraTempTexture, _compositionTexture;
		DynamicQuadtree _shapeQuadtree;
		DynamicQuadtree _lightPointEmissionQuadtree;

		std::unordered_set<LightPointEmission::Ptr> _pointEmissionLights;
		std::unordered_set<LightDirectionEmission::Ptr> _directionEmissionLights;
		std::unordered_set<LightShape::Ptr> _lightShapes;

		sf::Shader* mUnshadowShader;
		sf::Shader* mLightOverShapeShader;
};

} // namespace ltbl

#endif // LIGHTSYSTEM_HPP