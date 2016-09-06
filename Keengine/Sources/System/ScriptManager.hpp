#ifndef KE_SCRIPTMANAGER_HPP
#define KE_SCRIPTMANAGER_HPP

#include "../Config.hpp"

#ifndef KEENGINE_ANDROID

#include <functional>
#include <unordered_map>
#include <vector>

#include "../ExtLibs/Selene/selene.h"

namespace ke
{

class ScriptManager
{
    public:
        ScriptManager() : mScripts(), mPath(""), mLibraries() {}

        sel::State& operator[](std::string const& script)
        {
            if (mScripts.find(script) == mScripts.end())
            {
                mScripts.emplace(script, true);
                mScripts[script].Load(mPath + script);
                for (auto& lib : mLibraries)
                {
                    if (lib)
                    {
                        lib(mScripts[script]);
                    }
                }
            }
            return mScripts.at(script);
        }

        bool isLoaded(std::string const& script) const
        {
            return (mScripts.find(script) == mScripts.end());
        }

        void release(std::string const& script)
        {
            auto itr = mScripts.find(script);
            if (itr != mScripts.end())
            {
                mScripts.erase(itr);
            }
        }

        void reload(std::string const& script)
        {
            auto itr = mScripts.find(script);
            if (itr != mScripts.end())
            {
                mScripts.erase(itr);
                mScripts.emplace(script, true);
                mScripts[script].Load(script);
                for (auto& lib : mLibraries)
                {
                    if (lib)
                    {
                        lib(mScripts[script]);
                    }
                }
            }
        }

        void setPath(std::string const& path)
        {
            mPath = path;
        }

        void addLibrary(std::function<void(sel::State& state)> library = [](sel::State& state){})
        {
            if (library)
            {
                mLibraries.push_back(library);
                for (auto itr = mScripts.begin(); itr != mScripts.end(); itr++)
                {
                    library(itr->second);
                }
            }
        }

    private:
        std::unordered_map<std::string,sel::State> mScripts;
        std::string mPath;
        std::vector<std::function<void(sel::State& state)>> mLibraries;
};

} // namespace ke

#endif // KEENGINE_ANDROID

#endif // KE_SCRIPTMANAGER_HPP
