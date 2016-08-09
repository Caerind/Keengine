#ifndef PIXELATE_HPP
#define PIXELATE_HPP

#include "../Sources/Core/Effect.hpp"

class Pixelate : public Effect
{
    public:
        Pixelate()
		{
		}

        void apply(sf::RenderTexture const& input, sf::RenderTarget& output)
		{
			Shader& shader = getWorld().getApplication().getResource<Shader>("pixel");
			shader.setParameter("texture", input.getTexture());
			applyShader(shader, output);
		}
};
#endif // PIXELATE_HPP
