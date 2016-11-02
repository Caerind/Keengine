#include "Factories.hpp"

namespace ke
{

std::map<std::string, std::function<Actor::Ptr(Scene& scene)>> Factories::mActorFactory;
std::map<std::string, std::function<Component::Ptr(Actor& actor)>> Factories::mComponentFactory;
std::map<std::string, std::function<std::shared_ptr<ke::Effect>()>> Factories::mEffectFactory;
bool Factories::mRegistered = false;

void Factories::registerAll()
{
	if (!mRegistered)
	{
		// TODO : Check up to date
		registerComponent<AnimatorComponent>();
		registerComponent<AudioListenerComponent>();
		registerComponent<CameraComponent>();
		registerComponent<DirectionLightComponent>();
		registerComponent<InputComponent>();
		registerComponent<LayerComponent>();
		registerComponent<NodeComponent>();
		registerComponent<ParticleComponent>();
		registerComponent<PointLightComponent>();
		registerComponent<ShapeComponent>();
		registerComponent<SpriteComponent>();
		registerComponent<TextComponent>();
		
		registerEffect<Effect>();
		registerEffect<Blur>();
		registerEffect<Pixelate>();

		registerActor<Actor>();

		mRegistered = true;
	}
}

Actor::Ptr Factories::createActor(Scene& scene, const std::string& type)
{
	if (!mRegistered)
	{
		registerAll();
	}
	return mActorFactory[type](scene);
}

Component::Ptr Factories::createComponent(Actor& actor, const std::string& type)
{
	if (!mRegistered)
	{
		registerAll();
	}
	return mComponentFactory[type](actor);
}

std::shared_ptr<ke::Effect> Factories::createEffect(const std::string& type)
{
	if (!mRegistered)
	{
		registerAll();
	}
	return mEffectFactory[type]();
}

} // namespace ke