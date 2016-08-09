#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

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

#endif // EFFECT_HPP
