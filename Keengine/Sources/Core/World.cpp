#include "World.hpp"

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
	: mIdCounter(0)
	, mActors()
	, mPrimitives()
	, mSceneTexture()
	, mVertices(sf::Triangles, 6)
	, mClockCreation()
	, mCamera(nullptr)
	, mWorldView(getApplication().getDefaultView())
	, mEffects()
{
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

	if (!hasResource("pointLightTexture"))
	{
		createResource<Texture>("pointLightTexture", "Example/pointLightTexture.png").setSmooth(true);
	}
	if (!hasResource("directionLightTexture"))
	{
		createResource<Texture>("directionLightTexture", "Example/directionLightTexture.png").setSmooth(true);
	}
	if (!hasResource("penumbraTexture"))
	{
		createResource<Texture>("penumbraTexture", "Example/penumbraTexture.png").setSmooth(true);
	}
	Texture& penumbra = getResource<Texture>("penumbraTexture");
	if (!hasResource("unshadowShader"))
	{
		createResource<Shader>("unshadowShader", "Example/unshadowShader.vert", "Example/unshadowShader.frag");
	}
	Shader& unshadow = getResource<Shader>("unshadowShader");
	if (!hasResource("lightOverShapeShader"))
	{
		createResource<Shader>("lightOverShapeShader", "Example/lightOverShapeShader.vert", "Example/lightOverShapeShader.frag");
	}
	Shader& lightOverShape = getResource<Shader>("lightOverShapeShader");

	mLights.create({ -1000.f, -1000.f, 2000.f, 2000.f }, getApplication().getSize(), penumbra, unshadow, lightOverShape);
}

World::~World()
{
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

ltbl::LightSystem & World::getLights()
{
	return mLights;
}

void World::handleEvent(sf::Event const & event)
{
	mInputs.handleEvent(event);
}

void World::update(sf::Time dt)
{
	mInputs.update(dt);

	for (auto& actor : mActors)
	{
		actor->updateComponents(dt);
		actor->update(dt);
	}

	mActors.erase(std::remove_if(mActors.begin(), mActors.end(), [](Actor::Ptr actor) 
	{ 
		bool ret = (actor == nullptr || actor->isMarkedForRemoval());
		if (ret && actor != nullptr)
		{
			actor->onDestroyed();
		}
		return ret;
	}), mActors.end());
}

void World::render(sf::RenderTarget& target)
{
	// Update size
	if (target.getSize() != mSceneTexture.getSize())
	{
		sf::Vector2u size = target.getSize();
		mBackground.setSize(static_cast<sf::Vector2f>(size));
		mSceneTexture.create(size.x, size.y);
		mVertices[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
		mVertices[1] = sf::Vertex(sf::Vector2f(static_cast<float>(size.x), 0), sf::Vector2f(static_cast<float>(size.x), 0));
		mVertices[2] = sf::Vertex(static_cast<sf::Vector2f>(size), static_cast<sf::Vector2f>(size));
		mVertices[3] = mVertices[2];
		mVertices[4] = sf::Vertex(sf::Vector2f(0, static_cast<float>(size.y)), sf::Vector2f(0, static_cast<float>(size.y)));
		mVertices[5] = mVertices[0];
	}

	// Update rendering order
	std::sort(mPrimitives.begin(), mPrimitives.end(), [](PrimitiveComponent* a, PrimitiveComponent* b) -> bool
	{
		if (a != nullptr && b != nullptr)
		{
			if (a->getWorldZ() < b->getWorldZ())
			{
				return true;
			}
			else if (a->getWorldZ() > b->getWorldZ())
			{
				return false;
			}
			else if (a->getWorldPosition().y < b->getWorldPosition().y)
			{
				return true;
			}
			else if (a->getWorldPosition().y > b->getWorldPosition().y)
			{
				return false;
			}
			else
			{
				return (a->getWorldPosition().x < b->getWorldPosition().x);
			}
		}
		return true;
	});

	// Draw
	mSceneTexture.clear();

	mSceneTexture.setView(mSceneTexture.getDefaultView());
	mSceneTexture.draw(mBackground);

	mSceneTexture.setView(getView());
	mLights.render(getView(), getResource<Shader>("unshadowShader"), getResource<Shader>("lightOverShapeShader"));

	mSceneTexture.setView(mSceneTexture.getDefaultView());
	mSceneTexture.draw(sf::Sprite(mLights.getLightingTexture()), sf::RenderStates(sf::BlendMultiply));

	mSceneTexture.setView(getView());
	for (PrimitiveComponent* primitive : mPrimitives)
	{
		if (primitive->isRegistered() && primitive->isVisible())
		{
			primitive->render(mSceneTexture);
		}
	}
	mSceneTexture.display();

	// Post effects
	for (auto itr = mEffects.begin(); itr != mEffects.end(); itr++)
	{
		itr->second->apply(mSceneTexture, mSceneTexture);
	}

	// Apply to the window
	target.draw(mVertices, sf::RenderStates(&mSceneTexture.getTexture()));
}

void World::registerPrimitive(PrimitiveComponent* component)
{
	if (component != nullptr)
	{
		mPrimitives.push_back(component);
	}
}

void World::unregisterPrimitive(PrimitiveComponent* component)
{
	if (component != nullptr)
	{
		mPrimitives.erase(std::remove_if(mPrimitives.begin(), mPrimitives.end(), [&component](PrimitiveComponent* cmpnt) { return (cmpnt == nullptr || cmpnt == component); }), mPrimitives.end());
	}
}

void World::removeActor(std::string const& id)
{
	Actor::Ptr actor = getActor(id);
	if (actor != nullptr)
	{
		actor->remove();
	}
}

void World::removeActor(std::size_t index)
{
	Actor::Ptr actor = getActor(index);
	if (actor != nullptr)
	{
		actor->remove();
	}
}

bool World::hasActor(std::string const& id) const
{
	return (getActor(id) != nullptr);
}

Actor::Ptr World::getActor(std::string const & id) const
{
	for (Actor::Ptr actor : mActors)
	{
		if (actor->getId() == id)
		{
			return actor;
		}
	}
	return nullptr;
}

Actor::Ptr World::getActor(std::size_t index) const
{
	if (0 <= index && index < mActors.size())
	{
		return mActors.at(index);
	}
	return nullptr;
}

std::size_t World::getActorCount() const
{
	return mActors.size();
}

std::size_t World::getActualId()
{
	return mIdCounter++;
}

sf::Time World::getTimeSinceCreation() const
{
	return mClockCreation.getElapsedTime();
}

void World::removeEffect(std::size_t const & order)
{
	auto itr = mEffects.find(order);
	if (itr != mEffects.end())
	{
		mEffects.erase(itr);
	}
}

sf::View& World::getView()
{
	if (mCamera == nullptr)
	{
		return mWorldView;
	}
	else
	{
		return mCamera->getView();
	}
}

void World::registerCamera(CameraComponent* camera)
{
	mCamera = camera;
}

void World::unregisterCamera(CameraComponent* camera)
{
	mCamera = nullptr;
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
