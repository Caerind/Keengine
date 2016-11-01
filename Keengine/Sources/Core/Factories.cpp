#include "Factories.hpp"

namespace ke
{

std::map<std::string, std::function<Actor::Ptr(Scene& scene)>> Factories::mActorFactory;
std::map<std::string, std::function<Component::Ptr(Actor& actor)>> Factories::mComponentFactory;
bool Factories::mRegistered = false;

void Factories::registerAll()
{
	if (!mRegistered)
	{
		// TODO : Check up to date
		registerComponent<AnimatorComponent>();
		registerComponent<CameraComponent>();
		registerComponent<DirectionLightComponent>();
		registerComponent<InputComponent>();
		registerComponent<LayerComponent>();
		registerComponent<ParticleComponent>();
		registerComponent<PointComponent>();
		registerComponent<PointLightComponent>();
		registerComponent<ShapeComponent>();
		registerComponent<SpriteComponent>();
		registerComponent<TextComponent>();

		registerActor<Actor>();
		mRegistered = true;
	}
}

Actor::Ptr ke::Factories::createActor(Scene& scene, const std::string& type)
{
	return mActorFactory[type](scene);
}

Component::Ptr ke::Factories::createComponent(Actor& actor, const std::string& type)
{
	return mComponentFactory[type](actor);
}

} // namespace ke