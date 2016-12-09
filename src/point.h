/*
 * =====================================================================================
 *
 *       Filename:  point.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/07/2016 10:28:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _POINT_H_
#define _POINT_H_

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

//declare constants
class Point {
    private:
        double X, Y, U, V, P, velocity, vorticity, K, omega;

    public:
        Point();
        void PointVlozHodnoty(vector<double>& Input);
        void PointVypisHodnoty();
//        ~Point();
};

#endif
