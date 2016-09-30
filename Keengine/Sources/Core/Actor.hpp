#ifndef KE_ACTOR_HPP
#define KE_ACTOR_HPP

#include <memory>
#include <vector>
#include <sstream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Application/Application.hpp"

#include "../System/Serializable.hpp"

#include "Component.hpp"
#include "SceneComponent.hpp"
#include "../Components/Components.hpp"

namespace ke
{

class Scene;
class Actor : public Serializable
{
	public:
		typedef std::shared_ptr<Actor> Ptr;

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

		virtual void initializePhysic();
		virtual void initializeComponents();
		virtual void initialize();

		void render(sf::RenderTarget& target);

		void attachComponent(SceneComponent::Ptr component);
		void detachComponent(SceneComponent::Ptr component);

		std::size_t getComponentCount() const;
		Component::Ptr getComponent(std::size_t index);
		Component::Ptr getComponent(std::string const& id);

		template <typename T>
		std::shared_ptr<T> getComponentT(std::size_t index)
		{
			Component::Ptr c = getComponent(index);
			if (c == nullptr)
			{
				return nullptr;
			}
			return std::dynamic_pointer_cast<T>(c);
		}

		template <typename T>
		std::shared_ptr<T> getComponentT(std::string const& id)
		{
			Component::Ptr c = getComponent(id);
			if (c == nullptr)
			{
				return nullptr;
			}
			return std::dynamic_pointer_cast<T>(c);
		}

		Scene& getScene();

		b2Body* getBody();
		void destroyPhysic();
		void prePhysicUpdate();
		void postPhysicUpdate();
		void desiredImpulseX(float impulse);
		void desiredImpulseY(float impulse);
		void setVelocity(sf::Vector2f const& velocity);
		sf::Vector2f getVelocity() const;
		void setAngularVelocity(float angularVelocity);
		float getAngularVelocity() const;
		void setPhysicType(b2BodyType const& type);
		b2BodyType getPhysicType() const;
		void setFixedRotation(bool fixed);
		bool isFixedRotation() const;
		float getMass() const;
		float getInertia() const;
		void setLinearDamping(float damping);
		float getLinearDamping() const;
		void setAngularDamping(float damping);
		float getAngularDamping() const;
		void setGravityScale(float scale);
		float getGravityScale() const;
		void setPhysicBullet(bool bullet);
		bool isPhysicBullet() const;

		Log& getLog();
		Application& getApplication();

		template <typename T, typename ... Args>
		std::shared_ptr<T> createComponent(Args&& ... args)
		{
			std::shared_ptr<T> component = std::make_shared<T>(*this, std::forward<Args>(args)...);
			mComponents.push_back(component);
			component->setId(ke::decToHex(mComponentIdCounter++));
			component->onRegister();
			return component;
		}

		void removeComponent(Component::Ptr component);

	private:
		SceneComponent mRoot; ///< The root for scene components

		std::vector<Component::Ptr> mComponents; ///< All the registered components of this actor

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
