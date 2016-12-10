/*
 * =====================================================================================
 *
 *       Filename:  point.cpp
 *
 *    Description:  Source code for methods of object Point.
 *
 *        Version:  1.0
 *        Created:  12/07/2016 11:30:06 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Vaclav Pokorny
 *   Organization:  mat.fs.cvut.cz
 *
 * =====================================================================================
 */
#include "point.h"

Point::Point()
{
    HodnotyPromennych.resize(0);
}

void Point::PointVlozHodnotuPromenne(double HodnotaPromenne)
{
        HodnotyPromennych.push_back(HodnotaPromenne);
}

double Point::PointVypisHodnotuPromenne(int IndexPromenne)
{
    return HodnotyPromennych[IndexPromenne];
}
