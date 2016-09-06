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

AnimatorComponent::AnimatorComponent() 
	: mPlaying(false)
	, mSprite()
	, mAnimations()
	, mActualTexture()
	, mActualAnimation()
	, mActualFrame()
	, mTimeElapsed()
{
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

void AnimatorComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mSprite, states);
}

} // namespace ke