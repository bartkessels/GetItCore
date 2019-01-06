#pragma once

#include <QList>
#include <QString>

#include "IHeader.h"

namespace GetItCore
{
    class IResponse
    {
    public:
        virtual ~IResponse(){}

        virtual QList<IHeader> getHeaders() = 0;
        virtual QString getBody() = 0;
    };
}
