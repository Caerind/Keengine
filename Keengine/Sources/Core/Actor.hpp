#ifndef KE_ACTOR_HPP
#define KE_ACTOR_HPP

#include <memory>
#include <vector>
#include <sstream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Application/Application.hpp"

#include "Component.hpp"
#include "SceneComponent.hpp"
#include "../Components/Components.hpp"

namespace ke
{

class Scene;
class Actor
{
	public:
		typedef std::shared_ptr<Actor> Ptr;

    public:
		Actor(Scene& scene);
		virtual ~Actor();

		void remove();
		bool isMarkedForRemoval() const;

		void setId(std::string const& id);
		std::string getId() const;

		std::string getType() const;

		const sf::Vector2f& getPosition() const;
		void setPosition(sf::Vector2f const& position);
		void setPosition(float x, float y);
		void move(sf::Vector2f const& movement);
		void move(float x, float y);

		float getRotation() const;
		void setRotation(float rotation);
		void rotate(float rotation);

		const sf::Vector2f& getScale() const;
		void setScale(sf::Vector2f const& scale);
		void setScale(float x, float y);
		void scale(sf::Vector2f const& scale);
		void scale(float x, float y);

		const sf::Transform& getTransform();

		float getZ() const;
		void setZ(float z);
		void moveZ(float z);

		bool isVisible() const;
		void setVisible(bool visible);

		virtual void update(sf::Time dt);
		void updateComponents(sf::Time dt);

		void render(sf::RenderTarget& target);

		void attachComponent(SceneComponent* component);
		void detachComponent(SceneComponent* component);

		void registerComponent(Component* component);
		void unregisterComponent(Component* component);
		void unregisterComponents();

		std::size_t getComponentCount() const;
		Component* getComponent(std::size_t index);
		Component* getComponent(std::string const& id);

		template <typename T>
		T* getComponentT(std::size_t index)
		{
			Component* c = getComponent(index);
			if (c == nullptr)
			{
				return nullptr;
			}
			return dynamic_cast<T*>(c);
		}

		template <typename T>
		T* getComponentT(std::string const& id)
		{
			Component* c = getComponent(id);
			if (c == nullptr)
			{
				return nullptr;
			}
			return dynamic_cast<T*>(c);
		}

		Scene& getScene();

		b2Body* getBody();
		void initializePhysic();
		void destroyPhysic();
		void prePhysicUpdate();
		void postPhysicUpdate();

		Log& getLog();
		Application& getApplication();

	private:
		SceneComponent mRoot; ///< The root for scene components

		std::vector<Component*> mComponents; ///< All the registered components of this actor

		bool mMarkedForRemoval; ///< Do the Actor need to be removed ?

		std::string mId; ///< The ID of the Actor

		std::size_t mComponentIdCounter; ///< The ID generator for registered components

	protected:
		Scene& mScene; ///< Scene where the actor lives in

		std::string mType; ///< Type of the object

		b2Body* mBody; ///< Physic body
};

} // namespace ke

#endif // KE_ACTOR_HPP
