#include <QDebug>
#include "streamparsexml.h"

StreamParseXml::StreamParseXml()
{
    fileName = "streamparse.xml";
}

StreamParseXml::~StreamParseXml()
{

}

int StreamParseXml::writeXml()
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("COMMAND");
        writer.writeTextElement("OBJECT", "USER");
        writer.writeTextElement("ACTION", "LOGIN");
        writer.writeStartElement("DATA");
        writer.writeStartElement("USER");
        writer.writeAttribute("NAME", "root");
        writer.writeAttribute("PASSWORD", "123456");
        writer.writeEndElement();
        writer.writeEndElement();
        writer.writeEndElement();
        file.close();
    }
    return 0;
}

int StreamParseXml::readXml()
{
    if(fileName.isEmpty()) return -2;
    QFile *file = new QFile(fileName);
    if(!file->open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(NULL, QString("title"), QString("open error!"));
        return -1;
    }
    reader = new QXmlStreamReader(file);
     while(!reader->atEnd() && !reader->hasError()) {
         QXmlStreamReader::TokenType token = reader->readNext();
         if(token == QXmlStreamReader::StartDocument) {
             continue;
         }
          if (reader->isStartElement() && reader->name() == "OBJECT") {
              QString elementText = reader->readElementText();
              if (elementText == "USER") {
                  parseUserInformation();
                  break;
              }
          }
     }
    if (reader->hasError()) {
        qDebug() << reader->errorString();
        //QMessageBox::information(NULL, QString("parseXML"), reader->errorString());
    }
    reader->clear();
    delete reader;
    reader = NULL;
    return 0;
}

void StreamParseXml::parseUserInformation()
{
    QString elementString = getValue("ACTION");
    if (elementString == "LOGIN") {
        while(!reader->atEnd()) {
            reader->readNext();
            if (reader->name() == "USER") {
                QXmlStreamAttributes attributes = reader->attributes();
                if(attributes.hasAttribute("NAME")) {
                    qDebug() << "USER=" << attributes.value("NAME").toString();
                }
                if(attributes.hasAttribute("PASSWORD")) {
                    qDebug() << "PASSWORD=" << attributes.value("PASSWORD").toString();
                }
            }
        }
    }
}
QString StreamParseXml::getValue(const QString &name)
{
    while(!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement() && reader->name() == name) {
            return reader->readElementText();
        }
    }
    return "";
}
