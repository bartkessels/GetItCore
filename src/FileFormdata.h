#pragma once

#include <QFile>
#include <QString>

#include "IFormdata.h"

namespace GetItCore
{
    class FileFormdata: public IFormdata
    {
    public:
        FileFormdata(QString name, QFile* file);
        ~FileFormdata();

        QString getName();
        QString getValue();

    private:
        QString name;
        QFile* file;
    };
}
