#ifndef KE_CAMERACOMPONENT_HPP
#define KE_CAMERACOMPONENT_HPP

#include "../Core/SceneComponent.hpp"
#include <SFML/Graphics/View.hpp>

namespace ke
{

class CameraComponent : public SceneComponent
{
    public:
		typedef std::shared_ptr<CameraComponent> Ptr;

		TYPE(CameraComponent)

        CameraComponent(Actor& actor);

        sf::View& getView();

		void onTransformUpdated();
};

} // namespace ke

#endif // KE_CAMERACOMPONENT_HPP
