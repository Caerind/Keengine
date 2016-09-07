#ifndef KE_COMPONENT_HPP
#define KE_COMPONENT_HPP

#include <memory>
#include <string>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../Application/Application.hpp"

namespace ke
{

class Actor;
class Scene;
class Component
{
    public:
		typedef std::shared_ptr<Component> Ptr;

		Component(Actor& actor);
		virtual ~Component();

		virtual void onRegister();
		virtual void onUnregister();

		bool isUpdatable() const;
		virtual void update(sf::Time dt);

		sf::Vector2f getActorPosition() const;
		void setActorPosition(sf::Vector2f const& position);
		void setActorPosition(float x, float y);
		void moveActor(sf::Vector2f const& movement);
		void moveActor(float x, float y);

		float getActorRotation() const;
		void setActorRotation(float rotation);
		void rotateActor(float rotation);

		sf::Vector2f getActorScale() const;
		void setActorScale(sf::Vector2f const& scale);
		void setActorScale(float x, float y);
		void scaleActor(sf::Vector2f const& scale);
		void scaleActor(float x, float y);

		float getActorZ() const;
		void setActorZ(float z);
		void moveActorZ(float z);

		std::string getId() const;
		void setId(std::string const& id);

		Actor& getActor();
		Scene& getScene();

		Log& getLog();
		Application& getApplication();
		
	protected:
		Actor& mActor;

		std::string mId;

		bool mUpdatable;
};

} // namespace ke

#endif // KE_COMPONENT_HPP
