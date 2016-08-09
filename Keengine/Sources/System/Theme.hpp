#ifndef THEME_HPP
#define THEME_HPP

#include "../Application/ResourceManager.hpp"
#include "../ExtLibs/TGUI/Loading/Theme.hpp"

class Theme : public Resource
{
    public:
        Theme() {}

        bool loadFromFile(std::string const& filename)
        {
            mTheme = std::make_shared<tgui::Theme>(filename);
            mLoaded = (mTheme != nullptr);
            return mLoaded;
        }

        tgui::WidgetConverter create(std::string const& className)
        {
            return mTheme->load(className);
        }

    private:
        tgui::Theme::Ptr mTheme;
};

#endif // THEME_HPP
