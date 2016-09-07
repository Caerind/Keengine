#ifndef KE_LIGHTSHAPECOMPONENT_HPP
#define KE_LIGHTSHAPECOMPONENT_HPP

#include "../Core/SceneComponent.hpp"

#include "../ExtLibs/LTBL2/LightShape.hpp"

namespace ke
{

class LightShapeComponent : public SceneComponent
{
	public:
		typedef std::shared_ptr<LightShapeComponent> Ptr;

		LightShapeComponent(Actor& actor);

		void onRegister();
		void onUnregister();

		void setPointCount(std::size_t points);
		std::size_t getPointCount() const;

		void setPoint(std::size_t index, sf::Vector2f const& point);
		sf::Vector2f getPoint(std::size_t index) const;

		void setOutlineThickness(float thickness);
		float getOutlineThicnkess() const;

		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

	private:
		virtual void onTransformUpdated();

	private:
		ltbl::LightShape::Ptr mLightShape;
};

} // namespace ke

#endif // KE_LIGHTSHAPECOMPONENT_HPP
