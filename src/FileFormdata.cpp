#include "FileFormdata.h"

namespace GetItCore
{
    FileFormdata::FileFormdata(QString name, QFile* file):
        name(name),
        file(file)
    {
    }

    FileFormdata::~FileFormdata()
    {
    }

    QString FileFormdata::getName()
    {
        return this->name;
    }

    QString FileFormdata::getValue()
    {
        // TODO: Read the file and return it's contents
        return "";
    }
}
