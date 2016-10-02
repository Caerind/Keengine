#ifndef KE_SCENE_HPP
#define KE_SCENE_HPP

#include "../Config.hpp"

#include <cassert>
#include <memory>
#include <vector>

#include <SFML/System/Time.hpp>

#include "../Application/Application.hpp"

#include "Actor.hpp"
#include "PhysicSystem.hpp"
#include "../ExtLibs/LetThereBeLight.hpp"
#include "LightTextures.hpp"
#include "Effect.hpp"

namespace ke
{

class Scene
{
	public:
		typedef std::unique_ptr<Scene> Ptr;

		enum Options
		{
			None = 0,
			Physic = 1 << 0,
			Effect = 1 << 1,
			Light = 1 << 2,
		};

		Scene(sf::Uint32 options = Options::None);
		virtual ~Scene();

		void handleEvent(sf::Event const& event);
		void update(sf::Time dt);
		void render(sf::RenderTarget& target);

		bool usePhysic() const;
		bool useEffect() const;
		bool useLight() const;

		PhysicSystem& getPhysic();
		b2World* getPhysicWorld();

		ltbl::LightSystem& getLights();

		template <typename T, typename ... Args>
		std::shared_ptr<T> createActor(std::string const& actorId, Args&& ... args)
		{
			std::shared_ptr<T> actor = std::make_shared<T>(*this, std::forward<Args>(args)...);
			if (actorId == "")
			{
				actor->setId(ke::decToHex<std::size_t>(mActorIdCounter++));
			}
			else
			{
				actor->setId(actorId);
			}
			actor->initializePhysic();
			actor->initializeComponents();
			actor->initialize();
			mActors.push_back(actor);
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

		template <typename T>
		void setEffect(std::size_t const& order)
		{
			mEffects[order] = std::make_shared<T>();
		}

		template <typename T>
		std::shared_ptr<T> getEffect(std::size_t const& order)
		{
			auto itr = mEffects.find(order);
			if (itr != mEffects.end())
			{
				return std::dynamic_pointer_cast<T>(itr->second);
			}
			return nullptr;
		}

		void removeEffect(std::size_t const& order);

		Log& getLog();
		Application& getApplication();

		Input& getInput();

		template <typename T, typename ... Args>
		std::shared_ptr<T> createComponent(Args&& ... args)
		{
			if (mSceneRoot != nullptr)
			{
				return mSceneRoot->createComponent<T>(std::forward<Args>(args)...);
			}
			return nullptr;
		}

		void attachComponent(SceneComponent::Ptr component);
		void detachComponent(SceneComponent::Ptr component);

		void removeComponent(Component::Ptr component);

		bool loadFromXml(const std::string& filename);
		void saveToXml(const std::string& filename);

	private:
		static bool sortActor(Actor::Ptr a, Actor::Ptr b);

		void initLights();

		void renderComplex(sf::RenderTarget& target);
		void renderSimple(sf::RenderTarget& target);

	protected:
		sf::Uint32 mOptions;

		std::size_t mActorIdCounter;

		std::vector<Actor::Ptr> mActors;

		sf::View mView;

		PhysicSystem mPhysic;

		ltbl::LightSystem mLights;

		sf::RenderTexture mSceneTexture;

		std::map<std::size_t, std::shared_ptr<ke::Effect>> mEffects;

		Input mInput;

		Actor::Ptr mSceneRoot;
};

} // namespace ke

#endif // KE_SCENE_HPP