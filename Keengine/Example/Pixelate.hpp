#ifndef PIXELATE_HPP
#define PIXELATE_HPP

#include "../Sources/Core/Effect.hpp"
#include "../Sources/Core/World.hpp"

class Pixelate : public Effect
{
    public:
        Pixelate()
		{
			const std::string fragmentShader = \
				"uniform sampler2D texture;" \
				"uniform float pixel_threshold;" \
				"void main()" \
				"{" \
				"	float factor = 1.0 / (pixel_threshold);" \
				"	vec2 pos = floor(gl_TexCoord[0].xy * factor + 0.5) / factor;" \
				"	gl_FragColor = texture2D(texture, pos) * gl_Color;" \
				"}";

			if (!getWorld().hasResource("pixelateShader"))
			{
				getWorld().createResource<Shader>("pixelateShader").loadFromMemory(fragmentShader, sf::Shader::Fragment);
			}
		}

        void apply(sf::RenderTexture const& input, sf::RenderTarget& output)
		{
			Shader& shader = getWorld().getApplication().getResource<Shader>("pixelateShader");
			shader.setParameter("texture", input.getTexture());
			applyShader(shader, output);
		}
};
#endif // PIXELATE_HPP
