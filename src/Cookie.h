#pragma once

#include <QString>

#include "ICookie.h"

namespace GetItCore
{
    class Cookie: public ICookie
    {
    public:
        Cookie(QString name, QString value);
        ~Cookie();

        QString getName();
        QString getValue();

    private:
        QString name;
        QString value;
    };
}
