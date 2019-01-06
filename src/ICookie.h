#pragma once

#include <QString>

namespace GetItCore
{
    class ICookie
    {
    public:
        virtual ~ICookie(){}

        virtual QString getName() = 0;
        virtual QString getValue() = 0;
    };
}
