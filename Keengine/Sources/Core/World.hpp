#ifndef WORLD_HPP
#define WORLD_HPP

#include <cassert>
#include <memory>
#include <vector>

#include <SFML/System/Time.hpp>

#include "../Application/Application.hpp"

#include "Actor.hpp"
#include "Effect.hpp"
#include "PrimitiveComponent.hpp"

#include "../Components/CameraComponent.hpp"

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
		Log& getLog();

		virtual void handleEvent(sf::Event const& event);
		virtual void update(sf::Time dt);
		virtual void render(sf::RenderTarget& target);

		void registerPrimitive(PrimitiveComponent* component);
		void unregisterPrimitive(PrimitiveComponent* component);

		template <typename T, typename ... Args>
		std::shared_ptr<T> createActor(Args&& ... args);

		void removeActor(std::string const& id);
		void removeActor(std::size_t index);

		bool hasActor(std::string const& id) const;

		Actor::Ptr getActor(std::string const& id) const;
		Actor::Ptr getActor(std::size_t index) const;

		std::size_t getActorCount() const;

		std::size_t getActualId();

		sf::Time getTimeSinceCreation() const;

		template <typename T>
		void setEffect(std::size_t const& order);

		template <typename T>
		std::shared_ptr<T> getEffect(std::size_t const& order);

		void removeEffect(std::size_t const& order);

		sf::View& getView();
		void registerCamera(CameraComponent* camera);
		void unregisterCamera(CameraComponent* camera);

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
};

#endif // WORLD_HPP

template <typename T, typename ... Args>
std::shared_ptr<T> World::createActor(Args&& ...args)
{
	std::shared_ptr<T> actor = std::make_shared<T>(std::forward<Args>(args)...);
	instance().mActors.push_back(actor);
	actor->onCreated();
	return actor;
}

template <typename T>
void World::setEffect(std::size_t const& order)
{
	mEffects[order] = std::make_shared<T>();
}

template <typename T>
std::shared_ptr<T> World::getEffect(std::size_t const& order)
{
	auto itr = mEffects.find(order);
	if (itr != mEffects.end())
	{
		return static_cast<std::shared_ptr<T>>(itr->second);
	}
	return nullptr;
}