#ifndef BLUR_HPP
#define BLUR_HPP

#include "../Sources/Core/Effect.hpp"

class Blur : public Effect
{
    public:
        Blur()
		{
		}

        void apply(sf::RenderTexture const& input, sf::RenderTarget& output)
		{
			Shader& shader = getWorld().getApplication().getResource<Shader>("blur");
			shader.setParameter("texture", input.getTexture());
			applyShader(shader, output);
		}
};
#endif // BLUR_HPP
