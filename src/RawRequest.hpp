#pragma once

#include <string>
#include <curl/curl.h>

#include "Request.hpp"

namespace GetItCore
{
    class RawRequest: public Request
    {
    public:
        RawRequest();
        ~RawRequest();

        void setBody(std::string body);
        void send(std::string method, std::string uri);

    private:
        CURL *buildCURLRequest(std::string method, std::string uri);
        void addHeadersToCURL(CURL *curl);
        void addCookiesToCURL(CURL *curl);
        void addFormdataToCURL(CURL *curl);

        std::string body;
    };
}
