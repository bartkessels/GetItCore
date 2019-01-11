#pragma once

#include <string>
#include <list>

#include "Header.hpp"

class ResponseListener
{
public:
    virtual ~ResponseListener();

    virtual void requestSent(std::list<GetItCore::Header*> headers, std::string body) = 0;
};
