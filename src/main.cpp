#include <QCoreApplication>
#include <QtDebug>

#include "TextFormdata.h"
#include "IFormdata.h"
#include "IHeader.h"
#include "Header.h"
#include "IRequest.h"
#include "FormdataRequest.h"

using namespace GetItCore;

int main(int argc, char **argv)
{
    // Create some formdata elements
    QList<IFormdata*> formdata;

    formdata.append(new TextFormdata("Test", "Hallo"));
    formdata.append(new TextFormdata("username", "bartkessels"));
    formdata.append(new TextFormdata("password", "barthos"));

    // Create some headers
    QList<IHeader*> headers;

    headers.append(new Header("Accept-Language", "CHINA"));
    headers.append(new Header("Content-Type", "application/json"));

    // Create the actual request
    IRequest *request = new FormdataRequest(formdata);
    request->setHeaders(headers);

    request->send("POST", "http://localhost:5000/post.php");

    QCoreApplication a(argc, argv);
    return a.exec();
}
