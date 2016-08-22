#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "StateManager.hpp"
#include "PropertiesHolder.hpp"
#include "Window.hpp"

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#ifndef SFML_SYSTEM_ANDROID // Dont use imgui on Android
#include "../ExtLibs/imgui/imgui.h"
#include "../ExtLibs/imgui/imgui-SFML.h"
#endif

#include "../System/Log.hpp"
#include "../Maths/Math.hpp"
#include "../System/ScriptManager.hpp"

class Application
{
    public:
        using EventFunction = std::function<void(sf::Event const& event)> ;
        using UpdateFunction = std::function<void(sf::Time dt)>;
        using RenderFunction = std::function<void(sf::RenderTarget& target)>;

        static void init(std::string const& pathToSettings = "");
        static void quit();

        static void runState(std::string const& startState);

        static void setEventDefaultFunction(EventFunction event = [](sf::Event const& event){});
        static void setUpdateDefaultFunction(UpdateFunction update = [](sf::Time dt){});
        static void setRenderDefaultFunction(RenderFunction render = [](sf::RenderTarget& target){});
        static void runDefault();

        static void run();
        static void handleEvent();
        static void update(sf::Time dt);
        static void render();

        static sf::Time getRunningTime();
        static unsigned int getFPS();
        static bool isStateMode();

        static Application& instance();
        static Log& getLog();
		static Window& getWindow();
		static tgui::Gui& getGui();
		static PropertiesHolder& getValues();

		template <typename T> static std::shared_ptr<T> createGui(std::string const& name, std::string const& theme);
		// TODO : Create Gui without theme

        //
        // Audio
        //
        static void registerMusicFile(std::string const& id, std::string const& filename);
        static std::shared_ptr<sf::Music> playMusic(std::string const& id, bool loop = true, sf::Vector2f position = sf::Vector2f());
        static void removeMusic(std::string const& id);
        static std::shared_ptr<sf::Sound> playSound(std::string const& id, sf::Vector2f position = sf::Vector2f());
        static void playAudio();
        static void pauseAudio();
        static void stopAudio();
        static void setGlobalVolume(float volume);
        static void setMusicVolume(float volume);
        static void setSoundVolume(float volume);
        static float getGlobalVolume();
        static float getMusicVolume();
        static float getSoundVolume();
        static sf::SoundSource::Status getAudioStatus();

        //
        // Resources
        //
        template <typename T, typename ... Args>
        static T& createResource(std::string const& id, Args&& ... args);
        template <typename T>
        static T& getResource(std::string const& id);
        static bool hasResource(std::string const& id);
        static bool isResourceLoaded(std::string const& id);
        static void releaseResource(std::string const& id);
        static void releaseAllResources();

		// Script
		static void setScriptPath(std::string const& scriptPath);
		static std::string getScriptPath();
		static sel::State& script(std::string const& name);

        //
        // States
        //
        template <typename T>
        static void registerState(std::string const& className);
        static void pushState(std::string const& id);
        static void popState();
        static void clearStates();
        static std::size_t stateCount();

		//
		// Lang
		//
		static void setLang(std::string const& lang);
		static std::string getLang();
		static std::string inLang(std::string const& id);

        //
        // Window
        //
        static void create();
        static bool isOpen();
        static void close();
        static bool pollEvent(sf::Event& event);
        static void clear();
        static void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
        static void draw(const sf::Vertex* vertices, unsigned int vertexCount, sf::PrimitiveType type, const sf::RenderStates& states = sf::RenderStates::Default);
        static void display();
        static void setFullscreen(bool full);
        static bool isFullscreen();
        static void setVideoMode(sf::VideoMode const& videoMode);
        static sf::VideoMode getVideoMode();
        static void setStyle(sf::Uint32 style);
        static sf::Uint32 getStyle();
        static void setTitle(std::string const& title);
        static std::string getTitle();
        static void setVerticalSyncEnabled(bool enabled);
        static bool isVerticalSyncEnabled();
        static void setVisible(bool visible);
        static bool isVisible();
        static void setKeyRepeatEnabled(bool enabled);
        static bool isKeyRepeatEnabled();
        static void setJoystickThreshold(float threshold);
        static float getJoystickThreshold();
        static sf::Vector2u getSize();

        static void setView(const sf::View &view);
        static const sf::View& getView();
        static void setDefaultView();
        static const sf::View& getDefaultView();
        static sf::IntRect getViewport(const sf::View &view);

        static void setIcon(std::string const& filename);
        static std::string getIcon();

        static void setMousePosition2i(sf::Vector2i const& position);
        static void setMousePosition(sf::Vector2f const& position);
        static void setMousePositionMap(sf::Vector2f const& position);
        static void setMousePositionView(sf::Vector2f const& position, sf::View const& view);
        static sf::Vector2i getMousePosition2i();
        static sf::Vector2f getMousePosition();
        static sf::Vector2f getMousePositionMap();
        static sf::Vector2f getMousePositionView(sf::View const& view);
        static sf::Vector2i getTouchPosition2i(unsigned int touchIndex = 0);
        static sf::Vector2f getTouchPosition(unsigned int touchIndex = 0);
        static sf::Vector2f getTouchPositionMap(unsigned int touchIndex = 0);
        static sf::Vector2f getTouchPositionView(sf::View const& view, unsigned int touchIndex = 0);
        static void setPointerPosition2i(sf::Vector2i const& position);
        static void setPointerPosition(sf::Vector2f const& position);
        static void setPointerPositionMap(sf::Vector2f const& position);
        static void setPointerPositionView(sf::Vector2f const& position, sf::View const& view);
        static sf::Vector2i getPointerPosition2i(unsigned int touchIndex = 0);
        static sf::Vector2f getPointerPosition(unsigned int touchIndex = 0);
        static sf::Vector2f getPointerPositionMap(unsigned int touchIndex = 0);
        static sf::Vector2f getPointerPositionView(sf::View const& view, unsigned int touchIndex = 0);

        static void setMouseCursor(Window::MouseCursor cursor);
        static void hideMouseCursor();
        static void useDefaultMouseCursor();
        static void useCustomMouseCursor(sf::Texture* texture = nullptr, sf::Vector2f const& origin = sf::Vector2f(), sf::IntRect const& textureRect = sf::IntRect());
        static Window::MouseCursor getMouseCursor();
        static void setMouseCursorTexture(std::string const& filename, sf::IntRect rect = sf::IntRect());
        static void setMouseCursorTextureRect(sf::IntRect const& textureRect);
        static void setMouseCursorOrigin(sf::Vector2f const& origin);
        static std::string getMouseCursorTexture();
        static sf::IntRect getMouseCursorTextureRect();
        static sf::Vector2f getMouseCursorOrigin();

        static void screenshot();
        static void setScreenshotPath(std::string const& screenshotPath);
        static std::string getScreenshotPath();

        static void showDebugInfo(bool visible);
        static bool isDebugInfoVisible();
        template <typename T>
        static void setDebugInfo(std::string const& id, T value);
        static std::string getDebugInfo(std::string const& id);
        static void removeDebugInfo(std::string const& id);
        static void removeDebugInfos();

        static void setBackgroundColor(sf::Color color);
        static sf::Color getBackgroundColor();
        static void setBackgroundTexture(std::string const& filename, sf::IntRect rect = sf::IntRect());
        static std::string getBackgroundTexture();
        static sf::IntRect getBackgroundTextureRect();

    private:
        Application();
        ~Application();

        AudioManager mAudio;
        ResourceManager mResources;
        StateManager mStates;
        Window mWindow;
		tgui::Gui mGui;
		PropertiesHolder mProperties;
		ScriptManager mScripts;

        std::string mPathToSettings;
		std::string mScriptPath;
		std::string mLang;
        sf::Time mRunningTime;
        unsigned int mFps;
        bool mStateMode; // Default Mode Or State Mode
        std::string mIconFilename;
        std::string mCursorFilename;
        std::string mBackgroundFilename;

        EventFunction mEventDefaultFunction;
        UpdateFunction mUpdateDefaultFunction;
        RenderFunction mRenderDefaultFunction;
};

template<typename T>
std::shared_ptr<T> Application::createGui(std::string const& name, std::string const& theme)
{
	std::shared_ptr<T> widget = Application::getResource<Theme>(theme).create(name);
	instance().mGui.add(widget);
	return widget;
}

template <typename T, typename ... Args>
T& Application::createResource(std::string const& id, Args&& ... args)
{
    return instance().mResources.createResource<T>(id, std::forward<Args>(args)...);
}

template <typename T>
T& Application::getResource(std::string const& id)
{
    return instance().mResources.getResource<T>(id);
}

template <typename T>
void Application::registerState(std::string const& className)
{
    instance().mStates.registerState<T>(className);
}

template <typename T>
void Application::setDebugInfo(std::string const& id, T value)
{
    instance().mWindow.setDebugInfo<T>(id, value);
}

#endif // APPLICATION_HPP
