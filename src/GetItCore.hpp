#pragma once

#include <list>

#include "Request.hpp"
#include "ResponseListener.hpp"

namespace GetItCore _GLIBCXX_VISIBILITY(default)
{
    class GetItCore
    {
    public:
        GetItCore();
        ~GetItCore();

        void sendRequest(Request* request);

        void registerListener(ResponseListener* listener);
        void deregisterListener(ResponseListener* listener);

    private:
        std::list<ResponseListener*> listeners;
    };
}
