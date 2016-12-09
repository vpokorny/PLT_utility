/*
 * =====================================================================================
 *
 *       Filename:  point.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/07/2016 11:30:06 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "point.h"

Point::Point()
{
    X = 0.;
    Y = 0.;
    U = 0.;
    V = 0.;
    P = 0.;
    velocity = 0.;
    vorticity = 0.;
    K = 0.;
    omega = 0.;
}

void Point::PointVlozHodnoty(vector<double>& Input)
{
    X = Input[0];
    Y = Input[1];
    U = Input[2];
    V = Input[3];
    P = Input[4];
    velocity = Input[5];
    vorticity = Input[6];
    K = Input[7];
    omega = Input[8];
}

void Point::PointVypisHodnoty()
{
    cout << "X: " << X << endl;
    cout << "Y: " << Y << endl;
    cout << "U: " << U << endl;
    cout << "V: " << V << endl;
    cout << "P: " << P << endl;
    cout << "velocity: " << velocity << endl;
    cout << "vorticity: " << vorticity << endl;
    cout << "K: " << K << endl;
    cout << "Omega: " << omega << endl;
}
