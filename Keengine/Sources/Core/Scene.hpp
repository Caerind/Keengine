#ifndef KE_SCENE_HPP
#define KE_SCENE_HPP

#include "../Config.hpp"

#include <cassert>
#include <memory>
#include <vector>

#include <SFML/System/Time.hpp>

#include "Actor.hpp"
#include "PhysicSystem.hpp"

namespace ke
{

class Scene
{
	public:
		typedef std::unique_ptr<Scene> Ptr;

		Scene(World* world = nullptr);
		virtual ~Scene();

		virtual void onCreate();
		virtual void onDestroy();

		void update(sf::Time dt);
		void render(sf::RenderTarget& target);

		void renderPhysic(sf::RenderTarget& target);

		PhysicSystem& getPhysic();
		b2World* getPhysicWorld();

		template <typename T, typename ... Args>
		std::shared_ptr<T> createActor(Args&& ... args)
		{
			std::shared_ptr<T> actor = std::make_shared<T>(std::forward<Args>(args)...);
			mActors.push_back(actor);
			actor->setWorld(mWorld);
			if (mUsePhysic)
			{
				actor->initializePhysic();
			}
			actor->setId(ke::decToHex<std::size_t>(mActorIdCounter++));
			return actor;
		}

		Actor::Ptr getActor(std::string const& id) const;
		Actor::Ptr getActor(std::size_t index) const;

		void removeActor(std::string const& id);
		void removeActor(std::size_t index);

		bool hasActor(std::string const& id) const;

		template <typename T>
		std::shared_ptr<T> getActorT(std::string const& id) const
		{
			Actor::Ptr actor = getActor(id);
			if (actor == nullptr)
			{
				return nullptr;
			}
			return std::dynamic_pointer_cast<T>(actor);
		}

		template <typename T>
		std::shared_ptr<T> getActorT(std::size_t index) const
		{
			Actor::Ptr actor = getActor(index);
			if (actor == nullptr)
			{
				return nullptr;
			}
			return std::dynamic_pointer_cast<T>(actor);
		}

		std::size_t getActorCount() const;

		sf::View& getView();

		static bool sortActor(Actor::Ptr a, Actor::Ptr b);

	protected:
		World* mWorld;

		std::size_t mActorIdCounter;

		std::vector<Actor::Ptr> mActors;

		sf::View mView;

		PhysicSystem mPhysic;

		bool mUsePhysic;
};

} // namespace ke

#endif // KE_SCENE_HPP