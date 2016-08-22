#include "Effect.hpp"
#include "World.hpp"

namespace ke
{

Effect::~Effect()
{
}

bool Effect::isSupported()
{
    return sf::Shader::isAvailable();
}

void Effect::apply(sf::RenderTexture const& input, sf::RenderTarget& output)
{
}

void Effect::applyShader(sf::Shader const& shader, sf::RenderTarget& output)
{
    sf::Vector2f outputSize = static_cast<sf::Vector2f>(output.getSize());

	sf::VertexArray vertices(sf::TrianglesStrip, 4);
	vertices[0] = sf::Vertex(sf::Vector2f(0, 0),            sf::Vector2f(0, 1));
	vertices[1] = sf::Vertex(sf::Vector2f(outputSize.x, 0), sf::Vector2f(1, 1));
	vertices[2] = sf::Vertex(sf::Vector2f(0, outputSize.y), sf::Vector2f(0, 0));
	vertices[3] = sf::Vertex(sf::Vector2f(outputSize),      sf::Vector2f(1, 0));

	sf::RenderStates states;
	states.shader 	 = &shader;
	states.blendMode = sf::BlendNone;

	output.draw(vertices, states);
}

World& Effect::getWorld()
{
	return World::instance();
}

Blur::Blur()
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

void Blur::apply(sf::RenderTexture const& input, sf::RenderTarget& output)
{
	Shader& shader = getWorld().getResource<Shader>("blurShader");
	shader.setUniform("texture", input.getTexture());
	applyShader(shader, output);
}

Pixelate::Pixelate()
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

void Pixelate::apply(sf::RenderTexture const& input, sf::RenderTarget& output)
{
	Shader& shader = getWorld().getApplication().getResource<Shader>("pixelateShader");
	shader.setUniform("texture", input.getTexture());
	applyShader(shader, output);
}

} // namespace ke