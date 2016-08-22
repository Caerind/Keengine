#include "MyMap.hpp"
#include "../Sources/Core/World.hpp"
#include "MyObject.hpp"

MyMap::MyMap()
{
	registerComponent(&mSun);
	attachComponent(&mSun);
	mSun.setIntensity(6.f);
	mSun.setDirection({ -0.1f, 0.6f });
}