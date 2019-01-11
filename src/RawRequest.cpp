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

    size_t curlWriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
    {
        size_t newSize = size * nmemb;

        static_cast<std::string*>(userp)->append(static_cast<char*>(contents), newSize);
        return newSize;
    }

    void RawRequest::send(std::string method, std::string uri)
    {
        CURL *curl;
        CURLcode res;
        std::string buffer;

        curl = curl_easy_init();

        if (curl) {
            std::cout << "curl" << std::endl;

            curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            std::cout << buffer << std::endl;
        } else {
            std::cout << "!curl..." << std::endl;
        }

        curl_global_cleanup();
    }

    CURL *RawRequest::buildCURLRequest(std::string method, std::string uri)
    {
        CURL *curl = curl_easy_init();

        if (!curl) {
            // Throw exception
        }

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);

        return curl;
    }

    void RawRequest::addHeadersToCURL(CURL *curl)
    {
        for (Header *header : this->headers)
        {
            std::string encodedName     = curl_easy_escape(curl, header->getName().c_str(), header->getName().length());
            std::string encodedValue    = curl_easy_escape(curl, header->getValue().c_str(), header->getValue().length());

            std::string completeHeader  = encodedName + "=" + encodedValue;
        }
    }

    void addCookiesToCURL(CURL *curl)
    {

    }

    void addFormdataToCURL(CURL *curl)
    {

    }
}
