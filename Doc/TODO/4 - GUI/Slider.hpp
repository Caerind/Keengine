#ifndef SGUI_SLIDER_HPP
#define SGUI_SLIDER_HPP

/*

namespace SGUI
{

class Slider : public Widget, public Sprite, public Callback
{
    public:
        typedef std::shared_ptr<Slider> Ptr;

        enum Textures
        {
            Normal = 0,
            Active = 1,
            Disabled = 2,
            Count = 3,
        };

    public:
        Slider();

        void setInterval(float a, float b);

        void setCursorSize(sf::Vector2f cursorSize);
        void setCursorColor(size_t index, sf::Color color = sf::Color(0.123,0.123,0.123,0.123));

        void useAxisX();
        void useAxisY();

        float getValueFloat() const;
        int getValueInt() const;
        std::string getValueStringFloat() const;
        std::string getValueStringInt() const;

        template<typename T>
        void setValue(T value);

        virtual void update();

        virtual void handleEvent(sf::Event const& event, sf::RenderWindow& RenderWindow);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::RectangleShape mShape;
        sf::Vector2f mInterval;
        float mValue;
        bool mMoving;
        bool mUseAxisX;
        std::array<sf::Color,Textures::Count> mColors;
};

template <typename T>
void Slider::setValue(T value)
{
    mValue = static_cast<float>(value);
    float x = mSprite.getGlobalBounds().width * mValue / (mInterval.y - mInterval.x);
    x = std::min(x,mSprite.getGlobalBounds().width - mShape.getGlobalBounds().width / 2);
    x = std::max(x,mShape.getGlobalBounds().width / 2);
    mShape.setPosition(x,mShape.getPosition().y);
}

} // namespace SGUI

*/

#endif // SGUI_SLIDER_HPP
