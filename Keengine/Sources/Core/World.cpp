#include "World.hpp"

namespace ke
{

World* World::mWorld = nullptr;
bool World::mInstantiated = false;

World& World::createInstance()
{
	assert(!mInstantiated);
	mWorld = new World();
	mInstantiated = true;
	return *mWorld;
}

World& World::instance()
{
	assert(mInstantiated);
	return *mWorld;
}

void World::destroyInstance()
{
	assert(mInstantiated);
	delete mWorld;
	mWorld = nullptr;
	mInstantiated = false;
}

World::World()
	: mSceneTexture()
	, mVertices(sf::Triangles, 6)
	, mEffects()
	, mInputs()
	, mBackground()
	, mUsePhysic(false)
	, mUseLights(false)
	, mLights()
	, mTime()
	, mScene(nullptr)
{
	initLights();
	newScene();
}

World::~World()
{
	if (mScene != nullptr)
	{
		mScene->onDestroy();
	}
}

Application& World::getApplication()
{
	return Application::instance();
}

InputSystem& World::getInputs()
{
	return mInputs;
}

Log& World::getLog()
{
	return Application::getLog();
}

ltbl::LightSystem& World::getLights()
{
	return mLights;
}

TimeSystem& World::getTime()
{
	return mTime;
}

PhysicSystem* World::getPhysic()
{
	if (mScene != nullptr)
	{
		return &mScene->getPhysic();
	}
	return nullptr;
}

b2World* World::getPhysicWorld()
{
	if (mScene != nullptr)
	{
		return mScene->getPhysicWorld();
	}
	return nullptr;
}

void World::newScene()
{
	if (mScene != nullptr)
	{
		mScene->onDestroy();
	}
	mScene = std::unique_ptr<Scene>(new Scene(this));
	if (mScene != nullptr)
	{
		mScene->onCreate();
	}
}

void World::initLights()
{
	if (!hasResource("pointLightTexture"))
	{
		Texture& texture = createResource<Texture>("pointLightTexture");
		if (!texture.loadFromMemory(pointLightTexture, (sizeof(pointLightTexture) / sizeof(*pointLightTexture))))
		{
			getLog() << "World - Can't load pointLightTexture";
		}
		texture.setSmooth(true);
	}
	if (!hasResource("directionLightTexture"))
	{
		Texture& texture = createResource<Texture>("directionLightTexture");
		if (!texture.loadFromMemory(directionLightTexture, (sizeof(directionLightTexture) / sizeof(*directionLightTexture))))
		{
			getLog() << "World - Can't load directionLightTexture";
		}
		texture.setSmooth(true);
	}
	if (!hasResource("penumbraTexture"))
	{
		Texture& texture = createResource<Texture>("penumbraTexture");
		if (!texture.loadFromMemory(penumbraTexture, (sizeof(penumbraTexture) / sizeof(*penumbraTexture))))
		{
			getLog() << "World - Can't load penumbraTexture";
		}
		texture.setSmooth(true);
	}
	if (!hasResource("unshadowShader"))
	{
		const std::string v = "void main() { gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; gl_TexCoord[0] = gl_MultiTexCoord0; gl_FrontColor = gl_Color; }";
		const std::string f = "uniform sampler2D penumbraTexture; uniform float lightBrightness; uniform float darkBrightness; void main()  { float penumbra = texture2D(penumbraTexture, gl_TexCoord[0].xy).x; float shadow = (lightBrightness - darkBrightness) * penumbra + darkBrightness; gl_FragColor = vec4(vec3(1.0 - shadow), 1.0); }";
		Shader& shader = createResource<Shader>("unshadowShader");
		if (!shader.loadFromMemory(v, f))
		{
			getLog() << "World - Can't load unshadowShader";
		}
	}
	if (!hasResource("lightOverShapeShader"))
	{
		const std::string v = "void main() { gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; gl_TexCoord[0] = gl_MultiTexCoord0; }";
		const std::string f = "uniform sampler2D emissionTexture; uniform vec2 targetSizeInv; void main() { vec2 targetCoords = gl_FragCoord.xy * targetSizeInv; vec4 emissionColor = texture2D(emissionTexture, targetCoords); gl_FragColor = vec4(emissionColor.rgb, 1.0); }";
		Shader& shader = createResource<Shader>("lightOverShapeShader");
		if (!shader.loadFromMemory(v, f))
		{
			getLog() << "World - Can't load lightOverShapeShader";
		}
	}

	mLights.create({ -1000.f, -1000.f, 2000.f, 2000.f }, getApplication().getSize(), getResource<Texture>("penumbraTexture"), getResource<Shader>("unshadowShader"), getResource<Shader>("lightOverShapeShader"));
}

void World::handleEvent(sf::Event const & event)
{
	mInputs.handleEvent(event);
}

void World::update(sf::Time dt)
{
	dt *= mTime.getTimeFactor();

	mInputs.update(dt);
	mTime.update(dt);

	if (mScene != nullptr)
	{
		mScene->update(dt);
	}
}

void World::render(sf::RenderTarget& target)
{
	// Update size
	if (target.getSize() != mSceneTexture.getSize())
	{
		sf::Vector2u size = target.getSize();
		mBackground.setSize(static_cast<sf::Vector2f>(size));
		mSceneTexture.create(size.x, size.y);
	}

	// Draw
	mSceneTexture.clear();

	mSceneTexture.setView(mSceneTexture.getDefaultView());
	mSceneTexture.draw(mBackground);

	/* TODO : Background
	std::string bgTexture = Application::getBackgroundTexture();
	sf::IntRect bgRect = Application::getBackgroundTextureRect();
	sf::Color bgColor = Application::getBackgroundColor();
	if (bgTexture == "")
	{
		mBackground.setFillColor(bgColor);
	}
	else
	{
		mBackground.setFillColor(sf::Color::White);
		mBackground.setTexture(&Application::getResource<Texture>(bgTexture));
		mBackground.setTextureRect(bgRect);
	}
	*/

	// Render Scene
	if (mScene != nullptr)
	{
		mScene->render(mSceneTexture);
	}

	// Lights

	// Post effects
	for (auto itr = mEffects.begin(); itr != mEffects.end(); itr++)
	{
		itr->second->apply(mSceneTexture, mSceneTexture);
	}

	mSceneTexture.display();

	// Apply to the window
	target.draw(sf::Sprite(mSceneTexture.getTexture()));
}

Actor::Ptr World::getActor(std::string const& id) const
{
	if (mScene != nullptr)
	{
		return mScene->getActor(id);
	}
	return nullptr;
}

Actor::Ptr World::getActor(std::size_t index) const
{
	if (mScene != nullptr)
	{
		return mScene->getActor(index);
	}
	return nullptr;
}

void World::removeActor(std::string const& id)
{
	if (mScene != nullptr)
	{
		mScene->removeActor(id);
	}
}

void World::removeActor(std::size_t index)
{
	if (mScene != nullptr)
	{
		mScene->removeActor(index);
	}
}

bool World::hasActor(std::string const& id) const
{
	if (mScene != nullptr)
	{
		return mScene->hasActor(id);
	}
	return false;
}

std::size_t World::getActorCount() const
{
	if (mScene != nullptr)
	{
		return mScene->getActorCount();
	}
	return 0;
}

void World::removeEffect(std::size_t const & order)
{
	auto itr = mEffects.find(order);
	if (itr != mEffects.end())
	{
		mEffects.erase(itr);
	}
}

sf::View* World::getView()
{
	if (mScene != nullptr)
	{
		return &(mScene->getView());
	}
	return nullptr;
}

bool World::hasResource(std::string const& id)
{
	return Application::hasResource(id);
}

bool World::isResourceLoaded(std::string const& id)
{
	return Application::isResourceLoaded(id);
}

void World::releaseResource(std::string const& id)
{
	Application::releaseResource(id);
}

void World::releaseAllResources()
{
	Application::releaseAllResources();
}

} // namespace ke