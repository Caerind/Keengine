#ifndef KE_LOG_HPP
#define KE_LOG_HPP

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <SFML/Network/Http.hpp>
#include <SFML/Network/IpAddress.hpp>

#include "HttpThread.hpp"
#include "Time.hpp"

namespace ke
{

class Log
{
    public:
        enum LogType
        {
            Error,
            Warning,
            Info,
        };

		static Log& instance()
        {
            static Log* instance = new Log();
            return *instance;
        }

        static void log(std::string const& message)
        {
            std::stringstream ss;
            ss << getTime("[%x][%X]");
            switch (instance().mType)
            {
                case LogType::Error:
                    ss << "[ERROR] : ";
                    break;

                case LogType::Warning:
                    ss << "[WARNING] : ";
                    break;

                default:
                    ss << "[INFO] : ";
            }
            ss << message;

            if (instance().mConsole)
            {
                std::cout << ss.str() << std::endl;
            }
            if (instance().mFile.is_open())
            {
                instance().mFile << ss.str() << std::endl;
            }
            if (instance().mOnline)
            {
                Log::onlineLog(message);
            }

            instance().mType = Log::LogType::Info;
        }

		static void onlineLog(std::string const& message)
        {
            std::stringstream stream;
            stream << "action=insert";
            if (instance().mType == LogType::Warning)
                stream << "&type=warning";
            else if (instance().mType == LogType::Error)
                stream << "&type=error";
            else
                stream << "&type=info";
            stream << "&address=" << sf::IpAddress::getPublicAddress().toString();
            stream << "&content=" << message;
            instance().mThread.setMessage(stream.str());
        }

        friend Log& operator<<(Log& log, std::string const& message)
        {
            Log::log(message);
            return log;
        }

        friend Log& operator<<(Log& log, LogType type)
        {
			Log::setLogType(type);
            return log;
        }

        static void info(std::string const& message)
        {
            instance().mType = LogType::Info;
            log(message);
        }

        static void warning(std::string const& message)
        {
            instance().mType = LogType::Warning;
            log(message);
        }

        static void error(std::string const& message)
        {
            instance().mType = LogType::Error;
            log(message);
        }

        static void setLogType(LogType type)
        {
            instance().mType = type;
        }

		static LogType getLogType()
		{
		    return instance().mType;
		}

        static bool openLog(std::string const& filename)
        {
            instance().mFilename = filename;
            instance().mFile.close();
            if (filename != "")
            {
                instance().mFile.open(filename,std::ios::app);
            }
            return instance().mFile.is_open();
        }

        static std::string getFilename()
        {
            return instance().mFilename;
        }

        static bool isLogOpen()
        {
            return instance().mFile.is_open();
        }

        static void useConsole(bool use)
        {
            instance().mConsole = use;
        }

		static bool usingConsole()
        {
            return instance().mConsole;
        }

		static void setOnline(std::string const& url)
		{
		    instance().mUrl = url;
            if (url != "")
            {
                instance().mThread.setAddress(url);
                instance().mOnline = true;
            }
            else
            {
                instance().mOnline = false;
            }
        }

        static std::string getUrl()
        {
            return instance().mUrl;
        }

		static bool isOnline()
        {
            return instance().mOnline;
        }

	private:
        Log() : mType(Log::LogType::Info), mFile(), mConsole(true), mOnline(false)
        {
        }

		~Log()
		{
		}

    private:
        LogType mType;
        std::string mFilename;
        std::ofstream mFile;
        bool mConsole;
		bool mOnline;
		HttpThread mThread;
		std::string mUrl;
};

} // namespace ke

#endif // KE_LOG_HPP
