#include <QCoreApplication>
#include <QDebug>
//#include "streamparsexml.h"
#include "domdocument.h"
#include "parserobotmodel.h"

using namespace std;

int main(int argc, char *argv[])
{
    //int errorLine, errorCol;
    //QString errorStr;

    QCoreApplication a(argc, argv);

    //Point originPoint(POINT_LINK);
    ParseRobotModel parseRobotModel("robotA.xml");
    parseRobotModel.ParseModelXml();

//    QDomDocument doc;

#if 0
    //QFile file("my.xml");
    QFile file("robotA.xml");

    if (!file.open(QIODevice::ReadWrite))
        return 0;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorCol))
    {
        qDebug() << errorStr << "line: " << errorLine << "col: " << errorCol;
        file.close();
        return 0;
    }

    file.close();

    QDomElement docElem = doc.documentElement();
    qDebug() << qPrintable(docElem.tagName()) << qPrintable(docElem.attribute("name"));

    QDomNode firstLevelN = docElem.firstChild();

    //如果节点不为空
    while (!firstLevelN.isNull())
    {
        //如果节点是元素
        if (firstLevelN.isElement())
        {
            //将其转换为元素
            QDomElement firstLevelE = firstLevelN.toElement();
            qDebug() << "--" << qPrintable(firstLevelE.tagName()) << qPrintable(firstLevelE.attribute("name"));

            //获得元素e的所有子节点的列表
            QDomNodeList firstLevelCL = firstLevelE.childNodes();

            //遍历该列表
            for (int i=0; i<firstLevelCL.count(); ++i)
            {             
                QDomNode secondLevelN = firstLevelCL.at(i);
                if (secondLevelN.isElement())
                {
                    QDomElement secondLevelE = secondLevelN.toElement();
                    qDebug() << "----" << qPrintable(secondLevelE.tagName()) << qPrintable(secondLevelE.attribute("name"));

                    QDomNodeList secondLevelCL = secondLevelE.childNodes();

                    for (int j=0; j<secondLevelCL.count(); ++j)
                    {
                        QDomNode thirdLevelN = secondLevelCL.at(j);

                        QDomElement thirdLevelE = thirdLevelN.toElement();
                        qDebug() << "------" << qPrintable(thirdLevelE.tagName()) << qPrintable(thirdLevelE.attribute("name"));
                    }
                }
            }
        }

        firstLevelN = firstLevelN.nextSibling();  //下一个兄弟节点
    }
#endif
    return a.exec();
}
