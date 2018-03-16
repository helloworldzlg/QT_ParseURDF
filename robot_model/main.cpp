#include <QCoreApplication>
#include <QDebug>
//#include "streamparsexml.h"
#include "domdocument.h"
#include "parserobotmodel.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ParseRobotModel parseRobotModel("robotB.urdf");

    parseRobotModel.ParseModelXml();

    parseRobotModel.printModelTree(parseRobotModel.getRootPoint());

    return a.exec();
}
