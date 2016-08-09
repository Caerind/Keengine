#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP

#include "../Core/SceneComponent.hpp"
#include <SFML/Graphics/View.hpp>

class CameraComponent : public SceneComponent
{
    public:
        CameraComponent();
		~CameraComponent();

        sf::View& getView();

		void onChangedTransform();

	protected:
		sf::View mCamera;
};

#endif // NCAMERACOMPONENT_HPP
