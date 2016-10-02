#include "ShapeComponent.hpp"
#include "../Core/Scene.hpp"
#include "../Core/Actor.hpp"
#include "../Core/PhysicSystem.hpp"

namespace ke
{

ShapeComponent::ShapeComponent(Actor& actor, sf::Uint32 options)
	: SceneComponent(actor)
	, mOptions(options)
	, mPoints()
	, mShape()
	, mFixture(nullptr)
	, mLightShape(nullptr)
{
	mUpdatable = false;
}

void ShapeComponent::onRegister()
{
	mShape.setFillColor(sf::Color::Transparent);
	mShape.setOutlineColor(sf::Color::Transparent);

	b2Body* actorBody = mActor.getBody();
	if (usePhysic() && actorBody != nullptr && mFixture == nullptr)
	{
		b2FixtureDef fDef;
		if ((mOptions & Options::Trigger) != 0)
		{
			fDef.isSensor = true;
		}
		b2PolygonShape shape;
		fDef.shape = &shape;
		mFixture = actorBody->CreateFixture(&fDef);
		mFixture->SetUserData(this);
	}

	if (useLight() && mLightShape == nullptr)
	{
		mLightShape = getScene().getLights().createLightShape();
	}
}

void ShapeComponent::onUnregister()
{
	b2Body* actorBody = mActor.getBody();
	if (usePhysic() && actorBody != nullptr && mFixture != nullptr)
	{
		actorBody->SetUserData(nullptr);
		actorBody->DestroyFixture(mFixture);
		mFixture = nullptr;
	}

	if (useLight() && mLightShape != nullptr)
	{
		getScene().getLights().removeShape(mLightShape);
		mLightShape = nullptr;
	}
}

bool ShapeComponent::useGraphic()
{
	return ((mOptions & Options::Graphic) != 0);
}

bool ShapeComponent::usePhysic()
{
	return (((mOptions & Options::Physic) != 0 || (mOptions & Options::Trigger) != 0) && getScene().usePhysic());
}

bool ShapeComponent::useLight()
{
	return ((mOptions & Options::Light) != 0 && getScene().useLight());
}

void ShapeComponent::setPointCount(std::size_t points)
{
	mPoints.resize(points, sf::Vector2f());
	mShape.setPointCount(points);
	updatePhysicShape();
	if (mLightShape != nullptr)
	{
		mLightShape->setPointCount(points);
	}
}

std::size_t ShapeComponent::getPointCount() const
{
	return mPoints.size();
}

void ShapeComponent::setPoint(std::size_t index, sf::Vector2f const& point)
{
	mPoints[index] = point;
	mShape.setPoint(index, point);
	updatePhysicShape();
	if (mLightShape != nullptr)
	{
		mLightShape->setPoint(index, point);
	}
}

sf::Vector2f ShapeComponent::getPoint(std::size_t index) const
{
	return mPoints[index];
}

void ShapeComponent::setOutlineThickness(float thickness)
{
	mShape.setOutlineThickness(thickness);
}

float ShapeComponent::getOutlineThickness() const
{
	return mShape.getOutlineThickness();
}

void ShapeComponent::setOutlineColor(sf::Color const& color)
{
	mShape.setOutlineColor(color);
}

sf::Color ShapeComponent::getOutlineColor() const
{
	return mShape.getOutlineColor();
}

void ShapeComponent::setFillColor(sf::Color const& color)
{
	mShape.setFillColor(color);
}

sf::Color ShapeComponent::getFillColor() const
{
	return mShape.getFillColor();
}

sf::FloatRect ShapeComponent::getLocalBounds()
{
	return getTransform().transformRect(mShape.getLocalBounds());
}

sf::FloatRect ShapeComponent::getGlobalBounds()
{
	return getWorldTransform().transformRect(mShape.getLocalBounds());
}

b2Fixture* ShapeComponent::getFixture()
{
	return mFixture;
}

b2Shape* ShapeComponent::getShape()
{
	if (mFixture != nullptr)
	{
		return mFixture->GetShape();
	}
	return nullptr;
}

b2PolygonShape* ShapeComponent::getPolygonShape()
{
	if (mFixture != nullptr)
	{
		return dynamic_cast<b2PolygonShape*>(mFixture->GetShape());
	}
	return nullptr;
}

void ShapeComponent::setDensity(float density)
{
	if (mFixture != nullptr)
	{
		mFixture->SetDensity(density);
	}
}

float ShapeComponent::getDensity() const
{
	if (mFixture != nullptr)
	{
		return mFixture->GetDensity();
	}
	return 0.0f;
}

void ShapeComponent::setPoints(const std::vector<sf::Vector2f>& points)
{
	std::size_t count = points.size();
	mPoints.resize(count, sf::Vector2f());
	mShape.setPointCount(count);
	if (mLightShape != nullptr)
	{
		mLightShape->setPointCount(count);
	}
	for (std::size_t i = 0; i < count; i++)
	{
		sf::Vector2f p = points[i];
		mPoints[i] = p;
		mShape.setPoint(i, p);
		if (mLightShape != nullptr)
		{
			mLightShape->setPoint(i, p);
		}
	}
	updatePhysicShape();
}

std::vector<sf::Vector2f> ShapeComponent::getPoints() const
{
	return mPoints;
}

void ShapeComponent::serialize(Serializer& serializer)
{
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("options", mOptions);
	serializer.save("pos", getPosition());
	serializer.save("rot", getRotation());
	serializer.save("sca", getScale());
	serializer.save("z", getZ());
	serializer.save("visible", isVisible());
	serializer.save("fillColor", getFillColor());
	serializer.save("outColor", getOutlineColor());
	serializer.save("outThick", getOutlineThickness());
	serializer.save("points", getPoints());
	serializer.end();
}

bool ShapeComponent::deserialize(Serializer & serializer, const std::string & identifier)
{
	return false;
}

void ShapeComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	if (useGraphic())
	{
		target.draw(mShape, states);
	}
}

void ShapeComponent::onTransformUpdated()
{
	// TODO : Update physic

	if (mLightShape != nullptr)
	{
		mLightShape->setPosition(getWorldPosition());
		mLightShape->setRotation(getRotation());
		mLightShape->setScale(getScale());
	}
}

void ShapeComponent::updatePhysicShape()
{
	if (mFixture != nullptr)
	{
		b2PolygonShape* polygon = getPolygonShape();
		if (polygon != nullptr)
		{
			b2Vec2 vertices[8];
			std::size_t count = mPoints.size();
			for (std::size_t i = 0; i < count; i++)
			{
				vertices[i] = mPoints[i] * ke::Physic::conv;
			}
			polygon->Set(vertices, count);
		}
	}
}

} // namespace ke