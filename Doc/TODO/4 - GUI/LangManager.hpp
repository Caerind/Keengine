#ifndef AH_LANGMANAGER_HPP
#define AH_LANGMANAGER_HPP

#include <string>
#include <map>
#include <vector>
#include <fstream>

#include <dirent.h>
#ifndef WIN32
    #include <sys/types.h>
#endif

namespace ah
{

class LangManager
{
    public:
        LangManager();

        bool load(std::string const& path);

        std::vector<std::string> getLoadedLangs();
        bool isLangLoaded(std::string const& lang);

        bool setActualLang(std::string const& lang);
        std::string getActualLang() const;

        void set(std::string const& id, std::string const& str);
        std::string get(std::string const& id) const;

    protected:
        std::string mActualLang;
        std::map<std::string,std::map<std::string,std::string>> mLangs;
};

} // namespace ah

#endif // AH_LANGMANAGER_HPP
