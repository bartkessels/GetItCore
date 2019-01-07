#include "Response.h"

namespace GetItCore
{
    Response::Response(QString body, QList<IHeader*> headers):
        body(body),
        headers(headers)
    {
    }

    Response::~Response()
    {

    }

    QList<IHeader*> Response::getHeaders()
    {
        return this->headers;
    }

    QString Response::getBody()
    {
        return this->body;
    }
}
