#ifndef BLUR_HPP
#define BLUR_HPP

#include "../Sources/Core/Effect.hpp"
#include "../Sources/Core/World.hpp"

class Blur : public Effect
{
    public:
        Blur()
		{
			const std::string fragmentShader = \
				"uniform sampler2D texture;" \
				"uniform float blur_radius;" \
				"void main()" \
			    "{" \
				"   vec2 offx = vec2(blur_radius, 0.0);" \
				"	vec2 offy = vec2(0.0, blur_radius);" \
				"	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy)               * 4.0 +" \
				"		texture2D(texture, gl_TexCoord[0].xy - offx)        * 2.0 +" \
				"		texture2D(texture, gl_TexCoord[0].xy + offx)        * 2.0 +" \
				"		texture2D(texture, gl_TexCoord[0].xy - offy)        * 2.0 +" \
				"		texture2D(texture, gl_TexCoord[0].xy + offy)        * 2.0 +" \
				"		texture2D(texture, gl_TexCoord[0].xy - offx - offy) * 1.0 +" \
				"		texture2D(texture, gl_TexCoord[0].xy - offx + offy) * 1.0 +" \
				"		texture2D(texture, gl_TexCoord[0].xy + offx - offy) * 1.0 +" \
				"		texture2D(texture, gl_TexCoord[0].xy + offx + offy) * 1.0;" \
				"	gl_FragColor = gl_Color * (pixel / 16.0);" \
				"}";

			if (!getWorld().hasResource("blurShader"))
			{
				getWorld().createResource<Shader>("blurShader").loadFromMemory(fragmentShader, sf::Shader::Fragment);
			}
		}

        void apply(sf::RenderTexture const& input, sf::RenderTarget& output)
		{
			Shader& shader = getWorld().getResource<Shader>("blurShader");
			shader.setParameter("texture", input.getTexture());
			applyShader(shader, output);
		}
};
#endif // BLUR_HPP
