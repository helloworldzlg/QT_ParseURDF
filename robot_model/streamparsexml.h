#ifndef STREAMPARSEXML_H
#define STREAMPARSEXML_H
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>

class StreamParseXml
{
public:
    StreamParseXml();
    ~StreamParseXml();
    int writeXml();
    int readXml();

private:
    void parseUserInformation();
    QString getValue(const QString &name);
    QString getAttribute(const QString &name);

private:
    QString fileName;
    QXmlStreamReader *reader;
};

#endif // STREAMPARSEXML_H
