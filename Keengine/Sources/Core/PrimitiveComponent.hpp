#ifndef PRIMITIVECOMPONENT_HPP
#define PRIMITIVECOMPONENT_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include "SceneComponent.hpp"

class PrimitiveComponent : public SceneComponent
{
    public:
        PrimitiveComponent();
        virtual ~PrimitiveComponent();
		
		bool isRenderable() const;
		virtual void render(sf::RenderTarget& target);
		
	protected:
		bool mRenderable;
};

#endif // PRIMITIVECOMPONENT_HPP
