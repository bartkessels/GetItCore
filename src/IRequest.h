#pragma once

#include <QList>
#include <QObject>
#include <QString>

#include "ICookie.h"
#include "IHeader.h"
#include "IRequestListener.h"

namespace GetItCore
{
    class IRequest
    {
    public:
        virtual ~IRequest(){}

        virtual void addCookies(QList<ICookie*> cookies) = 0;
        virtual void addHeaders(QList<IHeader*> headers) = 0;
        virtual void send(QString httpMethod, QString uri) = 0;
        virtual void registerListener(IRequestListener* listener) = 0;
        virtual void deregisterListener(IRequestListener* listener) = 0;
    };
}

Q_DECLARE_INTERFACE(GetItCore::IRequest, "GetItCore::IRequest")
