/*
 * =====================================================================================
 *
 *       Filename:  point.h
 *
 *    Description:  Header file for object Point.
 *
 *        Version:  1.0
 *        Created:  12/07/2016 10:28:11 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Vaclav Pokorny
 *   Organization:  mat.fs.cvut.cz
 *
 * =====================================================================================
 */

#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <vector>

using namespace std;

//declare constants
class Point {
    private:
        vector<double> HodnotyPromennych;

    public:
        Point();
        ~Point();
        void PointVlozHodnotuPromenne(double HodnotaPromenne);
        double PointVypisHodnotuPromenne(int IndexPromenne);
        int PointVypisVelikostVektoru();
        void PointVypisHodnotyPromennych();
};

#endif
