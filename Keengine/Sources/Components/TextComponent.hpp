#ifndef KE_TEXTCOMPONENT_HPP
#define KE_TEXTCOMPONENT_HPP

#include "../Core/PrimitiveComponent.hpp"

#include <SFML/Graphics/Text.hpp>

namespace ke
{

class TextComponent : public PrimitiveComponent
{
	public:
		TextComponent();

		void render(sf::RenderTarget& target);

		void setFont(std::string const& font);
		void setFont(sf::Font& font);
		void setSize(unsigned int size);
		void setString(std::string const& text);
		void setFillColor(sf::Color const& color);
		void setOutlineColor(sf::Color const& color);
		void setOutlineThickness(float thickness);

		unsigned int getSize() const;
		std::string getString() const;
		sf::Color getFillColor() const;
		sf::Color getOutlineColor() const;
		float getOutlineThickness() const;

	private:
		sf::Text mText;
};

} // namespace ke

#endif // KE_TEXTCOMPONENT_HPP
