#pragma once

#include <QString>

#include "IHeader.h"

namespace GetItCore
{
    class Header: public IHeader
    {
    public:
        Header(QString name, QString value);
        ~Header();

        QString getName();
        QString getValue();

    private:
        QString name;
        QString value;
    };
}
