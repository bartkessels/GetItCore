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

    protected:
        std::string getBody();

    private:
        std::string body;
    };
}
