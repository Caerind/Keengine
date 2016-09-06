#include "SceneComponent.hpp"

namespace ke
{

SceneComponent::SceneComponent()
	: mTransformable()
	, mWorldTransform()
	, mNeedUpdate(true)
	, mZ(0.f)
	, mParent(nullptr)
	, mChildren()
	, mVisible(true)
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
	onTransformChanged();
}

void SceneComponent::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

void SceneComponent::move(sf::Vector2f const& movement)
{
	mTransformable.move(movement);
	onTransformChanged();
}

void SceneComponent::move(float x, float y)
{
	move(sf::Vector2f(x, y));
}

float SceneComponent::getRotation() const
{
	return mTransformable.getRotation();
}

void SceneComponent::setRotation(float rotation)
{
	mTransformable.setRotation(rotation);
	onTransformChanged();
}

void SceneComponent::rotate(float rotation)
{
	mTransformable.rotate(rotation);
	onTransformChanged();
}

const sf::Vector2f& SceneComponent::getScale() const
{
	return mTransformable.getScale();
}

void SceneComponent::setScale(sf::Vector2f const& scale)
{
	mTransformable.setScale(scale);
	onTransformChanged();
}

void SceneComponent::setScale(float x, float y)
{
	setScale(sf::Vector2f(x, y));
}

void SceneComponent::scale(sf::Vector2f const& scale)
{
	mTransformable.setScale(scale);
	onTransformChanged();
}

void SceneComponent::scale(float x, float y)
{
	scale(sf::Vector2f(x, y));
}

const sf::Transform& SceneComponent::getTransform() const
{
	return mTransformable.getTransform();
}

float SceneComponent::getZ() const
{
	return mZ;
}

void SceneComponent::setZ(float z)
{
	mZ = z;
}

void SceneComponent::moveZ(float z)
{
	mZ += z;
}

sf::Vector2f SceneComponent::getWorldPosition() const
{
	return mWorldTransform.transformPoint(sf::Vector2f());
}

const sf::Transform& SceneComponent::getWorldTransform() const
{
	return mWorldTransform;
}

void SceneComponent::setVisible(bool visible)
{
	mVisible = visible;
}

bool SceneComponent::isVisible() const
{
	return mVisible;
}

void SceneComponent::render(sf::RenderTarget& target, sf::RenderStates states)
{
	if (isVisible())
	{
		states.transform *= getTransform();
		renderCurrent(target, states);
		renderChildren(target, states);
	}
}

void SceneComponent::attachComponent(SceneComponent* component)
{
	if (component != nullptr)
	{
		component->mParent = this;
		component->onTransformChanged();
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
				component->mParent = nullptr;
				component->onTransformChanged();
				mChildren.erase(i + mChildren.begin());
				return;
			}
		}
	}
}

void SceneComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
}

void SceneComponent::renderChildren(sf::RenderTarget& target, sf::RenderStates states)
{
	if (isVisible())
	{
		std::sort(mChildren.begin(), mChildren.end(), sortChildren);

		std::size_t size = mChildren.size();
		for (std::size_t i = 0; i < size; i++)
		{
			if (mChildren[i] != nullptr)
			{
				if (mChildren[i]->isRegistered() && mChildren[i]->isVisible())
				{
					mChildren[i]->render(target, states);
				}
			}
		}
	}
}

bool SceneComponent::sortChildren(SceneComponent * a, SceneComponent * b)
{
	if (a != nullptr && b != nullptr)
	{
		if (a->getZ() < b->getZ())
		{
			return true;
		}
		else if (a->getZ() > b->getZ())
		{
			return false;
		}
		else if (a->getWorldPosition().y < b->getWorldPosition().y)
		{
			return true;
		}
		else if (a->getWorldPosition().y > b->getWorldPosition().y)
		{
			return false;
		}
		else
		{
			return (a->getWorldPosition().x < b->getWorldPosition().x);
		}
	}
	return true;
}

void SceneComponent::onTransformChanged()
{
	mWorldTransform = (mParent != nullptr) ? mParent->getWorldTransform() : sf::Transform();
	mWorldTransform *= mTransformable.getTransform();
	std::size_t size = mChildren.size();
	for (std::size_t i = 0; i < size; i++)
	{
		mChildren[i]->onTransformChanged();
	}
	onTransformUpdated();
}

void SceneComponent::onTransformUpdated()
{
}

} // namespace ke