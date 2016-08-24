#ifndef KE_WORLD_HPP
#define KE_WORLD_HPP

#include "../Config.hpp"

#include <cassert>
#include <memory>
#include <vector>

#include <SFML/System/Time.hpp>

#include "../Application/Application.hpp"

#include "Actor.hpp"
#include "Effect.hpp"
#include "InputSystem.hpp"
#include "PhysicSystem.hpp"
#include "PrimitiveComponent.hpp"

#include "../ExtLibs/LTBL2/LightSystem.hpp"

#include "../Components/CameraComponent.hpp"

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
		PhysicSystem& getPhysic();
		b2World* getPhysicWorld();

		virtual void handleEvent(sf::Event const& event);
		virtual void update(sf::Time dt);
		virtual void render(sf::RenderTarget& target);

		void registerPrimitive(PrimitiveComponent* component);
		void unregisterPrimitive(PrimitiveComponent* component);

		template <typename T, typename ... Args>
		std::shared_ptr<T> createActor(Args&& ... args)
		{
			std::shared_ptr<T> actor = std::make_shared<T>(std::forward<Args>(args)...);
			instance().mActors.push_back(actor);
			actor->onCreated();
			return actor;
		}

		void removeActor(std::string const& id);
		void removeActor(std::size_t index);

		bool hasActor(std::string const& id) const;

		Actor::Ptr getActor(std::string const& id) const;
		Actor::Ptr getActor(std::size_t index) const;
		template <typename T>
		std::shared_ptr<T> getTypedActor(std::string const& id) const
		{
			Actor::Ptr actor = getActor(id);
			if (actor == nullptr)
			{
				return nullptr;
			}
			return std::dynamic_pointer_cast<T>(actor);
		}
		template <typename T>
		std::shared_ptr<T> getTypedActor(std::size_t index) const
		{
			Actor::Ptr actor = getActor(index);
			if (actor == nullptr)
			{
				return nullptr;
			}
			return std::dynamic_pointer_cast<T>(actor);
		}

		std::size_t getActorCount() const;

		std::size_t getActualId();

		sf::Time getTimeSinceCreation() const;

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
				return static_cast<std::shared_ptr<T>>(itr->second);
			}
			return nullptr;
		}

		void removeEffect(std::size_t const& order);

		sf::View& getView();
		void registerCamera(CameraComponent* camera);
		void unregisterCamera(CameraComponent* camera);

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
		std::size_t mIdCounter;
		std::vector<Actor::Ptr> mActors;
		std::vector<PrimitiveComponent*> mPrimitives;

		sf::RenderTexture mSceneTexture;
		sf::VertexArray mVertices;

		sf::Clock mClockCreation;

		CameraComponent* mCamera;
		sf::View mWorldView;

		std::map<std::size_t, std::shared_ptr<Effect>> mEffects;

		InputSystem mInputs;

		bool mUsePhysic;
		PhysicSystem mPhysic;

		sf::RectangleShape mBackground;

		bool mUseLights;
		ltbl::LightSystem mLights;
	};

} // namespace ke

#endif // KE_WORLD_HPP