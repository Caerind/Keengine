#include "HttpThread.hpp"

HttpThread::HttpThread()
: mThread(std::bind(&HttpThread::run,this))
{
    mRunning = true;
    mThread.launch();
}

HttpThread::HttpThread(std::string const& url, std::string const& uri)
: mThread(std::bind(&HttpThread::run,this))
, mUrl(url)
, mUri(uri)
{
    mRunning = true;
    mThread.launch();
}

HttpThread::~HttpThread()
{
    mRunning = false;
    mThread.wait();
}

void HttpThread::run()
{
    while (mRunning)
    {
        while (!mMessages.empty())
        {
            sf::Http http(mUrl);
            sf::Http::Request request(mUri, sf::Http::Request::Post);
            request.setBody(mMessages.back());

            mMessages.pop_back();

            http.sendRequest(request);
        }
    }
}

void HttpThread::setAddress(std::string const& url, std::string const& uri)
{
    mUrl = url;
    mUri = uri;
}

void HttpThread::setMessage(std::string const& message)
{
    mMessages.push_back(message);
}
