#include "Scene.hpp"

namespace ke
{

Scene::Scene(sf::Uint32 options)
	: mOptions(options)
	, mActorIdCounter(1)
	, mActors()
	, mView(getApplication().getDefaultView())
	, mPhysic()
	, mLights()
{
	if (useLight())
	{
		initLights();
	}
	getApplication().getInputs().registerInput(&mInput);
	mSceneRoot = createActor<Actor>();
}

Scene::~Scene()
{
	mActors.clear();
	getApplication().getInputs().unregisterInput(&mInput);
	mSceneRoot = nullptr;
}

void Scene::handleEvent(sf::Event const & event)
{
}

void Scene::update(sf::Time dt)
{
	for (std::size_t i = 0; i < mActors.size(); i++)
	{
		if (mActors[i] != nullptr)
		{
			if (!mActors[i]->isMarkedForRemoval())
			{
				mActors[i]->updateComponents(dt);
				mActors[i]->update(dt);

				if (usePhysic())
				{
					mActors[i]->prePhysicUpdate();
				}
			}
		}
	}

	if (usePhysic())
	{
		mPhysic.update(dt);

		for (std::size_t i = 0; i < mActors.size(); i++)
		{
			if (mActors[i] != nullptr)
			{
				if (!mActors[i]->isMarkedForRemoval())
				{
					mActors[i]->postPhysicUpdate();
				}
			}
		}
	}

	mActors.erase(std::remove_if(mActors.begin(), mActors.end(), [](Actor::Ptr actor) 
	{
		return (actor == nullptr || actor->isMarkedForRemoval());
	}), mActors.end());
}

void Scene::render(sf::RenderTarget& target)
{
	if (useEffect() || useLight())
	{
		renderComplex(target);
	}
	else
	{
		renderSimple(target);
	}

	if (usePhysic())
	{
		mPhysic.render(target);
	}
}

bool Scene::usePhysic() const
{
	return ((mOptions & Options::Physic) != 0);
}

bool Scene::useEffect() const
{
	return ((mOptions & Options::Effect) != 0);
}

bool Scene::useLight() const
{
	return ((mOptions & Options::Light) != 0);
}

PhysicSystem& Scene::getPhysic()
{
	return mPhysic;
}

b2World* Scene::getPhysicWorld()
{
	return mPhysic.getWorld();
}

ltbl::LightSystem& Scene::getLights()
{
	return mLights;
}

Actor::Ptr Scene::getActor(std::string const & id) const
{
	std::size_t size = mActors.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mActors[i]->getId() == id)
		{
			return mActors[i];
		}
	}
	return nullptr;
}

Actor::Ptr Scene::getActor(std::size_t index) const
{
	if (0 <= index && index < mActors.size())
	{
		return mActors.at(index);
	}
	return nullptr;
}

void Scene::removeActor(std::string const& id)
{
	Actor::Ptr actor = getActor(id);
	if (actor != nullptr)
	{
		actor->remove();
	}
}

void Scene::removeActor(std::size_t index)
{
	Actor::Ptr actor = getActor(index);
	if (actor != nullptr)
	{
		actor->remove();
	}
}

bool Scene::hasActor(std::string const& id) const
{
	return (getActor(id) != nullptr);
}

std::size_t Scene::getActorCount() const
{
	return mActors.size();
}

sf::View& Scene::getView()
{
	return mView;
}

void Scene::removeEffect(std::size_t const& order)
{
	auto itr = mEffects.find(order);
	if (itr != mEffects.end())
	{
		mEffects.erase(itr);
	}
}

Log& Scene::getLog()
{
	return getApplication().getLog();
}

Application& Scene::getApplication()
{
	return Application::instance();
}

Input& Scene::getInput()
{
	return mInput;
}

void Scene::attachComponent(SceneComponent::Ptr component)
{
	if (mSceneRoot != nullptr)
	{
		mSceneRoot->attachComponent(component);
	}
}

void Scene::detachComponent(SceneComponent::Ptr component)
{
	if (mSceneRoot != nullptr)
	{
		mSceneRoot->detachComponent(component);
	}
}

void Scene::removeComponent(Component::Ptr component)
{
	if (mSceneRoot != nullptr)
	{
		mSceneRoot->removeComponent(component);
	}
}

bool Scene::sortActor(Actor::Ptr a, Actor::Ptr b)
{
	if (a != nullptr && b != nullptr)
	{
		float ay = a->getPosition().y;
		float by = b->getPosition().y;
		if (a->getZ() < b->getZ())
		{
			return true;
		}
		else if (a->getZ() > b->getZ())
		{
			return false;
		}
		else if (ay < by)
		{
			return true;
		}
		else if (ay > by)
		{
			return false;
		}
		else
		{
			return (a->getPosition().x < b->getPosition().x);
		}
	}
	return true;
}

void Scene::initLights()
{
	if (!getApplication().hasResource("pointLightTexture"))
	{
		Texture& texture = getApplication().createResource<Texture>("pointLightTexture");
		if (!texture.loadFromMemory(pointLightTexture, (sizeof(pointLightTexture) / sizeof(*pointLightTexture))))
		{
			getLog() << "World - Can't load pointLightTexture";
		}
		texture.setSmooth(true);
	}
	mLights.create({ -1000.f, -1000.f, 2000.f, 2000.f }, getApplication().getSize());
}

void Scene::renderComplex(sf::RenderTarget& target)
{
	// Update Texture
	sf::Vector2u size = target.getSize();
	if (mSceneTexture.getSize() != size)
	{
		mSceneTexture.create(size.x, size.y);
	}

	// Background
	std::string bgTexture = getApplication().getBackgroundTexture();
	sf::IntRect bgRect = getApplication().getBackgroundTextureRect();
	sf::Color bgColor = getApplication().getBackgroundColor();

	// Render Background
	mSceneTexture.clear(getApplication().getBackgroundColor());
	if (!getApplication().getWindow().useBackgroundColor())
	{
		std::string textureName = getApplication().getBackgroundTexture();
		if (getApplication().hasResource(textureName))
		{
			if (getApplication().isResourceLoaded(textureName))
			{
				mSceneTexture.setView(getApplication().getDefaultView());
				mSceneTexture.draw(sf::Sprite(getApplication().getResource<Texture>(textureName), getApplication().getBackgroundTextureRect()));
			}
		}
	}

	// Render Scene
	renderSimple(mSceneTexture);

	// Render Lights
	if (useLight())
	{
		mLights.render(mSceneTexture);
	}

	// Render Effects
	if (useEffect())
	{
		for (auto itr = mEffects.begin(); itr != mEffects.end(); itr++)
		{
			itr->second->apply(mSceneTexture);
		}
	}

	// Display
	mSceneTexture.display();
	target.draw(sf::Sprite(mSceneTexture.getTexture()));
}

void Scene::renderSimple(sf::RenderTarget& target)
{
	target.setView(mView);

	std::sort(mActors.begin(), mActors.end(), sortActor);

	std::size_t size = mActors.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mActors[i] != nullptr)
		{
			if (mActors[i]->isVisible())
			{
				mActors[i]->render(target);
			}
		}
	}
}

} // namespace ke