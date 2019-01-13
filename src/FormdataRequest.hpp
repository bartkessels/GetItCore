#pragma once

#include <string>
#include <list>

#include "Formdata.hpp"
#include "Request.hpp"

namespace GetItCore
{
    class FormdataRequest: public Request
    {
    public:
        FormdataRequest();
        ~FormdataRequest();

        void addFormdata();
        void removeFormdata();

    protected:
        std::string getBody();

    private:
        std::list<Formdata*> formdata;
    };
}
