/*
 * =====================================================================================
 *
 *       Filename:  mesh.h
 *
 *    Description:  Mesh header file
 *
 *        Version:  1.0
 *        Created:  12/07/2016 11:34:31 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Vaclav Pokorny
 *   Organization:  mat.fs.cvut.cz
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
        int PocetBodu, PocetElementu, PocetPromennych;
        vector<string> NazevPromennych;

    public:
        vector<Triangle> triangle;
        vector<Point> point;

        Mesh();
        int MeshVypisPocetPromennych();
        int MeshVypisPocetBodu();
        int MeshVypisPocetElementu();
        void MeshVlozNazvyPromennych(vector<string> NalezeneNazvyPromennych);
        void MeshVypisNazvyPromennych();
        void MeshVlozPocetPromennych(int NalezenyPocetPromennych);
        void MeshVlozPocetBodu(int NalezenyPocetBodu);
        void MeshVlozPocetElementu(int NalezenuPocetElementu);
        void MeshRealokujPamet();
        void MeshVlozHodnotyDoBodu(int IndexBodu, vector<double>& Promenne);
        void MeshVypisHodnotyPromennychVBode(int IndexBodu);
//      ~Mesh();
};

#endif
