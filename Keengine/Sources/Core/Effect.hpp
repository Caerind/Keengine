#ifndef KE_EFFECT_HPP
#define KE_EFFECT_HPP

#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "../Application/Application.hpp"

namespace ke
{

class Scene;
class Effect
{
    public:
		Effect();
        virtual ~Effect();

        static bool isSupported();

        virtual void apply(sf::RenderTexture& texture);

		void setScene(Scene* scene);
		Scene* getScene();

		Log& getLog();
		Application& getApplication();

    protected:
        static void applyShader(sf::Shader const& shader, sf::RenderTarget& output);

		Scene* mScene;
};

class Blur : public Effect
{
	public:
		Blur();

		void apply(sf::RenderTexture& texture);
};

class Pixelate : public Effect
{
	public:
		Pixelate();

		void apply(sf::RenderTexture& texture);
};

} // namespace ke

#endif // KE_EFFECT_HPP
