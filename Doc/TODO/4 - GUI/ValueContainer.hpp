#ifndef AH_VALUECONTAINER_HPP
#define AH_VALUECONTAINER_HPP

#include <map>
#include <string>
#include "../Utils/Pugixml.hpp"

namespace ah
{

class ValueContainer
{
    public:
        ValueContainer();

        bool exist(std::string const& id) const;

        void set(std::string const& id, std::string const& value);
        void set(std::string const& id, std::string const& value, bool save);
        std::string get(std::string const& id) const;

        void setInt(std::string const& id, int value);
        void setInt(std::string const& id, int value, bool save);
        int getInt(std::string const& id) const;

        void setFloat(std::string const& id, float value);
        void setFloat(std::string const& id, float value, bool save);
        float getFloat(std::string const& id) const;

        void setSaved(std::string const& id, bool save);
        bool isSaved(std::string const& id) const;

        bool load(std::string const& filename);
        void save(std::string const& filename);

    protected:
        std::map<std::string,std::pair<std::string,bool>> mValues;
};

} // namespace ah

#endif // AH_VALUECONTAINER_HPP
