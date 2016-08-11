#include "LangManager.hpp"

namespace ah
{

LangManager::LangManager()
{
}

bool LangManager::load(std::string const& path)
{
    DIR* dir = nullptr;
    struct dirent* file = nullptr;
    dir = opendir(path.c_str());
    if (dir == nullptr)
    {
        return false;
    }

    while ((file = readdir(dir)) != nullptr)
    {
        std::string n = file->d_name;
        std::size_t found = n.find(".lang");
        if (found != std::string::npos)
        {
            std::ifstream file(path + n);
            if (file)
            {
                std::string langName = n.substr(0,found);
                std::string line;
                while (std::getline(file,line))
                {
                    auto f = line.find("=");
                    std::string id = line.substr(0,f);
                    std::string str = line.substr(f+1);
                    mLangs[langName][id] = str;
                }
            }
            file.close();
        }
    }

    return true;
}

std::vector<std::string> LangManager::getLoadedLangs()
{
    std::vector<std::string> langs;
    for (auto itr = mLangs.begin(); itr != mLangs.end(); itr++)
    {
        langs.push_back(itr->first);
    }
    return langs;
}

bool LangManager::isLangLoaded(std::string const& lang)
{
    return (mLangs.find(lang) != mLangs.end());
}

bool LangManager::setActualLang(std::string const& lang)
{
    if (mLangs.find(lang) != mLangs.end())
    {
        mActualLang = lang;
        return true;
    }
    else
    {
        mActualLang = "";
        return false;
    }
}

std::string LangManager::getActualLang() const
{
    return mActualLang;
}

void LangManager::set(std::string const& id, std::string const& str)
{
    if (mActualLang != "")
    {
        if (mLangs.at(mActualLang).find(id) != mLangs.at(mActualLang).end())
        {
            mLangs.at(mActualLang)[id] = str;
        }
    }
}

std::string LangManager::get(std::string const& id) const
{
    if (mActualLang != "")
    {
        if (mLangs.at(mActualLang).find(id) != mLangs.at(mActualLang).end())
        {
            return mLangs.at(mActualLang).at(id);
        }
    }
    return id;
}

} // namespace ah
