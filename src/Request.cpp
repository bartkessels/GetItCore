#include "Request.hpp"

namespace GetItCore
{
    Request::Request()
    {
        this->headers       = nullptr;
        this->curl          = nullptr;
    }

    size_t curlWriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
    {
        size_t newSize = size * nmemb;

        static_cast<std::string*>(userp)->append(static_cast<char*>(contents), newSize);
        return newSize;
    }

    void Request::addCookie(Cookie* cookie)
    {
        const char *name            = cookie->getName().c_str();
        const char *value           = cookie->getValue().c_str();
        int nameSize                = static_cast<int>(cookie->getName().size());
        int valueSize               = static_cast<int>(cookie->getValue().size());

        std::string encodedName     = curl_easy_escape(curl, name, nameSize);
        std::string encodedValue    = curl_easy_escape(curl, value, valueSize);
        std::string cookieString    = encodedName + "=" + encodedValue + ";";

        this->cookies.append(cookieString);
    }

    void Request::addHeader(Header* header)
    {
        const char *name            = header->getName().c_str();
        const char *value           = header->getValue().c_str();
        int nameSize                = static_cast<int>(header->getName().size());
        int valueSize               = static_cast<int>(header->getValue().size());

        std::string encodedName     = curl_easy_escape(curl, name, nameSize);
        std::string encodedValue    = curl_easy_escape(curl, value, valueSize);
        std::string headerString    = encodedName + ": " + encodedValue;

        this->headers = curl_slist_append(this->headers, headerString.c_str());
    }

    void Request::registerListener(ResponseListener* listener)
    {
        this->listeners.push_back(listener);
    }

    void Request::deregisterListener(ResponseListener* listener)
    {
        this->listeners.remove(listener);
    }

    void Request::notifyListenersRequestSent()
    {
        std::string body;
        std::list<Header*> headers;
        for (ResponseListener* listener : this->listeners) {
            listener->requestSent(headers, body);
        }
    }

    void Request::send(std::string method, std::string uri)
    {
        this->setUpCURL(method, uri);
        this->sendCURL();
        this->cleanupCURL();
        this->notifyListenersRequestSent();
    }

    void Request::setUpCURL(std::string method, std::string uri)
    {
        this->curl = curl_easy_init();

        if (!this->curl) {
            throw "Unable to setup cURL";
        }

        curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST  , method.c_str());
        curl_easy_setopt(this->curl, CURLOPT_URL            , uri.c_str());
        curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION  , curlWriteCallback);
        curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER     , this->headers);
        curl_easy_setopt(this->curl, CURLOPT_HEADERDATA     , &this->responseHeaders);
        curl_easy_setopt(this->curl, CURLOPT_WRITEDATA      , &this->responseBody);
    }

    void Request::sendCURL()
    {
        std::string body    = this->getBody();
        int bodySize        = static_cast<int>(body.size());

        curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS     , body.c_str());
        curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE  , bodySize);

        curl_easy_perform(curl);
    }

    void Request::cleanupCURL()
    {
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        this->curl = nullptr;
    }
}
