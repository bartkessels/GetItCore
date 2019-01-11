#pragma once

#include <string>

namespace GetItCore
{
    class Cookie
    {
    public:
        Cookie(std::string name, std::string value);
        ~Cookie();

        std::string getName();
        std::string getValue();

    private:
        std::string name;
        std::string value;
    };
}
