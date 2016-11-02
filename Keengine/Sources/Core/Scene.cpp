#include "Scene.hpp"

#include "Factories.hpp"

namespace ke
{

Scene::Scene(const std::string& id, sf::Uint32 options)
	: mId(id)
	, mOptions(options)
	, mActorIdCounter(1)
	, mActors()
	, mView(getApplication().getDefaultView())
	, mPhysic(nullptr)
	, mLights(nullptr)
	, mSceneTexture(nullptr)
	, mEffects()
	, mInput()
	, mSceneRoot(nullptr)
{
	Factories::registerAll();
	if (useEffect() || useLight())
	{
		mSceneTexture = std::unique_ptr<sf::RenderTexture>(new sf::RenderTexture());
	}
	if (useLight())
	{
		initLights();
	}
	if (usePhysic())
	{
		mPhysic = std::make_shared<PhysicSystem>();
	}
	getApplication().getInputs().registerInput(&mInput);
	mSceneRoot = createActor<Actor>("0");
}

Scene::~Scene()
{
	mActors.clear();
	getApplication().getInputs().unregisterInput(&mInput);
	mSceneRoot = nullptr;
}

const std::string& Scene::getId() const
{
	return mId;
}

void Scene::setId(const std::string& id)
{
	mId = id;
}

void Scene::handleEvent(const sf::Event& event)
{
}

void Scene::update(sf::Time dt)
{
	for (std::size_t i = 0; i < mActors.size(); i++)
	{
		if (mActors[i] != nullptr && !mActors[i]->isMarkedForRemoval())
		{
			if (mActors[i]->isUpdatable())
			{
				mActors[i]->updateComponents(dt);
				mActors[i]->update(dt);
			}

			if (usePhysic())
			{
				mActors[i]->prePhysicUpdate();
			}
		}
	}

	if (usePhysic() && mPhysic != nullptr)
	{
		mPhysic->update(dt);

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

	if (usePhysic() && mPhysic != nullptr && mPhysic->isRenderingDebug())
	{
		sf::View v = target.getView();
		target.setView(mView);
		mPhysic->render(target);
		target.setView(v);
	}
}

Actor::Ptr Scene::createActorFromFactory(const std::string& type)
{
	Actor::Ptr actor = Factories::createActor(*this, type);
	actor->setId(ke::decToHex<std::size_t>(mActorIdCounter++));
	actor->initializePhysic();
	actor->initializeComponents();
	actor->initialize();
	mActors.push_back(actor);
	return actor;
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

std::shared_ptr<PhysicSystem> Scene::getPhysic()
{
	return mPhysic;
}

b2World* Scene::getPhysicWorld()
{
	return (mPhysic != nullptr) ? mPhysic->getWorld() : nullptr;
}

std::shared_ptr<ltbl::LightSystem> Scene::getLights()
{
	return mLights;
}

void Scene::setEffect(std::size_t const& order, const std::string& effect)
{
	mEffects[order] = Factories::createEffect(effect);
}

void Scene::removeEffect(std::size_t const& order)
{
	auto itr = mEffects.find(order);
	if (itr != mEffects.end())
	{
		mEffects.erase(itr);
	}
}

void Scene::removeComponent(Component::Ptr component)
{
	if (mSceneRoot != nullptr)
	{
		mSceneRoot->removeComponent(component);
	}
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

void Scene::useBackgroundColor(const sf::Color& color)
{
	mBackground.useColor(color);
}

void Scene::useBackgroundScaledTexture(sf::Texture* texture, sf::IntRect rect)
{
	mBackground.useScaledTexture(texture, rect);
}

void Scene::useBackgroundRepeatedTexture(sf::Texture* texture, sf::IntRect rect)
{
	mBackground.useRepeatedTexture(texture, rect);
}

sf::View& Scene::getView()
{
	return mView;
}

Input& Scene::getInput()
{
	return mInput;
}

Log& Scene::getLog()
{
	return getApplication().getLog();
}

Application& Scene::getApplication()
{
	return Application::instance();
}

bool Scene::loadFromXml(const std::string& filepath)
{
	Serializer xml;
	std::string filename = filepath + "scene" + ((mId != "") ? "-" + mId : "") + ".xml";
	if (!xml.openDocument(filename, false, "Scene"))
	{
		getLog() << ke::Log::Error << "Cannot open scene : " + filename;
		return false;
	}

	// Load Scene
	float inputp;
	if (!xml.load("count", mActorIdCounter) || !xml.load("inputp", inputp))
	{
		return false;
	}
	mInput.setPriority(inputp);
	if (usePhysic() && mPhysic != nullptr)
	{
		sf::Vector2f pgrav;
		float pxm;
		bool prdbg;
		unsigned int prfla;
		if (!xml.load("pgrav", pgrav)
			|| !xml.load("pxm", pxm)
			|| !xml.load("prdbg", prdbg)
			|| !xml.load("prfla", prfla))
		{
			return false;
		}
		mPhysic->setGravity(pgrav);
		mPhysic->setPixelsPerMeter(pxm);
		mPhysic->setRenderDebug(prdbg);
		mPhysic->setRenderFlags(prfla);
	}
	if (useLight() && mLights != nullptr)
	{
		float lrang;
		float lradm;
		sf::Color lambc;
		if (!xml.load("lrang", lrang)
			|| !xml.load("lradm", lradm)
			|| !xml.load("lambc", lambc))
		{
			return false;
		}
		mLights->setDirectionEmissionRange(lrang);
		mLights->setDirectionEmissionRadiusMultiplier(lradm);
		mLights->setAmbientColor(lambc);
	}
	if (useEffect() && xml.read("Effects"))
	{
		while (xml.read("Effect"))
		{
			std::size_t order;
			std::string effect;
			if (!xml.load("order", order) || !xml.load("effect", effect))
			{
				return false;
			}
			setEffect(order, effect);
			xml.end();
		}
		xml.end();
	}
	if (xml.read("View"))
	{
		sf::Vector2f center;
		sf::Vector2f size;
		float rotation;
		sf::FloatRect viewport;
		if (!xml.load("center", center)
			|| !xml.load("size", size)
			|| !xml.load("rotation", rotation)
			|| !xml.load("viewport", viewport))
		{
			return false;
		}
		mView.setCenter(center);
		mView.setSize(size);
		mView.setRotation(rotation);
		mView.setViewport(viewport);
		xml.end();
	}

	if (!xml.read("SceneRoot"))
	{
		return false;
	}
	mSceneRoot->deserialize(xml);
	mSceneRoot->deserializeComponents(xml);
	xml.end();

	// Load Actors
	for (pugi::xml_node node : xml.getRootNode().children())
	{
		xml.setNode(node);
		Actor::Ptr actor = Factories::createActor(*this, std::string(node.name()));
		if (actor != nullptr)
		{
			actor->initializePhysic();
			if (actor->deserialize(xml))
			{
				actor->initialize();
				mActors.push_back(actor);
			}
		}
	}
	return true;
}

void Scene::saveToXml(const std::string& filepath)
{
	Serializer xml;
	xml.openDocument(filepath + "scene" + ((mId != "") ? "-" + mId : "") + ".xml", true, "Scene");

	// Save Scene
	xml.save("count", mActorIdCounter);
	xml.save("inputp", mInput.getPriority());
	if (usePhysic() && mPhysic != nullptr)
	{
		xml.save("pgrav", mPhysic->getGravity());
		xml.save("pxm", mPhysic->getPixelsPerMeter());
		xml.save("prdbg", mPhysic->isRenderingDebug());
		xml.save("prfla", mPhysic->getRenderFlags());
	}
	if (useLight() && mLights != nullptr)
	{
		xml.save("lrang", mLights->getDirectionEmissionRange());
		xml.save("lradm", mLights->getDirectionEmissionRadiusMultiplier());
		xml.save("lambc", mLights->getAmbientColor());
	}
	if (useEffect() && mEffects.size() > 0)
	{
		xml.create("Effects");
		for (auto itr = mEffects.begin(); itr != mEffects.end(); itr++)
		{
			if (itr->second != nullptr)
			{
				xml.create("Effect");
				xml.save("order", itr->first);
				xml.save("effect", itr->second->getType());
				xml.close();
			}
		}
		xml.close();
	}
	xml.create("View");
	xml.save("center", mView.getCenter());
	xml.save("size", mView.getSize());
	xml.save("rotation", mView.getRotation());
	xml.save("viewport", mView.getViewport());
	xml.close();

	xml.create("SceneRoot");
	mSceneRoot->serialize(xml);
	mSceneRoot->serializeComponents(xml);
	xml.close();

	// Save Actors
	for (std::size_t i = 0; i < mActors.size(); i++)
	{
		if (mActors[i] != nullptr && !mActors[i]->isMarkedForRemoval())
		{
			if (mActors[i] != mSceneRoot)
			{
				xml.create(mActors[i]->getType());
				mActors[i]->serialize(xml);
				xml.close();
			}
		}
	}
	xml.saveDocument();
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
	mLights = std::make_shared<ltbl::LightSystem>();
	mLights->create({ -1000.f, -1000.f, 2000.f, 2000.f }, getApplication().getSize());
}

void Scene::renderComplex(sf::RenderTarget& target)
{
	if (mSceneTexture == nullptr)
	{
		return;
	}

	// Update Texture
	sf::Vector2u size = target.getSize();
	if (mSceneTexture->getSize() != size)
	{
		mSceneTexture->create(size.x, size.y);
	}

	// Render Scene
	renderSimple(*mSceneTexture);

	// Render Lights
	if (useLight() && mLights != nullptr)
	{
		mLights->render(*mSceneTexture);
	}

	// Render Effects
	if (useEffect())
	{
		for (auto itr = mEffects.begin(); itr != mEffects.end(); itr++)
		{
			itr->second->apply(*mSceneTexture);
		}
	}

	// Display
	mSceneTexture->display();
	target.draw(sf::Sprite(mSceneTexture->getTexture()));
}

void Scene::renderSimple(sf::RenderTarget& target)
{
	target.setView(mView);

	mBackground.draw(target);

	std::sort(mActors.begin(), mActors.end(), sortActor);

	std::size_t size = mActors.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mActors[i] != nullptr && mActors[i]->isVisible())
		{
			mActors[i]->renderComponents(target);
			mActors[i]->render(target);
		}
	}
}

} // namespace ke