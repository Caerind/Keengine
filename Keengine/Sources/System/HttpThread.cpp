#include "HttpThread.hpp"

HttpThread::HttpThread()
: mThread(std::bind(&HttpThread::run,this))
{
	mUrl = "";
    mRunning = true;
    mThread.launch();
}

HttpThread::HttpThread(std::string const& url)
: mThread(std::bind(&HttpThread::run,this))
{
	mUrl = url;
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
			sendHttpRequest(mUrl, mMessages.back());
			mMessages.pop_back();
        }

		sf::sleep(sf::microseconds(100));
    }
}

void HttpThread::setAddress(std::string const& url)
{
	mUrl = url;
}

void HttpThread::setMessage(std::string const& message)
{
    mMessages.push_back(message);
}

void HttpThread::splitUrl(std::string const& longurl, std::string& url, std::string& uri)
{
	std::string temp = longurl;
	if (longurl.find("http://") != std::string::npos)
	{
		temp = temp.substr(7);
		std::size_t found = temp.find_first_of("/");
		if (found != std::string::npos)
		{
			url = "http://" + temp.substr(0, found + 1);
			uri = temp.substr(found + 1);
		}
		else
		{
			url = longurl;
			uri = "";
		}
	}
	else
	{
		url = longurl;
		uri = "";
	}
}

bool HttpThread::sendHttpRequest(std::string const& url, std::string const& body, std::string* response)
{
	std::string tempUrl, tempUri;
	splitUrl(url, tempUrl, tempUri);
	sf::Http http(tempUrl);
	sf::Http::Request request(tempUri, sf::Http::Request::Post);
	request.setBody(body);
	sf::Http::Response rep = http.sendRequest(request);
	if (response != nullptr)
	{
		std::string tmp = rep.getBody();
		*response = tmp;
	}
	return rep.getStatus() == sf::Http::Response::Ok;
}
