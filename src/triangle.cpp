/*
 * =====================================================================================
 *
 *       Filename:  triangle.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/07/2016 11:25:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "triangle.h"

Triangle::Triangle()
{
    A = 0;
    B = 0;
    C = 0;
}

void Triangle::TriangleVlozVrcholy(vector<double>& Input)
{
    A = Input[0];
    B = Input[1];
    C = Input[2];
}

void Triangle::TriangleVypisVrcholy()
{
    cout << "Vrcholy:" << endl;
    cout << "A :" << A << endl;
    cout << "B :" << B << endl;
    cout << "C :" << C << endl;
    cout << "--------" << endl;
}
