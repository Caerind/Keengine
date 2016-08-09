#ifndef INIPARSER_HPP
#define INIPARSER_HPP

#include <fstream>
#include <sstream>
#include <map>

#include "../Application/ResourceManager.hpp"

namespace ini
{

class Variant : public std::string
{
    public:
        template <typename T>
        Variant(const T &t) : std::string(std::to_string(t))
        {}

        Variant(bool boolean) : std::string((boolean) ? "true" : "false")
        {}

        template <size_t N>
        Variant(const char (&s)[N]) : std::string(s, N)
        {}

        Variant(const char *cstr) : std::string(cstr)
        {}

        Variant(const std::string &other = std::string()) : std::string(other)
        {}

        template <typename T>
        operator T() const
        {
            T t;
            std::stringstream ss;
            return ss << *this && ss >> t ? t : T();
        }

        template <typename T> bool operator==(const T &t) const
        {
            return 0 == this->compare(Variant(t));
        }

        bool operator==(const char *t) const
        {
            return this->compare(t) == 0;
        }

        inline bool asBool()
        {
            return (*this == "true");
        }

        inline int asInt()
        {
			std::stringstream iss(*this);
			int value;
			iss >> value;
			return value;
        }

        inline unsigned int asUint()
        {
			std::stringstream iss(*this);
			unsigned int value;
			iss >> value;
			return value;
        }

        inline float asFloat()
        {
			std::stringstream iss(*this);
			float value;
			iss >> value;
			return value;
        }
};

}

class IniParser : public std::map<std::string,ini::Variant>, public Resource
{
    public:
        IniParser() {}

        ini::Variant& operator[](std::string const& id)
        {
            for (std::size_t i = 0; i < mPairs.size(); i++)
            {
                if (mPairs[i].first == id)
                {
                    return mPairs[i].second;
                }
            }
            mPairs.push_back(std::pair<std::string,ini::Variant>(id,std::string()));
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
                    mPairs.push_back(std::pair<std::string,ini::Variant>(key,value));
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
        std::vector<std::pair<std::string,ini::Variant>> mPairs;
};

#endif // INIPARSER_HPP
