#pragma once

#include <string>

namespace GetItCore
{
    class Header
    {
    public:
        Header(std::string name, std::string value);
        ~Header();

        std::string getName();
        std::string getValue();

    private:
        std::string name;
        std::string value;
    };
}
