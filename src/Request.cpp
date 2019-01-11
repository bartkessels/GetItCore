#include "Request.hpp"

namespace GetItCore
{
    void Request::addCookie(Cookie* cookie)
    {
        this->cookies.push_back(cookie);
    }

    void Request::addHeader(Header* header)
    {
        this->headers.push_back(header);
    }

    void Request::removeCookie(Cookie* cookie)
    {
        this->cookies.remove(cookie);
    }

    void Request::removeHeader(Header* header)
    {
        this->headers.remove(header);
    }

    void Request::registerListener(ResponseListener* listener)
    {
        this->listeners.push_back(listener);
    }

    void Request::deregisterListener(ResponseListener* listener)
    {
        this->listeners.remove(listener);
    }

    void Request::notifyListenersRequestSent(std::list<Header*> headers, std::string body)
    {
        for (ResponseListener* listener : this->listeners) {
            listener->requestSent(headers, body);
        }
    }
}
