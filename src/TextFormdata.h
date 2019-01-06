#pragma once

#include <QString>

#include "IFormdata.h"

namespace GetItCore
{
    class TextFormdata: public IFormdata
    {
    public:
        TextFormdata(QString name, QString value);
        ~TextFormdata();

        QString getName();
        QString getValue();

    private:
        QString name;
        QString value;
    };
}
