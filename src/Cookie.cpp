#include "Cookie.h"

namespace GetItCore
{
    Cookie::Cookie(QString name, QString value):
        name(name),
        value(value)
    {
    }

    Cookie::~Cookie()
    {
    }

    QString Cookie::getName()
    {
        return this->name;
    }

    QString Cookie::getValue()
    {
        return this->value;
    }
}
