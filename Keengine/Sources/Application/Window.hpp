#ifndef KE_WINDOW_HPP
#define KE_WINDOW_HPP

#include "../Config.hpp"

#include <unordered_map>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Touch.hpp>

#include "../System/Background.hpp"
#include "../System/Log.hpp"
#include "../System/Time.hpp"

namespace ke
{

class Window : public sf::RenderWindow
{
    public:
        Window();
        ~Window();

        void setDefaultView();

        void clear();
        void display();

        //
        // SETTINGS
        //
        void create();
        void create(sf::VideoMode videoMode, std::string const& title, sf::Uint32 style = sf::Style::Close);
        void close();
        bool isFullscreen() const;
        void setFullscreen(bool full);
        sf::VideoMode getVideoMode() const;
        void setVideoMode(sf::VideoMode const& videoMode);
        sf::Uint32 getStyle() const;
        void setStyle(sf::Uint32 style);

        void setTitle(std::string const& title);
        std::string getTitle() const;

        void setVerticalSyncEnabled(bool enabled);
        bool isVerticalSyncEnabled() const;

        void setVisible(bool visible);
        bool isVisible() const;

        void setKeyRepeatEnabled(bool enabled);
        bool isKeyRepeatEnabled() const;

        void setJoystickThreshold(float threshold);
        float getJoystickThreshold() const;

        //
        // ICON
        //
        void setIcon(sf::Image* image);

        //
        // MOUSE
        //
        void setMousePosition2i(sf::Vector2i const& position);
        void setMousePosition(sf::Vector2f const& position);
        void setMousePositionMap(sf::Vector2f const& position);
        void setMousePositionView(sf::Vector2f const& position, sf::View const& view);
        sf::Vector2i getMousePosition2i() const;
        sf::Vector2f getMousePosition() const;
        sf::Vector2f getMousePositionMap() const;
        sf::Vector2f getMousePositionView(sf::View const& view);

        //
        // TOUCH
        //
        sf::Vector2i getTouchPosition2i(unsigned int touchIndex = 0) const;
        sf::Vector2f getTouchPosition(unsigned int touchIndex = 0) const;
        sf::Vector2f getTouchPositionMap(unsigned int touchIndex = 0) const;
        sf::Vector2f getTouchPositionView(sf::View const& view, unsigned int touchIndex = 0);

        //
        // Pointer
        //
        void setPointerPosition2i(sf::Vector2i const& position);
        void setPointerPosition(sf::Vector2f const& position);
        void setPointerPositionMap(sf::Vector2f const& position);
        void setPointerPositionView(sf::Vector2f const& position, sf::View const& view);
        sf::Vector2i getPointerPosition2i(unsigned int touchIndex = 0) const;
        sf::Vector2f getPointerPosition(unsigned int touchIndex = 0) const;
        sf::Vector2f getPointerPositionMap(unsigned int touchIndex = 0) const;
        sf::Vector2f getPointerPositionView(sf::View const& view, unsigned int touchIndex = 0);

        //
        // CURSOR
        //
        enum MouseCursor
        {
            Default,
            None,
            Custom,
        };

        void setMouseCursor(MouseCursor cursor);
        void hideMouseCursor();
        void useDefaultMouseCursor();
        void useCustomMouseCursor(sf::Texture* texture = nullptr, sf::Vector2f const& origin = sf::Vector2f(), sf::IntRect const& textureRect = sf::IntRect());
        MouseCursor getMouseCursor() const;

        void setMouseCursorTexture(sf::Texture* texture, sf::IntRect rect = sf::IntRect());
        void setMouseCursorTextureRect(sf::IntRect const& textureRect);
        void setMouseCursorOrigin(sf::Vector2f const& origin);
        sf::IntRect getMouseCursorTextureRect();
        sf::Vector2f getMouseCursorOrigin();

        //
        // SCREENSHOT
        //
        void screenshot();
        void setScreenshotPath(std::string const& screenshotPath);
        std::string getScreenshotPath() const;

        //
        // DEBUG INFO
        //
        void showDebugInfo(bool visible);
        bool isDebugInfoVisible() const;
        template <typename T>
        void setDebugInfo(std::string const& id, T value);
        std::string getDebugInfo(std::string const& id) const;
        void removeDebugInfo(std::string const& id);
        void removeDebugInfos();
        std::size_t getDebugInfoCount() const;
        std::unordered_map<std::string,std::string>::iterator getDebugInfo(std::size_t id);

        //
        // BACKGROUND
        //
		void useBackgroundColor(const sf::Color& color);
		void useBackgroundScaledTexture(sf::Texture* texture, sf::IntRect rect = sf::IntRect());
		void useBackgroundRepeatedTexture(sf::Texture* texture, sf::IntRect rect = sf::IntRect());
		sf::RectangleShape& getBackgroundRectangle();
		sf::Sprite& getBackgroundSprite();
		const sf::Color& getBackgroundColor() const;
		const sf::IntRect& getBackgroundTextureRect() const;
		std::size_t getBackgroundUsage() const;

    protected:
        bool mFullscreen;
        std::string mTitle;
        bool mVerticalSync;
        bool mVisible;
        bool mKeyRepeat;
        sf::VideoMode mVideoMode;
        sf::Uint32 mStyle;
        float mJoystickThreshold;

        MouseCursor mCursor;
        sf::Sprite mCursorSprite;

        std::string mScreenshotPath;

        bool mDebugInfoVisible;
        std::unordered_map<std::string,std::string> mDebugInfo;

		Background mBackground; // TODO : Test it
};

template <typename T>
void Window::setDebugInfo(std::string const& id, T value)
{
    mDebugInfo[id] = std::to_string(value);
}

template <>
inline void Window::setDebugInfo<const std::string&>(std::string const& id, const std::string& value)
{
    mDebugInfo[id] = value;
}

template <>
inline void Window::setDebugInfo<std::string>(std::string const& id, std::string value)
{
    mDebugInfo[id] = value;
}

template <>
inline void Window::setDebugInfo<const char*>(std::string const& id, const char* value)
{
    mDebugInfo[id] = value;
}

template <>
inline void Window::setDebugInfo<char>(std::string const& id, char value)
{
    mDebugInfo[id] = {value};
}

template <>
inline void Window::setDebugInfo<bool>(std::string const& id, bool value)
{
    mDebugInfo[id] = (value) ? "true" : "false";
}

} // namespace ke

#endif // KE_WINDOW_HPP
