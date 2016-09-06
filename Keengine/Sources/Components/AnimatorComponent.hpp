#ifndef KE_ANIMATIONCOMPONENT_HPP
#define KE_ANIMATIONCOMPONENT_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "../Core/SceneComponent.hpp"

namespace ke
{

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

class AnimatorComponent : public SceneComponent
{
	public:
		AnimatorComponent();

		std::size_t getAnimationCount() const;

		Animation& getAnimation(std::string const& name);

		void removeAnimation(std::string const& name);

		void removeAllAnimations();

		void playAnimation(std::string const& name);
		void stopAnimation();

		void setElapsedTime(sf::Time elapsed);

		Animation& getActualAnimation();
		Frame& getActualFrame();

		void update(sf::Time dt);
		
		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

	private:
		virtual void renderCurrent(sf::RenderTarget& target, sf::RenderStates states);

	private:
		bool mPlaying;
		sf::Sprite mSprite;
		std::unordered_map<std::string, Animation> mAnimations;
		std::string mActualTexture;
		std::string mActualAnimation;
		std::size_t mActualFrame;
		sf::Time mTimeElapsed;
};

} // namespace ke

#endif // KE_ANIMATIORCOMPONENT_HPP
