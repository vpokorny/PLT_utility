/*
 * =====================================================================================
 *
 *       Filename:  triangle.cpp
 *
 *    Description:  File of source code for methods of object Triangle.
 *
 *        Version:  1.0
 *        Created:  12/07/2016 11:25:50 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Vaclav Pokorny
 *   Organization:  mat.fs.cvut.cz
 *
 * =====================================================================================
 */

#include "triangle.h"

using namespace std;

Triangle::Triangle()
{
    A = 0;
    B = 0;
    C = 0;
}

Triangle::~Triangle()
{

}

void Triangle::TriangleVlozVrcholy(vector<int>& Input)
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

int Triangle::TriangleVypisIndexVrcholu(string Vrchol)
{
    if (Vrchol.compare("A") == 0)
    {
        //cout << "Mam vrchol A" << endl;
        return A - 1;
    }
    else if (Vrchol.compare("B") == 0)
    {
        //cout << "Mam vrchol B" << endl;
        return B - 1;
    }
    else if (Vrchol.compare("C") == 0)
    {
        //cout << "Mam vrchol C" << endl;
        return C - 1;
    }
    else
    {
        cerr << "Vrchol nenalezen ... konec" << endl;
        exit(1);
    }
}
