#ifndef INIPARSER_HPP
#define INIPARSER_HPP

#include <fstream>
#include <sstream>
#include <map>

#include "../Application/ResourceManager.hpp"
#include "Variant.hpp"

class IniParser : public std::map<std::string,Variant>, public Resource
{
    public:
        IniParser() {}

        Variant& operator[](std::string const& id)
        {
            for (std::size_t i = 0; i < mPairs.size(); i++)
            {
                if (mPairs[i].first == id)
                {
                    return mPairs[i].second;
                }
            }
            mPairs.push_back(std::pair<std::string, Variant>(id, std::string()));
            return mPairs.back().second;
        }

        bool loadFromFile(std::string const& filename)
        {
            std::ifstream file(filename);
            if (!file)
            {
                return false;
            }
            auto trim = [](std::string line)
            {
                while (line.size() && (line.back()=='\t' || line.back()== ' ')) line.pop_back();
                while (line.size() && (line.front()=='\t' || line.front()== ' ')) line = line.substr(1);
                return line;
            };
            std::string line;
            while (std::getline(file, line))
            {
                line = trim(line);
                if (line.size() >= 1 && line.front() != ';')
                {
                    std::size_t found = line.find_first_of('=');
                    std::string key = trim(line.substr(0, found));
                    std::string value = (found == std::string::npos) ? std::string() : trim(line.substr(found + 1));
                    mPairs.push_back(std::pair<std::string, Variant>(key, value));
                }
            }
            mLoaded = true;
            return true;
        }

        bool saveToFile(std::string const& filename) const
        {
            std::ofstream file(filename);
            if (!file)
            {
                return false;
            }
            for (std::size_t i = 0; i < mPairs.size(); i++)
            {
                file << mPairs[i].first << "=" << mPairs[i].second << std::endl;
            }
            file.close();
            return true;
        }

    private:
        std::vector<std::pair<std::string, Variant>> mPairs;
};

#endif // INIPARSER_HPP
