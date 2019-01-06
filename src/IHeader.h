#pragma once

#include <QString>

namespace GetItCore
{
    class IHeader
    {
    public:
        virtual ~IHeader(){}

        virtual QString getName() = 0;
        virtual QString getValue() = 0;
    };
}
