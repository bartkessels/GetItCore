#pragma once

#include <QString>
#include <QList>

#include "IHeader.h"
#include "IResponse.h"

namespace GetItCore
{
    class Response: public IResponse
    {
    public:
        Response(QString body, QList<IHeader*> headers);
        ~Response();

        QList<IHeader*> getHeaders();
        QString getBody();

    private:
        QString body;
        QList<IHeader*> headers;
    };
}
