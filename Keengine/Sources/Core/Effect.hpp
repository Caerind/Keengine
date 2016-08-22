#ifndef KE_EFFECT_HPP
#define KE_EFFECT_HPP

#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace ke
{

class World;
class Effect
{
    public:
        virtual ~Effect();

        static bool isSupported();

        virtual void apply(sf::RenderTexture const& input, sf::RenderTarget& output);

    protected:
        static void applyShader(sf::Shader const& shader, sf::RenderTarget& output);

		World& getWorld();
};

class Blur : public Effect
{
	public:
		Blur();

		void apply(sf::RenderTexture const& input, sf::RenderTarget& output);
};

class Pixelate : public Effect
{
	public:
		Pixelate();

		void apply(sf::RenderTexture const& input, sf::RenderTarget& output);
};

} // namespace ke

#endif // KE_EFFECT_HPP
