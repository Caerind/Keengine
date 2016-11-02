#ifndef KE_BACKGROUND_HPP
#define KE_BACKGROUND_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ke
{

class Background
{
	public:
		enum Usage
		{
			Color = 0,
			Scaled = 1,
			Repeated = 2
		};

	public:
		Background();

		void useColor(const sf::Color& color);
		void useScaledTexture(sf::Texture* texture, sf::IntRect rect = sf::IntRect());
		void useRepeatedTexture(sf::Texture* texture, sf::IntRect rect = sf::IntRect());

		void draw(sf::RenderTarget& target);

		sf::RectangleShape& getRectangle();
		sf::Sprite& getSprite();

		const sf::Color& getColor() const;
		const sf::IntRect& getTextureRect() const;
		std::size_t getUsage() const;

	private:
		void update();

	private:
		sf::Vector2u mSize;
		sf::RectangleShape mRectangle;
		sf::Sprite mSprite;
		std::size_t mUsage;
};

} // namespace ke

#endif // KE_BACKGROUND_HPP