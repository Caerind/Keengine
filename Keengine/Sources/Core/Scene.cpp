#include "Scene.hpp"

namespace ke
{

Scene::Scene(World* world)
	: mWorld(world)
	, mActorIdCounter(1)
	, mActors()
	, mView()
	, mPhysic()
	, mUsePhysic(false)
{
}

Scene::~Scene()
{
	mActors.clear();
}

void Scene::onCreate()
{
}

void Scene::onDestroy()
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

				if (mUsePhysic)
				{
					mActors[i]->prePhysicUpdate();
				}
			}
		}
	}

	if (mUsePhysic)
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
	target.setView(mView);

	std::sort(mActors.begin(), mActors.end(), sortActor);

	std::size_t size = mActors.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mActors[i] = nullptr)
		{
			if (mActors[i]->isVisible())
			{
				mActors[i]->render(target);
			}
		}
	}
}

void Scene::renderPhysic(sf::RenderTarget& target)
{
	if (mUsePhysic)
	{
		mPhysic.render(target);
	}
}

PhysicSystem& Scene::getPhysic()
{
	return mPhysic;
}

b2World* Scene::getPhysicWorld()
{
	return mPhysic.getWorld();
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

} // namespace ke