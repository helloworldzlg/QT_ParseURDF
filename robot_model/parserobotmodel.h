#ifndef PARSEROBOTMODEL_H
#define PARSEROBOTMODEL_H
#include <QDomDocument>
#include <vector>
#include "point.h"

//#include <QFile>
//#include <QTextStream>
//#include <string>

class ParseRobotModel
{
public:
    ParseRobotModel(QString modelFile);
    ~ParseRobotModel();

    std::vector<Point*> m_linkTree;

    void ParseModelXml();
    Point *FindPoint(QString pointName);
    void setRootPoint(Point* rootPoint);
    Point* getRootPoint();
    void printModelTree(Point* currentPoint);
private:
    QString m_modelFile;
    QDomDocument m_doc;
    Point* m_rootPoint;
};

#endif // PARSEROBOTMODEL_H
