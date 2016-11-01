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
		virtual ~CameraComponent();

        sf::View& getView();

		void onTransformNotified();

		virtual void serialize(Serializer& serializer);
		virtual bool deserialize(Serializer& serializer);
};

} // namespace ke

#endif // KE_CAMERACOMPONENT_HPP
