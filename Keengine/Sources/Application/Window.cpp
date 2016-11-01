#include "Window.hpp"

namespace ke
{

Window::Window()
{
    setFullscreen(false);
    setTitle("");
    setVerticalSyncEnabled(false);
    mVisible = false;
    setKeyRepeatEnabled(true);
    mCursor = MouseCursor::Default;
    mScreenshotPath = "";
    mDebugInfoVisible = false;
    mVideoMode = sf::VideoMode(800,600);
    mStyle = sf::Style::Close;
    setJoystickThreshold(0.1f);
}

Window::~Window()
{
}

void Window::setDefaultView()
{
    setView(getDefaultView());
}

void Window::clear()
{
    sf::RenderWindow::clear();
	
	mBackground.draw(*this);
}

void Window::display()
{
    if (mCursor == MouseCursor::Custom)
    {
        setDefaultView();
        mCursorSprite.setPosition(getMousePosition());
        draw(mCursorSprite);
    }

    sf::RenderWindow::display();
}

void Window::create()
{
	#ifdef KEENGINE_ANDROID	
	sf::RenderWindow::create(sf::VideoMode::getDesktopMode(), "");
	sf::RenderTarget::initialize();
	#else
    if (isFullscreen())
    {
        sf::RenderWindow::create(sf::VideoMode::getFullscreenModes()[0], mTitle, sf::Style::Fullscreen);
    }
    else
    {
        sf::RenderWindow::create(mVideoMode, mTitle, mStyle);
    }

    sf::RenderTarget::initialize();
    setMouseCursor(mCursor);
    mVisible = true;
	#endif
}

void Window::create(sf::VideoMode videoMode, std::string const& title, sf::Uint32 style)
{
    mVideoMode = videoMode;
    mTitle = title;
    mStyle = style;
    create();
}

void Window::close()
{
    sf::RenderWindow::close();
    mVisible = false;
}

bool Window::isFullscreen() const
{
    return mFullscreen;
}

void Window::setFullscreen(bool full)
{
    mFullscreen = full;
    if (isOpen())
    {
        create();
    }
}

sf::VideoMode Window::getVideoMode() const
{
    return (isFullscreen()) ? sf::VideoMode::getFullscreenModes()[0] : mVideoMode;
}

void Window::setVideoMode(sf::VideoMode const& videoMode)
{
    mVideoMode = videoMode;
    if (isOpen())
    {
        create();
    }
}

sf::Uint32 Window::getStyle() const
{
    return mStyle;
}

void Window::setStyle(sf::Uint32 style)
{
    mStyle = style;
    if (isOpen() && !isFullscreen())
    {
        create();
    }
}

void Window::setTitle(std::string const& title)
{
    mTitle = title;
    sf::RenderWindow::setTitle(title);
}

std::string Window::getTitle() const
{
    return mTitle;
}

void Window::setVerticalSyncEnabled(bool enabled)
{
    sf::RenderWindow::setVerticalSyncEnabled(enabled);
    mVerticalSync = enabled;
}

bool Window::isVerticalSyncEnabled() const
{
    return mVerticalSync;
}

void Window::setVisible(bool visible)
{
    sf::RenderWindow::setVisible(visible);
    mVisible = visible;
}

bool Window::isVisible() const
{
    return mVisible;
}

void Window::setKeyRepeatEnabled(bool enabled)
{
    sf::RenderWindow::setKeyRepeatEnabled(enabled);
    mKeyRepeat = enabled;
}

bool Window::isKeyRepeatEnabled() const
{
    return mKeyRepeat;
}

void Window::setJoystickThreshold(float threshold)
{
    mJoystickThreshold = threshold;
    sf::RenderWindow::setJoystickThreshold(threshold);
}

float Window::getJoystickThreshold() const
{
    return mJoystickThreshold;
}

void Window::setIcon(sf::Image* image)
{
    if (image != nullptr)
    {
        sf::RenderWindow::setIcon(image->getSize().x, image->getSize().y, image->getPixelsPtr());
    }
    else
    {
        sf::RenderWindow::setIcon(0, 0, nullptr);
    }
}

void Window::setMousePosition2i(sf::Vector2i const& position)
{
    sf::Mouse::setPosition(position,*this);
}

void Window::setMousePosition(sf::Vector2f const& position)
{
    sf::Mouse::setPosition(static_cast<sf::Vector2i>(position),*this);
}

void Window::setMousePositionMap(sf::Vector2f const& position)
{
    sf::Mouse::setPosition(mapCoordsToPixel(position));
}

void Window::setMousePositionView(sf::Vector2f const& position, sf::View const& view)
{
    sf::Mouse::setPosition(mapCoordsToPixel(position,view));
}

sf::Vector2i Window::getMousePosition2i() const
{
    return sf::Mouse::getPosition(*this);
}

sf::Vector2f Window::getMousePosition() const
{
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this));
}

sf::Vector2f Window::getMousePositionMap() const
{
    return mapPixelToCoords(sf::Mouse::getPosition(*this));
}

sf::Vector2f Window::getMousePositionView(sf::View const& view)
{
    return mapPixelToCoords(sf::Mouse::getPosition(*this),view);
}

sf::Vector2i Window::getTouchPosition2i(unsigned int touchIndex) const
{
    return sf::Touch::getPosition(touchIndex,*this);
}

sf::Vector2f Window::getTouchPosition(unsigned int touchIndex) const
{
    return static_cast<sf::Vector2f>(sf::Touch::getPosition(touchIndex,*this));
}

sf::Vector2f Window::getTouchPositionMap(unsigned int touchIndex) const
{
    return mapPixelToCoords(sf::Touch::getPosition(touchIndex,*this));
}

sf::Vector2f Window::getTouchPositionView(sf::View const& view, unsigned int touchIndex)
{
    return mapPixelToCoords(sf::Touch::getPosition(touchIndex,*this),view);
}

void Window::setPointerPosition2i(sf::Vector2i const& position)
{
    #ifndef KEENGINE_ANDROID
    sf::Mouse::setPosition(position,*this);
    #endif
}

void Window::setPointerPosition(sf::Vector2f const& position)
{
    #ifndef KEENGINE_ANDROID
    sf::Mouse::setPosition(static_cast<sf::Vector2i>(position),*this);
    #endif
}

void Window::setPointerPositionMap(sf::Vector2f const& position)
{
    #ifndef KEENGINE_ANDROID
    sf::Mouse::setPosition(mapCoordsToPixel(position));
    #endif
}

void Window::setPointerPositionView(sf::Vector2f const& position, sf::View const& view)
{
    #ifndef KEENGINE_ANDROID
    sf::Mouse::setPosition(mapCoordsToPixel(position,view));
    #endif
}

sf::Vector2i Window::getPointerPosition2i(unsigned int touchIndex) const
{
    #ifdef KEENGINE_ANDROID
    return getTouchPosition2i(touchIndex);
    #else
    return getMousePosition2i();
    #endif
}

sf::Vector2f Window::getPointerPosition(unsigned int touchIndex) const
{
    #ifdef KEENGINE_ANDROID
    return getTouchPosition(touchIndex);
    #else
    return getMousePosition();
    #endif
}

sf::Vector2f Window::getPointerPositionMap(unsigned int touchIndex) const
{
    #ifdef KEENGINE_ANDROID
    return getTouchPositionMap(touchIndex);
    #else
    return getMousePositionMap();
    #endif
}

sf::Vector2f Window::getPointerPositionView(sf::View const& view, unsigned int touchIndex)
{
    #ifdef KEENGINE_ANDROID
    return getTouchPositionView(view,touchIndex);
    #else
    return getMousePositionView(view);
    #endif
}

void Window::setMouseCursor(MouseCursor cursor)
{
    switch (cursor)
    {
        case MouseCursor::None: hideMouseCursor(); break;
        case MouseCursor::Default: useDefaultMouseCursor(); break;
        case MouseCursor::Custom: useCustomMouseCursor(); break;
        default: break;
    }
}

void Window::hideMouseCursor()
{
    sf::RenderWindow::setMouseCursorVisible(false);
    mCursor = MouseCursor::None;
}

void Window::useDefaultMouseCursor()
{
    sf::RenderWindow::setMouseCursorVisible(true);
    mCursor = MouseCursor::Default;
}

void Window::useCustomMouseCursor(sf::Texture* texture, sf::Vector2f const& origin, sf::IntRect const& textureRect)
{
    sf::RenderWindow::setMouseCursorVisible(false);
    mCursor = MouseCursor::Custom;
    if (texture != nullptr)
    {
        setMouseCursorTexture(texture);
        if (textureRect != sf::IntRect())
        {
            setMouseCursorTextureRect(textureRect);
        }
        if (origin != sf::Vector2f())
        {
            setMouseCursorOrigin(origin);
        }
    }
    else
    {
        Log::instance() << Log::Error << std::string("Window : Can't use mouse texture");
    }
}

Window::MouseCursor Window::getMouseCursor() const
{
    return mCursor;
}

void Window::setMouseCursorTexture(sf::Texture* texture, sf::IntRect rect)
{
    if (texture != nullptr)
    {
        mCursorSprite.setTexture(*texture);
        mCursorSprite.setTextureRect(rect);
    }
    else
    {
        sf::Texture t;
        mCursorSprite.setTexture(t);
        mCursorSprite.setTextureRect(rect);
    }
}

void Window::setMouseCursorTextureRect(sf::IntRect const& textureRect)
{
    mCursorSprite.setTextureRect(textureRect);
}

void Window::setMouseCursorOrigin(sf::Vector2f const& origin)
{
    mCursorSprite.setOrigin(origin);
}

sf::IntRect Window::getMouseCursorTextureRect()
{
    return mCursorSprite.getTextureRect();
}

sf::Vector2f Window::getMouseCursorOrigin()
{
    return mCursorSprite.getOrigin();
}

void Window::screenshot()
{
    std::string file = mScreenshotPath + getTime("%Y-%m-%d_%H-%M-%S") + ".png";
    Log::instance() << Log::Info << std::string("Screenshot : " + file);
	sf::Texture texture;
	texture.create((unsigned int)getSize().x, (unsigned int)getSize().y);
	texture.update(*this);
	texture.copyToImage().saveToFile(file);
}

void Window::setScreenshotPath(std::string const& screenshotPath)
{
    mScreenshotPath = screenshotPath;
}

std::string Window::getScreenshotPath() const
{
    return mScreenshotPath;
}

void Window::showDebugInfo(bool visible)
{
    mDebugInfoVisible = visible;
}

bool Window::isDebugInfoVisible() const
{
    return mDebugInfoVisible;
}

std::string Window::getDebugInfo(std::string const& id) const
{
    auto itr = mDebugInfo.find(id);
    if (itr != mDebugInfo.end())
    {
        return itr->second;
    }
    return "";
}

void Window::removeDebugInfo(std::string const& id)
{
    auto itr = mDebugInfo.find(id);
    if (itr != mDebugInfo.end())
    {
        mDebugInfo.erase(itr);
    }
}

void Window::removeDebugInfos()
{
    mDebugInfo.clear();
}

std::size_t Window::getDebugInfoCount() const
{
    return mDebugInfo.size();
}

std::unordered_map<std::string,std::string>::iterator Window::getDebugInfo(std::size_t id)
{
    auto itr = mDebugInfo.begin();
    for (std::size_t i = 0; i < id; i++)
    {
        itr++;
    }
    return itr;
}

void Window::useBackgroundColor(const sf::Color& color)
{
	mBackground.useColor(color);
}

void Window::useBackgroundScaledTexture(sf::Texture* texture, sf::IntRect rect)
{
	mBackground.useScaledTexture(texture, rect);
}

void Window::useBackgroundRepeatedTexture(sf::Texture* texture, sf::IntRect rect)
{
	mBackground.useRepeatedTexture(texture, rect);
}

sf::RectangleShape& Window::getBackgroundRectangle()
{
	return mBackground.getRectangle();
}

sf::Sprite& Window::getBackgroundSprite()
{
	return mBackground.getSprite();
}

const sf::Color& Window::getBackgroundColor() const
{
	return mBackground.getColor();
}

const sf::IntRect& Window::getBackgroundTextureRect() const
{
	return mBackground.getTextureRect();
}

std::size_t Window::getBackgroundUsage() const
{
	return mBackground.getUsage();
}

} // namespace ke