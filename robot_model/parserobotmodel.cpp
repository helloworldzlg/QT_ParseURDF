#include "parserobotmodel.h"
#include "point.h"
#include <QFile>
#include <QDebug>
#include <vector>

ParseRobotModel::ParseRobotModel(QString modelFile)
{
    m_modelFile = modelFile;
    int errorLine, errorCol;
    QString errorStr;

    QFile file(m_modelFile);

    if (!file.open(QIODevice::ReadWrite))
        return;

    if (!m_doc.setContent(&file, false, &errorStr, &errorLine, &errorCol))
    {
        qDebug() << errorStr << "line: " << errorLine << "col: " << errorCol;
        file.close();
        return;
    }

    file.close();
}

ParseRobotModel::~ParseRobotModel()
{

}

Point &ParseRobotModel::ParseModelXml()
{
    Point originPoint(POINT_LINK);
    std::vector<Point*> linkTree;

    QDomElement docElem = m_doc.documentElement();
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

            if (firstLevelE.tagName() != "link")
                continue;

            Point *tmpPoint = new Point(POINT_LINK);
            tmpPoint->UpdateName(firstLevelE.attribute("name"));

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
                        qDebug() << "------" << qPrintable(thirdLevelE.tagName()) << qPrintable(thirdLevelE.attribute("rpy"));

                        if (secondLevelE.tagName() == "visual" && thirdLevelE.tagName() == "origin")
                        {
                            tmpPoint->UpdatePosition(thirdLevelE.attribute("xyz"));
                            tmpPoint->UpdateOrientation(thirdLevelE.attribute("rpy"));
                        }
                    }
                }
            }

            linkTree.push_back(tmpPoint);
        }

        firstLevelN = firstLevelN.nextSibling();  //下一个兄弟节点
    }
    return originPoint;
}
