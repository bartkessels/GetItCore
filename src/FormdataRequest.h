#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

#include "ICookie.h"
#include "IFormdata.h"
#include "IHeader.h"
#include "IResponse.h"
#include "IRequest.h"
#include "IRequestListener.h"
#include "Response.h"

#include <QtDebug>

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
        void setCookies(QList<ICookie*> cookies);
        void setHeaders(QList<IHeader*> headers);

        void registerListener(IRequestListener* listener);
        void deregisterListener(IRequestListener* listener);

    private:
        void addHeadersToRequest(QNetworkRequest request);
        void addFormdataToMultiPart(QHttpMultiPart* multiPart);

        void notifyListenersError();
        void notifyListenersTimedOut();
        void notifyListenersSuccess(IResponse* response);

        QList<IRequestListener*> listeners;
        QList<ICookie*> cookies;
        QList<IHeader*> headers;
        QList<IFormdata*> formdata;

        IResponse* response;
        QNetworkAccessManager* manager;

    private slots:
        void requestSent(QNetworkReply* reply);
    };
}
