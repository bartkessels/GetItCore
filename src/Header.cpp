#include "Header.hpp"

namespace GetItCore
{
    Header::Header(std::string name, std::string value):
        name(name),
        value(value)
    {
    }

    Header::~Header()
    {
    }

    std::string Header::getName()
    {
        return this->name;
    }

    std::string Header::getValue()
    {
        return this->value;
    }
}
