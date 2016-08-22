#ifndef KE_COMPONENT_HPP
#define KE_COMPONENT_HPP

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace ke
{

class Actor;
class World;
class Component
{
    public:
		Component();
		virtual ~Component();

		void registerComponent(Actor* actor);
		void unregisterComponent(Actor* actor = nullptr);
		bool isRegistered() const;

		virtual void onRegister();
		virtual void onUnregister();

		bool isUpdatable() const;
		virtual void update(sf::Time dt);

		sf::Vector2f getActorPosition() const;
		void setActorPosition(sf::Vector2f const& position);
		void moveActor(sf::Vector2f const& movement);

		float getActorRotation() const;
		void setActorRotation(float rotation);
		void rotateActor(float rotation);

		sf::Vector2f getActorScale() const;
		void setActorScale(sf::Vector2f const& scale);
		void scaleActor(sf::Vector2f const& scale);

		float getActorZ() const;
		void setActorZ(float z);
		void moveActorZ(float z);

		World& getWorld() const;
		
	private:
		bool mRegistered;

	protected:
		Actor* mActor;
		bool mUpdatable;
};

} // namespace ke

#endif // KE_COMPONENT_HPP
