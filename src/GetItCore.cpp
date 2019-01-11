#include "GetItCore.hpp"

namespace GetItCore
{

    GetItCore::GetItCore()
    {
    }

    GetItCore::~GetItCore()
    {

    }

    void GetItCore::sendRequest(Request* request)
    {

    }

    void GetItCore::registerListener(ResponseListener* listener)
    {
        this->listeners.push_back(listener);
    }

    void GetItCore::deregisterListener(ResponseListener* listener)
    {
        this->listeners.remove(listener);
    }
}
