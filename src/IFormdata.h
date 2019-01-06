#pragma once

#include <QString>

namespace GetItCore
{
    class IFormdata
    {
    public:
        virtual ~IFormdata(){}

        virtual QString getName() = 0;
        virtual QString getValue() = 0;
    };
}
