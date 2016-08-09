#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <memory>
#include <vector>
#include <sstream>

#include <SFML/System/Vector2.hpp>

#include "Component.hpp"
#include "SceneComponent.hpp"

class World;
class Actor
{
	public:
		typedef std::shared_ptr<Actor> Ptr;

    public:
		Actor(std::string const& id = "");
		virtual ~Actor();

		void remove();
		bool isMarkedForRemoval() const;

		virtual void onCreated();
		virtual void onDestroyed();

		std::string getId() const;

		const sf::Vector2f& getPosition() const;
		void setPosition(sf::Vector2f const& position);
		void move(sf::Vector2f const& movement);

		float getRotation() const;
		void setRotation(float rotation);
		void rotate(float rotation);

		const sf::Vector2f& getScale() const;
		void setScale(sf::Vector2f const& scale);
		void scale(sf::Vector2f const& scale);

		float getZ() const;
		void setZ(float z);
		void moveZ(float z);

		virtual void update(float dt);
		void updateComponents(float dt);

		void attachComponent(SceneComponent* component);
		void detachComponent(SceneComponent* component);

		void registerComponent(Component* component);
		void unregisterComponent(Component* component);

		World& getWorld() const;
		
	private:
		SceneComponent mRoot;
		std::vector<Component*> mComponents;

		bool mMarkedForRemoval;
		std::string mId;
};

#endif // ACTOR_HPP