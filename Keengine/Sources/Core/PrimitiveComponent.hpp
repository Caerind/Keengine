#ifndef PRIMITIVECOMPONENT_HPP
#define PRIMITIVECOMPONENT_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include "SceneComponent.hpp"

class PrimitiveComponent : public SceneComponent
{
    public:
        PrimitiveComponent();
        virtual ~PrimitiveComponent();
		
		void setVisible(bool visible);
		bool isVisible() const;

		virtual void render(sf::RenderTarget& target);
		
	protected:
		bool mVisible;
};

#endif // PRIMITIVECOMPONENT_HPP
