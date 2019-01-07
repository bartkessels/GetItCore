#include "FormdataRequest.h"

namespace GetItCore
{
    FormdataRequest::FormdataRequest(QList<IFormdata*> formdata, QObject* parent):
        QObject(parent),
        formdata(formdata)
    {
        this->manager   = new QNetworkAccessManager(this);

        QObject::connect(this->manager, &QNetworkAccessManager::finished, this, &FormdataRequest::requestSent);
    }

    FormdataRequest::~FormdataRequest()
    {
        delete this->manager;
    }

    /**
     * @brief FormdataRequest::send
     * Send a HTTP request to the given URI
     *
     * @param method HTTP verb
     * @param uri address of the resource
     */
    void FormdataRequest::send(QString method, QString uri)
    {
        QNetworkRequest request;
        QHttpMultiPart* multiPart;

        multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, this->manager);
        request.setUrl(uri);

        this->addFormdataToMultiPart(multiPart);
        this->addHeadersToRequest(request);
        this->manager->sendCustomRequest(request, method.toUtf8(), multiPart);
    }

    /**
     * @brief FormdataRequest::addHeadersToRequest
     * Add headers to given QNetworkRequest
     *
     * @param request the request to append the headers
     */
    void FormdataRequest::addHeadersToRequest(QNetworkRequest request)
    {
        foreach(IHeader *header, this->headers) {
            request.setRawHeader(header->getName().toUtf8(),
                                 header->getValue().toUtf8());
        }
    }

    /**
     * @brief FormdataRequest::addFormdataToMultiPart
     * Add formdata elements to given QHttpMultiPart
     *
     * @param multiPart the multipart to append the formdata elements
     */
    void FormdataRequest::addFormdataToMultiPart(QHttpMultiPart* multiPart)
    {
        foreach(IFormdata* formdata, this->formdata) {
            QString formdataName = "form-data; name=\"" + formdata->getName().toUtf8() + "\"";

            QHttpPart formdataPart;
            formdataPart.setHeader(QNetworkRequest::ContentDispositionHeader, formdataName);
            formdataPart.setBody(formdata->getValue().toUtf8());

            multiPart->append(formdataPart);
        }
    }

    /**
     * @brief FormdataRequest::setCookies
     * Set the cookies for the request
     *
     * @param cookies list with the cookies
     */
    void FormdataRequest::setCookies(QList<ICookie*> cookies)
    {
        this->cookies = cookies;
    }

    /**
     * @brief FormdataRequest::setHeaders
     * Set the headers for the request
     *
     * @param headers list with the headers
     */
    void FormdataRequest::setHeaders(QList<IHeader*> headers)
    {
        this->headers = headers;
    }

    /**
     * @brief FormdataRequest::registerListener
     * Register listener which will be notified when
     * the request is sent
     *
     * @param listener object to be notified when request is sent
     */
    void FormdataRequest::registerListener(IRequestListener* listener)
    {
        this->listeners.append(listener);
    }

    /**
     * @brief FormdataRequest::deregisterListener
     * Deregister the listener. The listener will no
     * longer be notified when the request is sent
     *
     * @param listener the object which won't be notified when request is sent
     */
    void FormdataRequest::deregisterListener(IRequestListener *listener)
    {
        this->listeners.removeAll(listener);
    }

    /**
     * @brief FormdataRequest::requestSent
     * The request is sent, check the QNetworkReply object
     * what actually happened.
     *
     * Parse the QNetworkReply and put it into an IResponse
     * implementation
     *
     * @param reply
     */
    void FormdataRequest::requestSent(QNetworkReply* reply)
    {
        QString body;
        QList<QNetworkReply::RawHeaderPair> headers;
        IResponse* response; // TODO: Initialize a response, keep in mind that DI should be used!

        body        = reply->readAll();
        headers     = reply->rawHeaderPairs();

        if (reply->error() != QNetworkReply::NetworkError::NoError) {
            this->notifyListenersError();

            return;
        }

        this->notifyListenersSuccess(response);
    }

    /**
     * @brief FormdataRequest::notifyListenersError
     * Notify all the listeners that an error occured
     * when the request was being sent
     *
     */
    void FormdataRequest::notifyListenersError()
    {
        foreach(IRequestListener* listener, this->listeners) {
            listener->requestError();
        }
    }

    /**
     * @brief FormdataRequest::notifyListenersSuccess
     * Notify all the listeners that the request is sent and
     * a response returned
     *
     * @param response the IResponse to pass to the listeners
     */
    void FormdataRequest::notifyListenersSuccess(IResponse* response)
    {
        foreach(IRequestListener* listener, this->listeners) {
            listener->requestSent(response);
        }
    }
}
