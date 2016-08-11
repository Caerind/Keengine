#ifndef SGUI_CALLBACK_HPP
#define SGUI_CALLBACK_HPP

#include <functional>
#include <map>

namespace SGUI
{

class Callback
{
    public:
        typedef std::function<void()> Function;

    public:
        Callback();

        void setCallback(int type, Function f);
		void callback(int type);

    protected:
		std::map<int,Function> mMap;

};

} // namespace SGUI

#endif // SGUI_CALLBACK_HPP
