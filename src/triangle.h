/*
 * =====================================================================================
 *
 *       Filename:  triangle.h
 *
 *    Description:  Header file for object Triangle.
 *
 *        Version:  1.0
 *        Created:  12/07/2016 11:22:43 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Vaclav Pokorny
 *   Organization:  mat.fs.cvut.cz
 *
 * =====================================================================================
 */

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Triangle {
    private:
        int A, B, C;

    public:
        Triangle();
        ~Triangle();
        void TriangleVlozVrcholy(vector<int>& Input);
        void TriangleVypisVrcholy();
        int TriangleVypisIndexVrcholu(string Vrchol);
};

#endif
