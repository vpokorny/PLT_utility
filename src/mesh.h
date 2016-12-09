/*
 * =====================================================================================
 *
 *       Filename:  mesh.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/07/2016 11:34:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _MESH_H_
#define _MESH_H_

#include <cstdio>
#include <iostream>
#include <vector>

#include "point.h"
#include "triangle.h"

using namespace std;

//declare constants
class Mesh {
    private:
        int PocetBodu, PocetElementu;

    public:
        vector<Triangle> triangle;
        vector<Point> point;

        Mesh();
        int MeshVypisPocetBodu();
        int MeshVypisPocetElementu();
        void MeshVlozPocetBodu(int NalezenyPocetBodu);
        void MeshVlozPocetElementu(int NalezenuPocetElementu);
        void MeshRealokujPamet();
//        ~Mesh();
};

#endif
