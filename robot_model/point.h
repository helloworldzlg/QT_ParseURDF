//
// Created by zlg on 18-3-14.
//

#ifndef ROBOT_MODEL_POINT_H
#define ROBOT_MODEL_POINT_H
#include <vector>
#include <QString>

typedef enum
{
    POINT_LINK  = 0,
    POINT_JOINT = 1,
}POINT_TYPE_E;

class Point
{
public:
    Point(int pointType);
    ~Point();

    QString m_Name;
    QString m_Parent;
    std::vector<Point*> m_ChildList;

    void UpdateName(QString name);
    void UpdateParent(QString parent);
    void UpdatePosition(QString position);
    void UpdateOrientation(QString orientation);
    void UpdateColor(QString color);
    void UpdateAxis(QString axis);
    void AddChildList(Point* child);

private:
    bool isLink;
    double m_position[3];
    double m_orientation[3];
    double m_color[4];
    double m_axis[3];
    //Point *m_brothers;
    //Point *m_firstChild;
};


#endif //ROBOT_MODEL_POINT_H
