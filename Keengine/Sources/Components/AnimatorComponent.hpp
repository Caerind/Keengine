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
		typedef std::shared_ptr<AnimatorComponent> Ptr;

		TYPE(AnimatorComponent)

		AnimatorComponent(Actor& actor);

		std::size_t getAnimationCount() const;

		Animation& getAnimation(std::string const& name);

		void removeAnimation(std::string const& name);

		void removeAllAnimations();

		bool isPlaying() const;
		void playAnimation(std::string const& name);
		void stopAnimation();

		sf::Time getElapsedTime() const;
		void setElapsedTime(sf::Time elapsed);

		Animation& getActualAnimation();
		Frame& getActualFrame();

		void update(sf::Time dt);
		
		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

		virtual void serialize(Serializer& serializer);
		virtual bool deserialize(Serializer& serializer, const std::string& identifier);

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
