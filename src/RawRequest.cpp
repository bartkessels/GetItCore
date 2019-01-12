#include "RawRequest.hpp"

#include <curl/curl.h>

#include <iostream>

namespace GetItCore
{
    RawRequest::RawRequest()
    {
    }

    RawRequest::~RawRequest()
    {

    }

    void RawRequest::setBody(std::string body)
    {
        this->body = body;
    }

    std::string RawRequest::getBody()
    {
        return this->body;
    }
}
