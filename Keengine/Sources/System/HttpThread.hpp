#ifndef HTTPTHREAD_HPP
#define HTTPTHREAD_HPP

#include <functional>
#include <vector>

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Http.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Sleep.hpp>

// Improvements :
// - Thread-safe
class HttpThread
{
    public:
        HttpThread();
        HttpThread(std::string const& url);
        ~HttpThread();

        void run();

        void setAddress(std::string const& url);
        void setMessage(std::string const& message);

		static void splitUrl(std::string const& longurl, std::string& url, std::string& uri);

		static bool sendHttpRequest(std::string const& url, std::string const& request, std::string* response = nullptr);

    private:
        sf::Thread mThread;

        bool mRunning;

        std::vector<std::string> mMessages;

        std::string mUrl;
};

#endif // HTTPTHREAD_HPP
