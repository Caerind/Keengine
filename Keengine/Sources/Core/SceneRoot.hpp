#ifndef KE_SCENEROOT_HPP
#define KE_SCENEROOT_HPP

#include "Actor.hpp"

namespace ke
{

class SceneRoot : public Actor
{
	public:
		typedef std::shared_ptr<SceneRoot> Ptr;

		SceneRoot(Scene& scene);

		template <typename T, typename ... Args>
		std::shared_ptr<T> createComponent(Args&& ... args)
		{
			std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
			mComponentsPtr.push_back(component);
			registerComponent(component.get());
			attachComponent(component.get());
			return component;
		}

		void removeComponent(std::shared_ptr<SceneComponent> component);

	protected:
		std::vector<std::shared_ptr<SceneComponent>> mComponentsPtr;
};

} // namespace ke

#endif // KE_SCENEROOT_HPP