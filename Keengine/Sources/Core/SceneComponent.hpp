#ifndef SCENECOMPONENT_HPP
#define SCENECOMPONENT_HPP

#include <vector>

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Component.hpp"

class SceneComponent : public Component
{
    public:
		SceneComponent();
		virtual ~SceneComponent();

		const sf::Vector2f& getPosition() const;
		void setPosition(sf::Vector2f const& position);
		void move(sf::Vector2f const& movement);

		float getRotation() const;
		void setRotation(float rotation);
		void rotate(float rotation);

		const sf::Vector2f& getScale() const;
		void setScale(sf::Vector2f const& scale);
		void scale(sf::Vector2f const& scale);

		const sf::Transform& getTransform() const;

		float getZ() const;
		void setZ(float z);
		void moveZ(float z);

		sf::Vector2f getWorldPosition();
		const sf::Transform& getWorldTransform();
		float getWorldZ();

		void attachComponent(SceneComponent* component);
		void detachComponent(SceneComponent* component);

	protected:
		virtual void onChangedTransform();
		virtual void onChangedZ();

	private:
		sf::Transformable mTransformable;
		float mZ;

		sf::Transform mWorldTransform;
		float mWorldZ;

		bool mTransformChanged;
		bool mZChanged;

	protected:
		SceneComponent* mParent;
		std::vector<SceneComponent*> mChildren;
};

#endif // SCENECOMPONENT_HPP
