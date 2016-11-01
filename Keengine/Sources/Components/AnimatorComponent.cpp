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
	SceneComponent::serialize(serializer);

	serializer.save("current", mActualAnimation);
	serializer.save("playing", isPlaying());
	serializer.save("elapsed", getElapsedTime());

	for (auto itr = mAnimations.begin(); itr != mAnimations.end(); itr++)
	{
		serializer.create("Animation");
		serializer.save("name", itr->first);
		Animation& a = itr->second;
		serializer.save("size", a.getFrameCount());
		for (std::size_t j = 0; j < a.getFrameCount(); j++)
		{
			Frame& f = a.getFrame(j);
			serializer.create("Frame");
			serializer.save("id", j);
			serializer.save("texture", f.textureName);
			serializer.save("textureRect", f.textureRect);
			serializer.save("duration", f.duration);
			serializer.close();
		}
		serializer.close();
	}
}

bool AnimatorComponent::deserialize(Serializer& serializer)
{
	if (!SceneComponent::deserialize(serializer) 
		|| !serializer.load("current", mActualAnimation) 
		|| !serializer.load("playing", mPlaying) 
		|| !serializer.load("elapsed", mTimeElapsed))
	{
		return false;
	}

	while (serializer.read("Animation"))
	{
		std::string name;
		unsigned int size;
		if (serializer.load("name", name) && serializer.load("size", size))
		{
			Animation& anim = getAnimation(name);
			while (anim.getFrameCount() < size)
			{
				anim.addFrame();
			}
			while (serializer.read("Frame"))
			{
				unsigned int id;
				std::string texture;
				sf::IntRect textureRect;
				sf::Time duration;
				if (serializer.load("id", id)
					&& serializer.load("texture", texture)
					&& serializer.load("textureRect", textureRect)
					&& serializer.load("duration", duration))
				{
					Frame& f = anim.getFrame(id);
					f.textureName = texture;
					f.textureRect = textureRect;
					f.duration = duration;
				}
				serializer.end();
			}
		}
		serializer.end();
	}

	setElapsedTime(mTimeElapsed);

	return true;
}

void AnimatorComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mSprite, states);
}

} // namespace ke