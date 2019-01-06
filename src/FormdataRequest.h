#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

#include "ICookie.h"
#include "IFormdata.h"
#include "IHeader.h"
#include "IRequest.h"
#include "IRequestListener.h"

namespace GetItCore
{
    class FormdataRequest: public QObject, public IRequest
    {
        Q_OBJECT
        Q_INTERFACES(GetItCore::IRequest)

    public:
        FormdataRequest(QList<IFormdata*> formdata, QObject* parent = nullptr);
        ~FormdataRequest();

        void send(QString httpMethod, QString uri);
        void addCookies(QList<ICookie*> cookies);
        void addHeaders(QList<IHeader*> headers);

        void registerListener(IRequestListener* listener);
        void deregisterListener(IRequestListener* listener);

    private:
        void setHeaders(QNetworkRequest* request);
        void setFormdata(QUrlQuery* parameters);

        QList<IRequestListener*> listeners;
        QList<ICookie*> cookies;
        QList<IHeader*> headers;
        QList<IFormdata*> formdata;

    private slots:
        void requestSent(QNetworkReply* reply);
    };
}
