#include "Application.hpp"
#include "../System/IniParser.hpp"

void Application::init(std::string const& pathToSettings)
{
    instance().mPathToSettings = pathToSettings;
    {
        IniParser& parser = createResource<IniParser>("application_settings");
        if (!parser.loadFromFile(instance().mPathToSettings + "application_settings.ini"))
        {
            Log::instance() << Log::Warning << "Application Settings can't be loaded, at : " + pathToSettings + "application_settings.ini";

            parser["log_console"] = true;
            parser["log_file"] = "";
            parser["log_url"] = "";
            parser["global_volume"] = 100.f;
            parser["music_volume"] = 100.f;
            parser["sound_volume"] = 100.f;
            parser["fullscreen"] = false;
            parser["width"] = 800;
            parser["height"] = 600;
            parser["style"] = static_cast<int>(sf::Style::Close);
            parser["title"] = "NodeEngine";
            parser["vsync"] = false;
            parser["key_repeat"] = false;
            parser["joystick_threshold"] = 0.1f;
            parser["icon"] = "";
            parser["cursor"] = static_cast<int>(Window::MouseCursor::Default);
            parser["cursor_texture"] = "";
            parser["cursor_rect_left"] = 0;
            parser["cursor_rect_top"] = 0;
            parser["cursor_rect_width"] = 0;
            parser["cursor_rect_height"] = 0;
            parser["cursor_origin_x"] = 0.f;
            parser["cursor_origin_y"] = 0.f;
            parser["screenshot_path"] = "";
            parser["show_debug"] = false;
            parser["background_color_r"] = 0;
            parser["background_color_g"] = 0;
            parser["background_color_b"] = 0;
            parser["background_texture"] = "";
            parser["background_rect_left"] = 0;
            parser["background_rect_top"] = 0;
            parser["background_rect_width"] = 0;
            parser["background_rect_height"] = 0;
            parser["imgui_filename"] = "";
        }

		// TODO : Still bugs here ?
        Log::instance().useConsole(parser["log_console"].asBool());
        Log::instance().openLog(parser["log_file"]);
        Log::instance().setOnline(parser["log_url"]);
        setGlobalVolume(parser["global_volume"].asFloat());
        setMusicVolume(parser["music_volume"].asFloat());
        setSoundVolume(parser["sound_volume"].asFloat());
        setFullscreen(parser["fullscreen"].asBool());
        setVideoMode(sf::VideoMode(parser["width"].asUint(), parser["height"].asUint()));
        setStyle(static_cast<sf::Uint32>(parser["style"].asInt()));
        setTitle(parser["title"]);
        setVerticalSyncEnabled(parser["vsync"].asBool());
        setKeyRepeatEnabled(parser["key_repeat"].asBool());
        setJoystickThreshold(parser["joystick_threshold"].asFloat());
        setIcon(parser["icon"]);
        setMouseCursor(static_cast<Window::MouseCursor>(parser["cursor"].asInt()));
        setMouseCursorTexture(parser["cursor_texture"], sf::IntRect(parser["cursor_rect_left"].asInt(), parser["cursor_rect_top"].asInt(), parser["cursor_rect_width"].asInt(), parser["cursor_rect_height"].asInt()));
        setMouseCursorOrigin(sf::Vector2f(parser["cursor_origin_x"].asFloat(), parser["cursor_origin_y"].asFloat()));
        setScreenshotPath(parser["screenshot_path"]);
        showDebugInfo(parser["show_debug"].asBool());
        setBackgroundColor(sf::Color(parser["background_color_r"].asUint(), parser["background_color_g"].asUint(), parser["background_color_b"].asUint()));
        setBackgroundTexture(parser["background_texture"], sf::IntRect(parser["background_rect_left"].asInt(), parser["background_rect_top"].asInt(), parser["background_rect_width"].asInt(), parser["background_rect_height"].asInt()));
        ImGui::GetIO().IniFilename = (parser["imgui_filename"] != "") ? parser["imgui_filename"].c_str() : nullptr;
    }

    releaseResource("application_settings");

    create();
	instance().mGui.setWindow(instance().mWindow);
    ImGui::SFML::Init(instance().mWindow);
    Log::instance() << Log::Info << "NodeEngine::Application started";
    Log::instance() << Log::Info << std::string("Current time is " + getTime("%b %d, %Y %I:%M:%S %p"));
}

void Application::quit()
{
    if (!hasResource("application_settings"))
    {
        createResource<IniParser>("application_settings");
    }
    IniParser& parser = getResource<IniParser>("application_settings");
    parser["log_console"] = Log::instance().usingConsole();
    parser["log_file"] = Log::instance().getFilename();
    parser["log_url"] = Log::instance().getUrl();
    parser["global_volume"] = getGlobalVolume();
    parser["music_volume"] = getMusicVolume();
    parser["sound_volume"] = getSoundVolume();
    parser["fullscreen"] = isFullscreen();
    parser["width"] = getSize().x;
    parser["height"] = getSize().y;
    parser["style"] = static_cast<int>(getStyle());
    parser["title"] = getTitle();
    parser["vsync"] = isVerticalSyncEnabled();
    parser["key_repeat"] = isKeyRepeatEnabled();
    parser["joystick_threshold"] = getJoystickThreshold();
    parser["icon"] = getIcon();
    parser["cursor"] = static_cast<int>(getMouseCursor());
    parser["cursor_texture"] = getMouseCursorTexture();
    sf::IntRect rect = getMouseCursorTextureRect();
    parser["cursor_rect_left"] = rect.left;
    parser["cursor_rect_top"] = rect.top;
    parser["cursor_rect_width"] = rect.width;
    parser["cursor_rect_height"] = rect.height;
    sf::Vector2f origin = getMouseCursorOrigin();
    parser["cursor_origin_x"] = origin.x;
    parser["cursor_origin_y"] = origin.y;
    parser["screenshot_path"] = getScreenshotPath();
    parser["show_debug"] = isDebugInfoVisible();
    sf::Color bColor = getBackgroundColor();
    parser["background_color_r"] = bColor.r;
    parser["background_color_g"] = bColor.g;
    parser["background_color_b"] = bColor.b;
    parser["background_texture"] = getBackgroundTexture();
    sf::IntRect bRect = getBackgroundTextureRect();
    parser["background_rect_left"] = bRect.left;
    parser["background_rect_top"] = bRect.top;
    parser["background_rect_width"] = bRect.width;
    parser["background_rect_height"] = bRect.height;
    parser["imgui_filename"] = (ImGui::GetIO().IniFilename != nullptr) ? ImGui::GetIO().IniFilename : std::string();
    parser.saveToFile(instance().mPathToSettings + "application_settings.ini");

    ImGui::SFML::Shutdown();
}

void Application::runState(std::string const& startState)
{
    pushState(startState);
    instance().mStates.update(sf::Time::Zero);
    instance().mStateMode = true;
    run();
}

void Application::setEventDefaultFunction(EventFunction event)
{
    instance().mEventDefaultFunction = event;
}

void Application::setUpdateDefaultFunction(UpdateFunction update)
{
    instance().mUpdateDefaultFunction = update;
}

void Application::setRenderDefaultFunction(RenderFunction render)
{
    instance().mRenderDefaultFunction = render;
}

void Application::runDefault()
{
    instance().mStateMode = false;
    run();
}

void Application::run()
{
    unsigned int fps = 0;
    sf::Clock clock;
    sf::Clock fpsClock;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate >= timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            instance().mRunningTime += timePerFrame;
            handleEvent();
            update(timePerFrame);
        }

		auto mouse = getMousePosition2i();
		setDebugInfo("MouseX", mouse.x);
		setDebugInfo("MouseY", mouse.y);

        ImGui::SFML::Update(dt);

        render();

        fps++;
        if (fpsClock.getElapsedTime() >= sf::seconds(1.f))
        {
            instance().mFps = fps;
            setDebugInfo("FPS", fps);
            fps = 0;
            fpsClock.restart();
        }
    }
}

void Application::handleEvent()
{
    sf::Event event;
    while (pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
		instance().mGui.handleEvent(event);

        if (instance().mStateMode)
        {
            if (stateCount() > 0)
            {
                instance().mStates.handleEvent(event);
            }
        }
        else
        {
            if (instance().mEventDefaultFunction)
            {
                instance().mEventDefaultFunction(event);
            }
        }

        if (event.type == sf::Event::Closed)
        {
            close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
        {
            screenshot();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3)
        {
            showDebugInfo(!isDebugInfoVisible());
        }
    }
}

void Application::update(sf::Time dt)
{
    if (instance().mStateMode)
    {
        if (stateCount() > 0)
        {
            instance().mStates.update(dt);
        }
        if (stateCount() <= 0)
        {
            close();
        }
    }
    else
    {
        if (instance().mUpdateDefaultFunction)
        {
            instance().mUpdateDefaultFunction(dt);
        }
    }

    instance().mAudio.update();
}

void Application::render()
{
    clear();
    if (instance().mStateMode)
    {
        if (stateCount() > 0)
        {
            instance().mStates.render(instance().mWindow);
        }
    }
    else
    {
        if (instance().mRenderDefaultFunction)
        {
            instance().mRenderDefaultFunction(instance().mWindow);
        }
    }
    if (isDebugInfoVisible())
    {
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Debug");
        std::size_t size = instance().mWindow.getDebugInfoCount();
        for (std::size_t i = 0; i < size; i++)
        {
            auto itr = instance().mWindow.getDebugInfo(i);
            ImGui::Text("%s : %s", itr->first.c_str(), itr->second.c_str());
        }
        ImGui::End();
    }
	instance().mGui.draw();
    ImGui::Render();
    display();
}

sf::Time Application::getRunningTime()
{
    return instance().mRunningTime;
}

unsigned int Application::getFPS()
{
    return instance().mFps;
}

bool Application::isStateMode()
{
    return instance().mStateMode;
}

Application& Application::instance()
{
    static Application* instance = new Application();
    return *instance;
}

Log& Application::getLog()
{
    return Log::instance();
}

Window& Application::getWindow()
{
	return instance().mWindow;
}

tgui::Gui& Application::getGui()
{
	return instance().mGui;
}

ValueContainer& Application::getValues()
{
	return instance().mValues;
}

void Application::registerMusicFile(std::string const& id, std::string const& filename)
{
    instance().mAudio.registerMusicFile(id, filename);
}

std::shared_ptr<sf::Music> Application::playMusic(std::string const& id, bool loop, sf::Vector2f position)
{
    return instance().mAudio.playMusic(id, loop, position);
}

void Application::removeMusic(std::string const& id)
{
    instance().mAudio.removeMusic(id);
}

std::shared_ptr<sf::Sound> Application::playSound(std::string const& id, sf::Vector2f position)
{
    return instance().mAudio.playSound(id, position);
}

void Application::playAudio()
{
    instance().mAudio.play();
}

void Application::pauseAudio()
{
    instance().mAudio.pause();
}

void Application::stopAudio()
{
    instance().mAudio.stop();
}

void Application::setGlobalVolume(float volume)
{
    instance().mAudio.setGlobalVolume(volume);
}

void Application::setMusicVolume(float volume)
{
    instance().mAudio.setMusicVolume(volume);
}

void Application::setSoundVolume(float volume)
{
    instance().mAudio.setSoundVolume(volume);
}

float Application::getGlobalVolume()
{
    return instance().mAudio.getGlobalVolume();
}

float Application::getMusicVolume()
{
    return instance().mAudio.getMusicVolume();
}

float Application::getSoundVolume()
{
    return instance().mAudio.getSoundVolume();
}

sf::SoundSource::Status Application::getAudioStatus()
{
    return instance().mAudio.getStatus();
}

bool Application::hasResource(std::string const& id)
{
    return instance().mResources.hasResource(id);
}

bool Application::isResourceLoaded(std::string const& id)
{
    return instance().mResources.isResourceLoaded(id);
}

void Application::releaseResource(std::string const& id)
{
    instance().mResources.releaseResource(id);
}

void Application::releaseAllResources()
{
    instance().mResources.releaseAllResources();
}

void Application::pushState(std::string const& id)
{
    instance().mStates.pushState(id);
}

void Application::popState()
{
    instance().mStates.popState();
}

void Application::clearStates()
{
    instance().mStates.clearStates();
}

std::size_t Application::stateCount()
{
    return instance().mStates.stateCount();
}

void Application::create()
{
    instance().mWindow.create();
}

bool Application::isOpen()
{
    return instance().mWindow.isOpen();
}

void Application::close()
{
    instance().mWindow.close();
}

bool Application::pollEvent(sf::Event& event)
{
    return instance().mWindow.pollEvent(event);
}

void Application::clear()
{
    instance().mWindow.clear();
}

void Application::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
    instance().mWindow.draw(drawable, states);
}

void Application::draw(const sf::Vertex* vertices, unsigned int vertexCount, sf::PrimitiveType type, const sf::RenderStates& states)
{
    instance().mWindow.draw(vertices, vertexCount, type, states);
}

void Application::display()
{
    instance().mWindow.display();
}

void Application::setFullscreen(bool full)
{
    instance().mWindow.setFullscreen(full);
}

bool Application::isFullscreen()
{
    return instance().mWindow.isFullscreen();
}

void Application::setVideoMode(sf::VideoMode const& videoMode)
{
    instance().mWindow.setVideoMode(videoMode);
}

sf::VideoMode Application::getVideoMode()
{
    return instance().mWindow.getVideoMode();
}

void Application::setStyle(sf::Uint32 style)
{
    instance().mWindow.setStyle(style);
}

sf::Uint32 Application::getStyle()
{
    return instance().mWindow.getStyle();
}

void Application::setTitle(std::string const& title)
{
    instance().mWindow.setTitle(title);
}

std::string Application::getTitle()
{
    return instance().mWindow.getTitle();
}

void Application::setVerticalSyncEnabled(bool enabled)
{
    instance().mWindow.setVerticalSyncEnabled(enabled);
}

bool Application::isVerticalSyncEnabled()
{
    return instance().mWindow.isVerticalSyncEnabled();
}

void Application::setVisible(bool visible)
{
    instance().mWindow.setVisible(visible);
}

bool Application::isVisible()
{
    return instance().mWindow.isVisible();
}

void Application::setKeyRepeatEnabled(bool enabled)
{
    instance().mWindow.setKeyRepeatEnabled(enabled);
}

bool Application::isKeyRepeatEnabled()
{
    return instance().mWindow.isKeyRepeatEnabled();
}

void Application::setJoystickThreshold(float threshold)
{
    instance().mWindow.setJoystickThreshold(threshold);
}

float Application::getJoystickThreshold()
{
    return instance().mWindow.getJoystickThreshold();
}

sf::Vector2u Application::getSize()
{
    return instance().mWindow.getSize();
}

void Application::setView(const sf::View &view)
{
    instance().mWindow.setView(view);
}

const sf::View& Application::getView()
{
    return instance().mWindow.getView();
}

void Application::setDefaultView()
{
    instance().mWindow.setDefaultView();
}

const sf::View& Application::getDefaultView()
{
    return instance().mWindow.getDefaultView();
}

sf::IntRect Application::getViewport(const sf::View &view)
{
    return instance().mWindow.getViewport(view);
}

void Application::setIcon(std::string const& filename)
{
    if (filename != "")
    {
        if (hasResource(filename))
        {
            if (isResourceLoaded(filename))
            {
                sf::Image* img = &getResource<Image>(filename);
                instance().mWindow.setIcon(img);
                instance().mIconFilename = (img != nullptr) ? filename : "";
                return;
            }
        }
    }
    instance().mWindow.setIcon(nullptr);
    instance().mIconFilename = "";
}

std::string Application::getIcon()
{
    return instance().mIconFilename;
}

void Application::setMousePosition2i(sf::Vector2i const& position)
{
    instance().mWindow.setMousePosition2i(position);
}

void Application::setMousePosition(sf::Vector2f const& position)
{
    instance().mWindow.setMousePosition(position);
}

void Application::setMousePositionMap(sf::Vector2f const& position)
{
    instance().mWindow.setMousePositionMap(position);
}

void Application::setMousePositionView(sf::Vector2f const& position, sf::View const& view)
{
    instance().mWindow.setMousePositionView(position, view);
}

sf::Vector2i Application::getMousePosition2i()
{
    return instance().mWindow.getMousePosition2i();
}

sf::Vector2f Application::getMousePosition()
{
    return instance().mWindow.getMousePosition();
}

sf::Vector2f Application::getMousePositionMap()
{
    return instance().mWindow.getMousePositionMap();
}

sf::Vector2f Application::getMousePositionView(sf::View const& view)
{
    return instance().mWindow.getMousePositionView(view);
}

sf::Vector2i Application::getTouchPosition2i(unsigned int touchIndex)
{
    return instance().mWindow.getTouchPosition2i(touchIndex);
}

sf::Vector2f Application::getTouchPosition(unsigned int touchIndex)
{
    return instance().mWindow.getTouchPosition(touchIndex);
}

sf::Vector2f Application::getTouchPositionMap(unsigned int touchIndex)
{
    return instance().mWindow.getTouchPositionMap(touchIndex);
}

sf::Vector2f Application::getTouchPositionView(sf::View const& view, unsigned int touchIndex)
{
    return instance().mWindow.getTouchPositionView(view, touchIndex);
}

void Application::setPointerPosition2i(sf::Vector2i const& position)
{
    instance().mWindow.setPointerPosition2i(position);
}

void Application::setPointerPosition(sf::Vector2f const& position)
{
    instance().mWindow.setPointerPosition(position);
}

void Application::setPointerPositionMap(sf::Vector2f const& position)
{
    instance().mWindow.setPointerPositionMap(position);
}

void Application::setPointerPositionView(sf::Vector2f const& position, sf::View const& view)
{
    instance().mWindow.setPointerPositionView(position, view);
}

sf::Vector2i Application::getPointerPosition2i(unsigned int touchIndex)
{
    return instance().mWindow.getPointerPosition2i(touchIndex);
}

sf::Vector2f Application::getPointerPosition(unsigned int touchIndex)
{
    return instance().mWindow.getPointerPosition(touchIndex);
}

sf::Vector2f Application::getPointerPositionMap(unsigned int touchIndex)
{
    return instance().mWindow.getPointerPositionMap(touchIndex);
}

sf::Vector2f Application::getPointerPositionView(sf::View const& view, unsigned int touchIndex)
{
    return instance().mWindow.getPointerPositionView(view, touchIndex);
}

void Application::setMouseCursor(Window::MouseCursor cursor)
{
    instance().mWindow.setMouseCursor(cursor);
}

void Application::hideMouseCursor()
{
    instance().mWindow.hideMouseCursor();
}

void Application::useDefaultMouseCursor()
{
    instance().mWindow.useDefaultMouseCursor();
}

void Application::useCustomMouseCursor(sf::Texture* texture, sf::Vector2f const& origin, sf::IntRect const& textureRect)
{
    instance().mWindow.useCustomMouseCursor(texture, origin, textureRect);
}

Window::MouseCursor Application::getMouseCursor()
{
    return instance().mWindow.getMouseCursor();
}

void Application::setMouseCursorTexture(std::string const& filename, sf::IntRect rect)
{
    if (filename != "")
    {
        if (hasResource(filename))
        {
            if (isResourceLoaded(filename))
            {
                sf::Texture* tex = &getResource<Texture>(filename);
                instance().mWindow.setMouseCursorTexture(tex, rect);
                instance().mCursorFilename = (tex != nullptr) ? filename : "";
                return;
            }
        }
    }
    instance().mWindow.setMouseCursorTexture(nullptr, rect);
    instance().mCursorFilename = "";
}

void Application::setMouseCursorTextureRect(sf::IntRect const& textureRect)
{
    instance().mWindow.setMouseCursorTextureRect(textureRect);
}

void Application::setMouseCursorOrigin(sf::Vector2f const& origin)
{
    instance().mWindow.setMouseCursorOrigin(origin);
}

std::string Application::getMouseCursorTexture()
{
    return instance().mCursorFilename;
}

sf::IntRect Application::getMouseCursorTextureRect()
{
    return instance().mWindow.getMouseCursorTextureRect();
}

sf::Vector2f Application::getMouseCursorOrigin()
{
    return instance().mWindow.getMouseCursorOrigin();
}

void Application::screenshot()
{
    instance().mWindow.screenshot();
}

void Application::setScreenshotPath(std::string const& screenshotPath)
{
    instance().mWindow.setScreenshotPath(screenshotPath);
}

std::string Application::getScreenshotPath()
{
    return instance().mWindow.getScreenshotPath();
}

void Application::showDebugInfo(bool visible)
{
    instance().mWindow.showDebugInfo(visible);
}

bool Application::isDebugInfoVisible()
{
    return instance().mWindow.isDebugInfoVisible();
}

std::string Application::getDebugInfo(std::string const& id)
{
    return instance().mWindow.getDebugInfo(id);
}

void Application::removeDebugInfo(std::string const& id)
{
    instance().mWindow.removeDebugInfo(id);
}

void Application::removeDebugInfos()
{
    instance().mWindow.removeDebugInfos();
}

void Application::setBackgroundColor(sf::Color color)
{
    instance().mWindow.setBackgroundColor(color);
}

sf::Color Application::getBackgroundColor()
{
    return instance().mWindow.getBackgroundColor();
}

void Application::setBackgroundTexture(std::string const& filename, sf::IntRect rect)
{
    if (filename != "" && hasResource(filename))
    {
        if (hasResource(filename))
        {
            if (isResourceLoaded(filename))
            {
                sf::Texture* tex = &getResource<Texture>(filename);
                instance().mWindow.setBackgroundTexture(tex, rect);
                instance().mBackgroundFilename = (tex != nullptr) ? filename : "";
                return;
            }
        }
    }
    instance().mWindow.setBackgroundTexture(nullptr, rect);
    instance().mBackgroundFilename = "";
}

std::string Application::getBackgroundTexture()
{
    return instance().mBackgroundFilename;
}

sf::IntRect Application::getBackgroundTextureRect()
{
    return instance().mWindow.getBackgroundTextureRect();
}

Application::Application()
{
    mEventDefaultFunction = [](sf::Event const& event){};
    mUpdateDefaultFunction = [](sf::Time dt){};
    mRenderDefaultFunction = [](sf::RenderTarget& target){};
}

Application::~Application()
{
    mResources.releaseAllResources();
}
