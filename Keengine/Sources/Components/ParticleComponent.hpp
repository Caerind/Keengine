#ifndef PARTICLECOMPONENT_HPP
#define PARTICLECOMPONENT_HPP

#include <array>
#include <functional>
#include <memory>

#include <SFML/Graphics/VertexArray.hpp>

#include "../Core/PrimitiveComponent.hpp"

// TODO : Make it work
class ParticleComponent : public PrimitiveComponent
{
    public:
		typedef std::array<sf::Vertex, 4> Quad;
		
		class Particle
		{
			public:
				Particle(sf::Time lifetime) : position(), velocity(), rotation(), rotationSpeed(), scale(1.f, 1.f), color(255, 255, 255), textureIndex(0), passedLifetime(sf::Time::Zero), totalLifetime(lifetime) {}

				sf::Vector2f position;
				sf::Vector2f velocity;
				float rotation;
				float rotationSpeed;
				sf::Vector2f scale;
				sf::Color color;
				std::size_t textureIndex;

				sf::Time passedLifetime;
				sf::Time totalLifetime;
		};

		typedef std::function<void(Particle&, sf::Time)> Affector;


	public:
		ParticleComponent();

		void setTexture(std::string const& id);
		void setTexture(sf::Texture& texture);
		std::size_t addTextureRect(sf::IntRect const& rect);

		void addAffector(Affector const& affector);
		void clearAffectors();

		virtual void update(sf::Time dt);
		virtual void render(sf::RenderTarget& target);

		std::size_t getParticleCount() const;
		void clearParticles();

		void enableEmission();
		void disableEmission();

		// TODO : Distribution
		void setEmissionRate(float particlesPerSecond);
		void setParticleLifetime(sf::Time lifetime);
		void setParticlePosition(sf::Vector2f position);
		void setParticleVelocity(sf::Vector2f velocity);
		void setParticleRotation(float rotation);
		void setParticleRotationSpeed(float rotationSpeed);
		void setParticleScale(sf::Vector2f scale);
		void setParticleColor(sf::Color color);
		void setParticleTextureIndex(std::size_t textureIndex);

		void emitParticle();
		void emitParticles(std::size_t particleAmount);

	private:
		std::size_t computeParticleCount(sf::Time dt);
		void updateParticle(Particle& particle, sf::Time dt);
		void computeVertices();
		void computeQuads();
		void computeQuad(Quad& quad, sf::IntRect const& rect);

	private:
		std::vector<Particle> mParticles;
		std::vector<Affector> mAffectors;

		sf::Texture* mTexture;
		std::vector<sf::IntRect> mTextureRects;

		sf::VertexArray mVertices;
		bool mNeedsVertexUpdate;
		std::vector<Quad> mQuads;
		bool mNeedsQuadUpdate;

		bool mEmitting;
		float mEmissionRate;
		float mEmissionDifference;

		sf::Time mParticleLifetime;
		sf::Vector2f mParticlePosition;
		sf::Vector2f mParticleVelocity;
		float mParticleRotation;
		float mParticleRotationSpeed;
		sf::Vector2f mParticleScale;
		sf::Color mParticleColor;
		std::size_t mParticleTextureIndex;
};

#endif // PARTICLECOMPONENT_HPP
