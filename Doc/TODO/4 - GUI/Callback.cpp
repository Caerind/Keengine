#include "Callback.hpp"

namespace SGUI
{

////////////////////////////////////////////////////////////
Callback::Callback()
{
}

////////////////////////////////////////////////////////////
void Callback::setCallback(int type, Function f)
{
	mMap[type] = f;
}

////////////////////////////////////////////////////////////
void Callback::callback(int type)
{
	auto itr = mMap.find(type);
	if (itr != mMap.end())
	{
		if (itr->second)
		{
			itr->second();
		}
	}
}

} // namespace SGUI

