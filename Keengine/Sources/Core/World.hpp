#ifndef KE_WORLD_HPP
#define KE_WORLD_HPP

#include "../Config.hpp"

#include <cassert>
#include <memory>
#include <vector>

#include <SFML/System/Time.hpp>

#include "../Application/Application.hpp"

#include "Effect.hpp"
#include "InputSystem.hpp"
#include "TimeSystem.hpp"
#include "Scene.hpp"

#include "../ExtLibs/LTBL2/LightSystem.hpp"
#include "LightTextures.hpp"

namespace ke
{

class World
{
	public:
		static World& createInstance();
		static World& instance();
		static void destroyInstance();

	private:
		static World* mWorld;
		static bool mInstantiated;
		World();
		virtual ~World();

	public:
		Application& getApplication();
		InputSystem& getInputs();
		Log& getLog();
		ltbl::LightSystem& getLights();
		TimeSystem& getTime();

		PhysicSystem* getPhysic();
		b2World* getPhysicWorld();

		void newScene();
		template <typename T>
		void newSceneT()
		{
			if (mScene != nullptr)
			{
				mScene->onDestroy();
			}
			mScene = std::unique_ptr<T>(new T(this));
			if (mScene != nullptr)
			{
				mScene->onCreate();
			}
		}

		void initLights();

		virtual void handleEvent(sf::Event const& event);
		virtual void update(sf::Time dt);
		virtual void render(sf::RenderTarget& target);

		template <typename T, typename ... Args>
		std::shared_ptr<T> createActor(Args&& ... args)
		{
			if (mScene != nullptr)
			{
				return mScene->createActor<T>(std::forward<Args>(args)...);
			}
			return nullptr;
		}

		Actor::Ptr getActor(std::string const& id) const;
		Actor::Ptr getActor(std::size_t index) const;

		template <typename T>
		std::shared_ptr<T> getActorT(std::string const& id) const
		{
			if (mScene != nullptr)
			{
				return mScene.getActorT<T>(id);
			}
			return nullptr;
		}
		template <typename T>
		std::shared_ptr<T> getActorT(std::size_t index) const
		{
			if (mScene != nullptr)
			{
				return mScene.getActorT<T>(index);
			}
			return nullptr;
		}

		void removeActor(std::string const& id);
		void removeActor(std::size_t index);

		bool hasActor(std::string const& id) const;

		std::size_t getActorCount() const;

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

		sf::View* getView();

		template <typename T, typename ... Args>
		T& createResource(std::string const& id, Args&& ... args)
		{
			return Application::createResource<T>(id, std::forward<Args>(args)...);
		}
		template <typename T>
		T& getResource(std::string const& id)
		{
			return Application::getResource<T>(id);
		}
		bool hasResource(std::string const& id);
		bool isResourceLoaded(std::string const& id);
		void releaseResource(std::string const& id);
		void releaseAllResources();

	private:
		sf::RenderTexture mSceneTexture;
		sf::VertexArray mVertices;

		std::map<std::size_t, std::shared_ptr<Effect>> mEffects;

		InputSystem mInputs;

		sf::RectangleShape mBackground;

		bool mUsePhysic;

		bool mUseLights;
		ltbl::LightSystem mLights;

		TimeSystem mTime;

		Scene::Ptr mScene;
};

} // namespace ke

#endif // KE_WORLD_HPP