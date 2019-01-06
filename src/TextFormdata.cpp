#include "TextFormdata.h"

namespace GetItCore
{
    TextFormdata::TextFormdata(QString name, QString value):
        name(name),
        value(value)
    {
    }

    TextFormdata::~TextFormdata()
    {
    }

    QString TextFormdata::getName()
    {
        return this->name;
    }

    QString TextFormdata::getValue()
    {
        return this->value;
    }
}
