#ifndef KE_ACTOR_HPP
#define KE_ACTOR_HPP

#include <memory>
#include <vector>
#include <sstream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <Box2D\Dynamics\b2Body.h>

#include "Component.hpp"
#include "SceneComponent.hpp"

namespace ke
{

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

		void setId(std::string const& id);
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

		const sf::Transform& getTransform();

		float getZ() const;
		void setZ(float z);
		void moveZ(float z);

		virtual void update(sf::Time dt);
		void updateComponents(sf::Time dt);

		void attachComponent(SceneComponent* component);
		void detachComponent(SceneComponent* component);

		void registerComponent(Component* component);
		void unregisterComponent(Component* component);

		World& getWorld() const;

		b2Body* getBody();

		std::size_t getActualId();
		std::size_t getComponentCount() const;
		Component* getComponent(std::size_t index);
		Component* getComponent(std::string const& id);

		template <typename T>
		T* getTypedComponent(std::size_t index)
		{
			Component* c = getComponent(index);
			if (c == nullptr)
			{
				return nullptr;
			}
			return std::dynamic_cast<T*>(c);
		}

		template <typename T>
		T* getTypedComponent(std::string const& id)
		{
			Component* c = getComponent(id);
			if (c == nullptr)
			{
				return nullptr;
			}
			return std::dynamic_cast<T*>(c);
		}

	private:
		SceneComponent mRoot;
		std::vector<Component*> mComponents;

		bool mMarkedForRemoval;
		std::string mId;

		b2Body* mBody;

		std::size_t mIdCounter;
};

} // namespace ke

#endif // KE_ACTOR_HPP
