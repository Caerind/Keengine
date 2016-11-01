#include "TextComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

TextComponent::TextComponent(Actor& actor)
	: SceneComponent(actor)
{
}

TextComponent::~TextComponent()
{
	onUnregister();
}

bool TextComponent::renderable() const
{
	return true;
}

void TextComponent::setFont(std::string const& font)
{
	if (getApplication().hasResource(font))
	{
		if (getApplication().isResourceLoaded(font))
		{
			mFont = font;
			mText.setFont(getApplication().getResource<ke::Font>(font));
		}
	}
}

void TextComponent::setFont(sf::Font& font)
{
	mText.setFont(font);
}

void TextComponent::setSize(unsigned int size)
{
	mText.setCharacterSize(size);
}

void TextComponent::setString(std::string const& text)
{
	mText.setString(text);
}

void TextComponent::setFillColor(sf::Color const& color)
{
	mText.setFillColor(color);
}

void TextComponent::setOutlineColor(sf::Color const& color)
{
	mText.setOutlineColor(color);
}

void TextComponent::setOutlineThickness(float thickness)
{
	mText.setOutlineThickness(thickness);
}

std::string TextComponent::getFont() const
{
	return mFont;
}

unsigned int TextComponent::getSize() const
{
	return mText.getCharacterSize();
}

std::string TextComponent::getString() const
{
	return mText.getString().toAnsiString();
}

sf::Color TextComponent::getFillColor() const
{
	return mText.getFillColor();
}

sf::Color TextComponent::getOutlineColor() const
{
	return mText.getOutlineColor();
}

float TextComponent::getOutlineThickness() const
{
	return mText.getOutlineThickness();
}

void TextComponent::serialize(Serializer& serializer)
{
	SceneComponent::serialize(serializer);
	serializer.save("font", getFont());
	serializer.save("size", getSize());
	serializer.save("string", getString());
	serializer.save("fillColor", getFillColor());
	serializer.save("outColor", getOutlineColor());
	serializer.save("outThick", getOutlineThickness());
}

bool TextComponent::deserialize(Serializer& serializer)
{
	std::string font;
	unsigned int size;
	std::string string;
	sf::Color fillColor;
	sf::Color outColor;
	float outThick;
	if (SceneComponent::deserialize(serializer)
		&& serializer.load("font", font)
		&& serializer.load("size", size)
		&& serializer.load("string", string)
		&& serializer.load("fillColor", fillColor)
		&& serializer.load("outColor", outColor)
		&& serializer.load("outThick", outThick))
	{
		setFont(font);
		setSize(size);
		setString(string);
		setFillColor(fillColor);
		setOutlineColor(outColor);
		setOutlineThickness(outThick);
		return true;
	}
	return false;
}

void TextComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mText, states);
}

} // namespace ke