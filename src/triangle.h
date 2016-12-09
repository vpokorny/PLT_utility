/*
 * =====================================================================================
 *
 *       Filename:  triangle.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/07/2016 11:22:43 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//declare constants
class Triangle {
    private:
        int A, B, C;

    public:
        Triangle();
        void TriangleVlozVrcholy(vector<double>& Input);
        void TriangleVypisVrcholy();
//        ~Triangle();
};

#endif
