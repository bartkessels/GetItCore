#include "FormdataRequest.h"

namespace GetItCore
{
    FormdataRequest::FormdataRequest(QList<IFormdata*> formdata, QObject* parent):
        QObject(parent),
        formdata(formdata)
    {
    }

    FormdataRequest::~FormdataRequest()
    {
    }

    void FormdataRequest::send(QString method, QString uri)
    {
        QNetworkRequest request(uri);
        QNetworkAccessManager* manager;
        QUrlQuery* formdata;

        manager     = new QNetworkAccessManager(this);
        formdata    = new QUrlQuery();

        this->setHeaders(&request);
        this->setFormdata(formdata);

        connect(manager, &QNetworkAccessManager::finished, this, &FormdataRequest::requestSent);

        QString tmp = formdata->toString(QUrl::FullyEncoded);

//        manager->sendCustomRequest(request, method.toUtf8(), formdata->toString(QUrl::FullyEncoded).toUtf8());
        manager->post(request, formdata->toString(QUrl::FullyEncoded).toUtf8());
    }

    void FormdataRequest::addCookies(QList<ICookie*> cookies)
    {
        this->cookies = cookies;
    }

    void FormdataRequest::addHeaders(QList<IHeader*> headers)
    {
        this->headers = headers;
    }

    void FormdataRequest::registerListener(IRequestListener* listener)
    {
        this->listeners.append(listener);
    }

    void FormdataRequest::deregisterListener(IRequestListener *listener)
    {
        this->listeners.removeAll(listener);
    }

    void FormdataRequest::requestSent(QNetworkReply* reply)
    {
        QString rep = reply->readAll();
    }

    /**
     * @brief FormdataRequest::setHeaders
     * Iterate over the headers member and append
     * them to the given request
     *
     * @param request
     */
    void FormdataRequest::setHeaders(QNetworkRequest* request)
    {
        foreach(IHeader *header, this->headers) {
            request->setRawHeader(header->getName().toUtf8(), header->getValue().toUtf8());
        }
    }

    /**
     * @brief FormdataRequest::setFormdata
     * Iterate over the formdata member and
     * append them to the given url query
     *
     * @param parameters
     */
    void FormdataRequest::setFormdata(QUrlQuery* parameters)
    {
        foreach(IFormdata* formdata, this->formdata) {
            parameters->addQueryItem(formdata->getName(), formdata->getValue());
        }
    }
}
