#include "AnimatorComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

Animation::Animation()
{
}

void Animation::addFrame(Frame const& frame)
{
	mFrames.push_back(frame);
}

void Animation::addFrame(std::string const& textureName, sf::IntRect const& textureRect, sf::Time duration)
{
	Frame frame;
	frame.textureName = textureName;
	frame.textureRect = textureRect;
	frame.duration = duration;
	addFrame(frame);
}

std::size_t Animation::getFrameCount() const
{
	return mFrames.size();
}

Frame& Animation::getFrame(std::size_t index)
{
	return mFrames.at(index);
}

void Animation::removeFrame(std::size_t index)
{
	mFrames.erase(mFrames.begin() + index);
}

void Animation::removeAllFrames()
{
	mFrames.clear();
}

sf::Time Animation::getDuration() const
{
	sf::Time duration;
	for (const auto& f : mFrames)
	{
		duration += f.duration;
	}
	return duration;
}

AnimatorComponent::AnimatorComponent(Actor& actor)
	: SceneComponent(actor)
	, mPlaying(false)
	, mSprite()
	, mAnimations()
	, mActualTexture()
	, mActualAnimation()
	, mActualFrame()
	, mTimeElapsed()
{
}

AnimatorComponent::~AnimatorComponent()
{
	onUnregister();
}

bool AnimatorComponent::updatable() const
{
	return true;
}

bool AnimatorComponent::renderable() const
{
	return true;
}

std::size_t AnimatorComponent::getAnimationCount() const
{
	return mAnimations.size();
}

Animation& AnimatorComponent::getAnimation(std::string const& name)
{
	return mAnimations[name];
}

void AnimatorComponent::removeAnimation(std::string const& name)
{
	mAnimations.erase(mAnimations.find(name));
}

void AnimatorComponent::removeAllAnimations()
{
	mAnimations.clear();
}

bool AnimatorComponent::isPlaying() const
{
	return mPlaying;
}

void AnimatorComponent::playAnimation(std::string const& name)
{
	mActualFrame = 0;
	mTimeElapsed = sf::Time::Zero;
	if (mAnimations.find(name) != mAnimations.end())
	{
		mActualAnimation = name;
		mActualTexture = getActualFrame().textureName;
		mSprite.setTexture(getApplication().getResource<Texture>(mActualTexture));
		mSprite.setTextureRect(getActualFrame().textureRect);
		mPlaying = true;
	}
	else
	{
		mActualAnimation = "";
	}
}

void AnimatorComponent::stopAnimation()
{
	mPlaying = false;
}

sf::Time AnimatorComponent::getElapsedTime() const
{
	return mTimeElapsed;
}

void AnimatorComponent::setElapsedTime(sf::Time elapsed)
{
	mTimeElapsed = elapsed;
	std::size_t size = getActualAnimation().getFrameCount();
	for (std::size_t i = 0; i < size; i++)
	{
		update(sf::Time::Zero);
	}
}

Animation& AnimatorComponent::getActualAnimation()
{
	return mAnimations[mActualAnimation];
}

Frame& AnimatorComponent::getActualFrame()
{
	return getActualAnimation().getFrame(mActualFrame);
}

void AnimatorComponent::update(sf::Time dt)
{
	if (mPlaying)
	{
		mTimeElapsed += dt;
		if (mTimeElapsed >= getActualFrame().duration)
		{
			mActualFrame = (mActualFrame + 1) % getActualAnimation().getFrameCount();
			const Frame& newFrame = getActualFrame();
			if (mActualTexture != newFrame.textureName)
			{
				mActualTexture = newFrame.textureName;
				mSprite.setTexture(getApplication().getResource<Texture>(mActualTexture));
			}
			mSprite.setTextureRect(newFrame.textureRect);
			mTimeElapsed = sf::Time::Zero;
		}
	}
}

sf::FloatRect AnimatorComponent::getLocalBounds()
{
	return getTransform().transformRect(mSprite.getLocalBounds());
}

sf::FloatRect AnimatorComponent::getGlobalBounds()
{
	return getWorldTransform().transformRect(mSprite.getLocalBounds());
}

void AnimatorComponent::serialize(Serializer& serializer)
{
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("pos", getPosition());
	serializer.save("rot", getRotation());
	serializer.save("sca", getScale());
	serializer.save("z", getZ());
	serializer.save("visible", isVisible());
	serializer.save("playing", isPlaying());
	serializer.save("elapsed", getElapsedTime());
	int i = 0;
	for (auto itr = mAnimations.begin(); itr != mAnimations.end(); itr++)
	{
		serializer.create("Animation");
		serializer.save("id", i);
		serializer.save("name", itr->first);
		Animation& a = itr->second;
		for (std::size_t j = 0; j < a.getFrameCount(); j++)
		{
			Frame& f = a.getFrame(j);
			serializer.create("Frame");
			serializer.save("id", j);
			serializer.save("texture", f.textureName);
			serializer.save("textureRect", f.textureRect);
			serializer.save("duration", f.duration);
			serializer.end();
		}
		serializer.end();
		i++;
	}
	serializer.end();
}

bool AnimatorComponent::deserialize(Serializer& serializer)
{
	return false;
}

void AnimatorComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mSprite, states);
}

} // namespace ke