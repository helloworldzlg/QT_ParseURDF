#include <QDebug>
#include "domdocument.h"
#include <iostream>

DomDocument::DomDocument()
{
    fileName = "domparse.xml";
}

DomDocument::~DomDocument()
{

}

int DomDocument::writeXml()
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return -2;
    QTextStream out(&file);
    QDomDocument doc;
    QDomText text;
    QDomElement element;
    QDomAttr attr;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction( "xml", "version = \'1.0\' encoding=\'UTF-8\'" );
    doc.appendChild( instruction );

    QDomElement root = doc.createElement( "COMMAND" );
    doc.appendChild(root);
    element = doc.createElement( "OBJECT" );
    text = doc.createTextNode( "USER" );
    element.appendChild(text);
    root.appendChild(element);

    element = doc.createElement( "ACTION" );
    text = doc.createTextNode( "LOGIN" );
    element.appendChild(text);
    root.appendChild(element);

    element = doc.createElement( "DATA" );
    root.appendChild(element);

    QDomElement userElement = doc.createElement( "USERINFO" );
    attr = doc.createAttribute( "NAME" );
    attr.setValue("root");
    userElement.setAttributeNode(attr);
    attr = doc.createAttribute( "PASSWORD" );
    attr.setValue("123456");
    userElement.setAttributeNode(attr);
    element.appendChild(userElement);

    doc.save(out, 4);       //each line space of file is 4
    return 0;
}

int DomDocument::readXml()
{
    QDomDocument doc;
    QFile file(fileName);
    QString error = "";
    int row = 0, column = 0;
    if (!file.open(QIODevice::ReadOnly)) return -2;

    if(!doc.setContent(&file, false, &error, &row, &column)){
        qDebug() << "parse file failed:" << row << "---" << column <<":" <<error;
        file.close();
        return -1;
    }

    file.close();
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChild();
    while(!node.isNull()) {
       QDomElement element = node.toElement(); // try to convert the node to an element.
       if(!element.isNull()) {
          qDebug()<<element.tagName() << ":" << element.text();
          QDomNode nodeson = element.firstChild();
          while(!nodeson.isNull()) {
              QDomElement elementson = nodeson.toElement();
              if(!elementson.isNull()) {
                  qDebug()<< "---" <<elementson.tagName();
                  if (elementson.hasAttribute("NAME")) {
                      qDebug()<< "---" << "NAME=" << elementson.attributeNode("NAME").value();
                  }
                  if (elementson.hasAttribute("PASSWORD")) {
                      qDebug()<< "---" << "PASSWORD=" << elementson.attributeNode("PASSWORD").value();
                  }
              }
              nodeson = nodeson.nextSibling();
          }
       }
       node = node.nextSibling();
    }
    return 0;
}
int DomDocument::readXml2()
{
    QDomDocument doc;
    QFile file(fileName);
    QString error = "";
    int row = 0, column = 0;
    if (!file.open(QIODevice::ReadOnly)) return -2;

    if(!doc.setContent(&file, false, &error, &row, &column)){
        qDebug() << "parse file failed:" << row << "---" << column <<":" <<error;
        file.close();
        return -1;
    }

    file.close();
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChildElement();
    while(!node.isNull()) {
       QDomElement element = node.toElement(); // try to convert the node to an element.
       if(!element.isNull()) {
           if (element.tagName() == "DATA") {
               qDebug()<< "---" <<element.tagName();
                QDomNodeList list = element.childNodes();
                for(int index = 0; index < list.count(); index++) {
                    QDomNode list_node = list.item(index);
                    QDomElement list_element = list_node.toElement();
                    if (list_element.hasAttribute("NAME")) {
                        qDebug()<< "---" << "NAME =" << list_element.attributeNode("NAME").value();
                    }
                    if (list_element.hasAttribute("PASSWORD")) {
                        qDebug()<< "---" << "PASSWORD =" << list_element.attributeNode("PASSWORD").value();
                    }
                }
           }
           else {
               qDebug()<<element.tagName() << ":" << element.text();
           }
       }
       node = node.nextSibling();
    }
    return 0;
}
