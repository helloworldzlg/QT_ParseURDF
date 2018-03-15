#ifndef DOMDOCUMENT_H
#define DOMDOCUMENT_H
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

class DomDocument
{
public:
    DomDocument();
    ~DomDocument();
    int writeXml();
    int readXml();
    int readXml2();

private:
    QString fileName;
};

#endif // DOMDOCUMENT_H
