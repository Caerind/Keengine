#include "SceneRoot.hpp"
#include "Scene.hpp"

namespace ke
{

SceneRoot::SceneRoot(Scene& scene) : Actor(scene)
{
}

void SceneRoot::removeComponent(std::shared_ptr<SceneComponent> component)
{
	std::size_t size = mComponentsPtr.size();
	for (std::size_t i = 0; i < size; i++)
	{
		bool erase = false;
		if (mComponentsPtr[i] == nullptr)
		{
			erase = true;
		}
		else if (mComponentsPtr[i] == component)
		{
			erase = true;
			detachComponent(mComponentsPtr[i].get());
			unregisterComponent(mComponentsPtr[i].get());
		}
		if (erase)
		{
			mComponentsPtr.erase(mComponentsPtr.begin() + i);
			i--;
			size--;
		}
	}
}

} // namespace ke