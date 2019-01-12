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
        Request();
        virtual ~Request() {}

        void addCookie(Cookie* cookie);
        void addHeader(Header* header);

        void registerListener(ResponseListener* listener);
        void deregisterListener(ResponseListener* listener);

        void send(std::string method, std::string uri);

    protected:
        void notifyListenersRequestSent(std::list<Header*> headers, std::string body);

        virtual std::string getBody() = 0;

        void addHeadersToCURL();
        void addCookiesToCURL();

        void setUpCURL(std::string method, std::string uri);
        std::list<Header*> readHeadersFromCURL();
        std::list<Cookie*> readCookiesFromCURL();


        FILE *responseHeaders, *responseBody;
        std::string cookies;
        CURL *curl;
        struct curl_slist *headers;

        std::list<ResponseListener*> listeners;
    };
}
