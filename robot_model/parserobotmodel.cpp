#include "parserobotmodel.h"
#include "point.h"
#include <QFile>
#include <QDebug>
#include <vector>

void ParseAllLink(ParseRobotModel* parseObj, QDomNode& domNode);
void ParseAllJoint(ParseRobotModel* parseObj, QDomNode& domNode);
void CreateModelTree(std::vector<Point*> &linkTree);
void AddChildToParent(ParseRobotModel* parseObj, QString parent, QString child);

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

    m_rootPoint = NULL;
}

ParseRobotModel::~ParseRobotModel()
{

}

void ParseRobotModel::ParseModelXml()
{
    QDomElement docElem = m_doc.documentElement();
    qDebug() << qPrintable(docElem.tagName()) << qPrintable(docElem.attribute("name"));

    QDomNode firstLevelN;

    firstLevelN = docElem.firstChild();
    ParseAllLink(this, firstLevelN);

    firstLevelN = docElem.firstChild();
    ParseAllJoint(this, firstLevelN);

    return;
}

Point *ParseRobotModel::FindPoint(QString pointName)
{
    Point* currentPoint = NULL;

    for (size_t i = 0; i < m_linkTree.size(); ++i)
    {
        currentPoint = m_linkTree.at(i);
        if (pointName == currentPoint->m_Name)
            return currentPoint;
    }
    return currentPoint;
}

void ParseRobotModel::setRootPoint(Point* rootPoint)
{
    m_rootPoint = rootPoint;
}

Point* ParseRobotModel::getRootPoint()
{
    return m_rootPoint;
}

void ParseRobotModel::printModelTree(Point* currentPoint)
{
    Point* tmpPoint = NULL;
    static int count = 0;

    QString logStr;
    for (int k=0; k<count; ++k)
        logStr += "----";

    qDebug() << logStr << "point name: " << currentPoint->m_Name;
    qDebug() << logStr << "point parent: " << currentPoint->m_Parent;

    for (size_t i = 0; i < currentPoint->m_ChildList.size(); ++i)
    {
        tmpPoint = currentPoint->m_ChildList.at(i);

        //qDebug() << "point name: " << tmpPoint->m_Name;
        //qDebug() << "point parent: " << tmpPoint->m_Parent;
        count++;
        this->printModelTree(tmpPoint);
        count--;
    }
}

void ParseAllLink(ParseRobotModel* parseObj, QDomNode& firstLevelN)
{
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
            {
                firstLevelN = firstLevelN.nextSibling();  //下一个兄弟节点
                continue;
            }

            Point *tmpPoint = new Point(POINT_LINK);
            tmpPoint->UpdateName(firstLevelE.attribute("name"));

            if (firstLevelE.tagName() == "link" && firstLevelE.attribute("name") == "base_link")
                parseObj->setRootPoint(tmpPoint);

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

            parseObj->m_linkTree.push_back(tmpPoint);
        }

        firstLevelN = firstLevelN.nextSibling();  //下一个兄弟节点
    }
}

void ParseAllJoint(ParseRobotModel* parseObj, QDomNode& firstLevelN)
{
    QString parent;
    QString child;

    //如果节点不为空
    while (!firstLevelN.isNull())
    {
        //如果节点是元素
        if (firstLevelN.isElement())
        {
            //将其转换为元素
            QDomElement firstLevelE = firstLevelN.toElement();
            qDebug() << "--" << qPrintable(firstLevelE.tagName()) << qPrintable(firstLevelE.attribute("name"));

            if (firstLevelE.tagName() != "joint")
            {
                firstLevelN = firstLevelN.nextSibling();  //下一个兄弟节点
                continue;
            }

            //获得元素e的所有子节点的列表
            QDomNodeList firstLevelCL = firstLevelE.childNodes();

            //遍历该列表
            for (int i=0; i<firstLevelCL.count(); ++i)
            {
                QDomNode secondLevelN = firstLevelCL.at(i);
                if (secondLevelN.isElement())
                {
                    QDomElement secondLevelE = secondLevelN.toElement();
                    qDebug() << "----" << qPrintable(secondLevelE.tagName()) << qPrintable(secondLevelE.attribute("link"));

                    if ("parent" == secondLevelE.tagName())
                        parent = secondLevelE.attribute("link");

                    if ("child" == secondLevelE.tagName())
                        child = secondLevelE.attribute("link");
                }
            }

            AddChildToParent(parseObj, parent, child);
        }

        firstLevelN = firstLevelN.nextSibling();  //下一个兄弟节点
    }
}

void AddChildToParent(ParseRobotModel* parseObj, QString parent, QString child)
{
    Point* childPoint;
    Point* parentPoint;

    childPoint  = parseObj->FindPoint(child);
    parentPoint = parseObj->FindPoint(parent);

    parentPoint->AddChildList(childPoint);
}
