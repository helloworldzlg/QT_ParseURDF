//
// Created by zlg on 18-3-14.
//

#include <cstring>
#include <QString>
#include <QList>
#include "point.h"

Point::Point(int pointType)
{
    if (POINT_LINK == pointType)
        isLink = true;
    else if (POINT_JOINT == pointType)
        isLink = false;

    memset(m_position, 0, sizeof(m_position));
    memset(m_orientation, 0, sizeof(m_orientation));
    memset(m_color, 0, sizeof(m_color));
    memset(m_axis, 0, sizeof(m_axis));

    m_pParent     = NULL;
}

Point::~Point()
{

}

void Point::UpdateName(QString name)
{
    m_name = name;
}

void Point::UpdatePosition(QString position)
{
    QList<QString> list;

    list = position.split(' ');
    for (int i = 0; i < list.count(); ++i)
    {
        m_position[i] = list.at(i).toDouble();
    }
}

void Point::UpdateOrientation(QString orientation)
{
    QList<QString> list;

    list = orientation.split(' ');
    for (int i = 0; i < list.count(); ++i)
    {
        m_orientation[i] = list.at(i).toDouble();
    }
}

void Point::UpdateColor(QString color)
{
    QList<QString> list;

    list = color.split(' ');
    for (int i = 0; i < list.count(); ++i)
    {
        m_color[i] = list.at(i).toDouble();
    }
}

void Point::UpdateAxis(QString axis)
{
    QList<QString> list;

    list = axis.split(' ');
    for (int i = 0; i < list.count(); ++i)
    {
        m_axis[i] = list.at(i).toDouble();
    }
}

void Point::UpdatePointInfo()
{

}
