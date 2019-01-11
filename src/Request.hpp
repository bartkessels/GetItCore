#pragma once

#include <string>
#include <list>
#include <curl/curl.h>

#include "Cookie.hpp"
#include "Header.hpp"
#include "ResponseListener.hpp"

namespace GetItCore
{
    class Request
    {
    public:
        virtual ~Request() {}

        void addCookie(Cookie* cookie);
        void addHeader(Header* header);

        void removeCookie(Cookie* cookie);
        void removeHeader(Header* header);

        void registerListener(ResponseListener* listener);
        void deregisterListener(ResponseListener* listener);

        virtual void send(std::string method, std::string uri) = 0;

    protected:
        void notifyListenersRequestSent(std::list<Header*> headers, std::string body);
        void setCURLHeader(CURL *curl, Header* header);
        void setCURLCookie(CURL *curl, Cookie* cookie);

        std::list<Cookie*> cookies;
        std::list<Header*> headers;
        std::list<ResponseListener*> listeners;
    };
}
