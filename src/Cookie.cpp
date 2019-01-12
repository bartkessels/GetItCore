#include "Cookie.hpp"

namespace GetItCore
{
    Cookie::Cookie(std::string name, std::string value):
        name(name),
        value(value)
    {
    }

    Cookie::~Cookie()
    {
    }

    std::string Cookie::getName()
    {
        return this->name;
    }

    std::string Cookie::getValue()
    {
        return this->value;
    }
}
