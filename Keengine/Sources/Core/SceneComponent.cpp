#include "SceneComponent.hpp"

SceneComponent::SceneComponent()
	: mTransformable()
	, mZ(0.f)
	, mWorldTransform()
	, mWorldZ(0.f)
	, mTransformChanged(true)
	, mZChanged(true)
	, mParent(nullptr)
	, mChildren()
{
}

SceneComponent::~SceneComponent()
{
}

const sf::Vector2f& SceneComponent::getPosition() const
{
	return mTransformable.getPosition();
}

void SceneComponent::setPosition(sf::Vector2f const& position)
{
	mTransformable.setPosition(position);
	onChangedTransform();
}

void SceneComponent::move(sf::Vector2f const& movement)
{
	mTransformable.move(movement);
	onChangedTransform();
}

float SceneComponent::getRotation() const
{
	return mTransformable.getRotation();
}

void SceneComponent::setRotation(float rotation)
{
	mTransformable.setRotation(rotation);
	onChangedTransform();
}

void SceneComponent::rotate(float rotation)
{
	mTransformable.rotate(rotation);
	onChangedTransform();
}

const sf::Vector2f& SceneComponent::getScale() const
{
	return mTransformable.getScale();
}

void SceneComponent::setScale(sf::Vector2f const& scale)
{
	mTransformable.setScale(scale);
	onChangedTransform();
}

void SceneComponent::scale(sf::Vector2f const& scale)
{
	mTransformable.setScale(scale);
	onChangedTransform();
}

float SceneComponent::getZ() const
{
	return mZ;
}

void SceneComponent::setZ(float z)
{
	mZ = z;
	onChangedZ();
}

void SceneComponent::moveZ(float z)
{
	mZ += z;
	onChangedZ();
}

sf::Vector2f SceneComponent::getWorldPosition()
{
	return getWorldTransform().transformPoint(sf::Vector2f());
}

const sf::Transform& SceneComponent::getWorldTransform()
{
	if (mTransformChanged)
	{
		mWorldTransform = (mParent != nullptr) ? mParent->getWorldTransform() : sf::Transform();
		mWorldTransform *= mTransformable.getTransform();
		mTransformChanged = false;
	}
	return mWorldTransform;
}

float SceneComponent::getWorldZ()
{
	if (mZChanged)
	{
		mWorldZ = (mParent != nullptr) ? mParent->getWorldZ() : 0.f;
		mWorldZ += mZ;
		mZChanged = false;
	}
	return mWorldZ;
}

void SceneComponent::attachComponent(SceneComponent* component)
{
	if (component != nullptr)
	{
		component->mParent = this;
		component->onChangedTransform();
		component->onChangedZ();
		mChildren.push_back(component);
	}
}

void SceneComponent::detachComponent(SceneComponent* component)
{
	if (component != nullptr)
	{
		std::size_t size = mChildren.size();
		for (std::size_t i = 0; i < size; i++)
		{ 
			if (mChildren[i] == component)
			{
				if (component->mParent == this)
				{
					component->mParent = nullptr;
				}
				component->onChangedTransform();
				component->onChangedZ();
				mChildren.erase(i + mChildren.begin());
				size--;
			}
		}

	}
}

void SceneComponent::onChangedTransform()
{
	mTransformChanged = true;
	std::size_t size = mChildren.size();
	for (std::size_t i = 0; i < size; i++)
	{
		mChildren[i]->onChangedTransform();
	}
}

void SceneComponent::onChangedZ()
{
	mZChanged = true;
	std::size_t size = mChildren.size();
	for (std::size_t i = 0; i < size; i++)
	{
		mChildren[i]->onChangedZ();
	}
}
