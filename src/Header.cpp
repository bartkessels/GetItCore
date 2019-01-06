#include "Header.h"

namespace GetItCore
{
    Header::Header(QString name, QString value):
        name(name),
        value(value)
    {
    }

    Header::~Header()
    {
    }

    QString Header::getName()
    {
        return this->name;
    }

    QString Header::getValue()
    {
        return this->value;
    }
}
