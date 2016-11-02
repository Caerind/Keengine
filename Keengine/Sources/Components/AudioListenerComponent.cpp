#include "AudioListenerComponent.hpp"

namespace ke
{

AudioListenerComponent::AudioListenerComponent(Actor& actor)
	: SceneComponent(actor)
{
}

AudioListenerComponent::~AudioListenerComponent()
{
	onUnregister();
}

void AudioListenerComponent::setGlobalVolume(float volume)
{
	sf::Listener::setGlobalVolume(volume);
}

float AudioListenerComponent::getGlobalVolume() const
{
	return sf::Listener::getGlobalVolume();
}

void AudioListenerComponent::setDirection(float x, float y, float z)
{
	sf::Listener::setDirection(x, y, z);
}

void AudioListenerComponent::setDirection(const sf::Vector3f& dir)
{
	sf::Listener::setDirection(dir);
}

sf::Vector3f AudioListenerComponent::getDirection() const
{
	return sf::Listener::getDirection();
}

void AudioListenerComponent::setUpVector(float x, float y, float z)
{
	sf::Listener::setUpVector(x, y, z);
}

void AudioListenerComponent::setUpVector(const sf::Vector3f& up)
{
	sf::Listener::setUpVector(up);
}

sf::Vector3f AudioListenerComponent::getUpVector() const
{
	return sf::Listener::getUpVector();
}

void AudioListenerComponent::onTransformNotified()
{
	sf::Listener::setPosition(ke::toVector3f(getWorldPosition()));
}

void AudioListenerComponent::serialize(Serializer& serializer)
{
	SceneComponent::serialize(serializer);
	serializer.save("volume", getGlobalVolume());
	serializer.save("direction", getDirection());
	serializer.save("upvector", getUpVector());
}

bool AudioListenerComponent::deserialize(Serializer& serializer)
{
	float volume;
	sf::Vector3f direction;
	sf::Vector3f upvector;
	if (SceneComponent::deserialize(serializer)
		&& serializer.load("volume", volume)
		&& serializer.load("direction", direction)
		&& serializer.load("upvector", upvector))
	{
		setGlobalVolume(volume);
		setDirection(direction);
		setUpVector(upvector);
		return true;
	}
	return false;
}

} // namespace ke
