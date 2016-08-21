#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "../Core/PrimitiveComponent.hpp"

struct Frame
{
	std::string textureName;
	sf::IntRect textureRect;
	sf::Time duration;
};

class Animation
{
public:
	Animation();

	void addFrame(Frame const& frame);
	void addFrame(std::string const& textureName, sf::IntRect const& textureRect, sf::Time duration);

	std::size_t getFrameCount() const;

	Frame& getFrame(std::size_t index);

	void removeFrame(std::size_t index);

	void removeAllFrames();

	sf::Time getDuration() const;

private:
	std::vector<Frame> mFrames;
};

class AnimatorComponent : public PrimitiveComponent
{
	public:
		AnimatorComponent();

		std::size_t getAnimationCount() const;

		Animation& getAnimation(std::string const& name);

		void removeAnimation(std::string const& name);

		void removeAllAnimations();

		void playAnimation(std::string const& name);
		void stopAnimation();

		Animation& getActualAnimation();
		Frame& getActualFrame();

		void update(sf::Time dt);
		void render(sf::RenderTarget& target);
		
		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

	private:
		bool mPlaying;
		sf::Sprite mSprite;
		std::unordered_map<std::string, Animation> mAnimations;
		std::string mActualTexture;
		std::string mActualAnimation;
		std::size_t mActualFrame;
		sf::Time mTimeElapsed;
};

#endif // ANIMATIORCOMPONENT_HPP
