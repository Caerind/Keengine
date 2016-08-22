#ifndef KE_PRIMITIVECOMPONENT_HPP
#define KE_PRIMITIVECOMPONENT_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include "SceneComponent.hpp"

namespace ke
{

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

} // namespace ke

#endif // KE_PRIMITIVECOMPONENT_HPP
