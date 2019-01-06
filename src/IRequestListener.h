#pragma once

#include "IResponse.h"

namespace GetItCore
{
    class IRequestListener
    {
    public:
        virtual ~IRequestListener(){}

        virtual void requestSent(IResponse* response) = 0;
        virtual void requestTimedOut() = 0;
        virtual void requestError() = 0;
    };
}
