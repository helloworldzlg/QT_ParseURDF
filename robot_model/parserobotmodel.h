#ifndef PARSEROBOTMODEL_H
#define PARSEROBOTMODEL_H
#include <QDomDocument>
#include "point.h"

//#include <QFile>
//#include <QTextStream>
//#include <string>

class ParseRobotModel
{
public:
    ParseRobotModel(QString modelFile);
    ~ParseRobotModel();

    Point &ParseModelXml();
private:
    QString m_modelFile;
    QDomDocument m_doc;
};

#endif // PARSEROBOTMODEL_H
