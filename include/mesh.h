/*
 * =====================================================================================
 *
 *       Filename:  mesh.h
 *
 *    Description:  Header file for object Mesh.
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
        int PocetBodu, PocetElementu, PocetPromennych, PocetHran;
        vector<string> NazevPromennych;
        vector<Point> point;
        vector<Triangle> triangle;

    public:
        Mesh();
        ~Mesh();
        int MeshVypisPocetPromennych();
        int MeshVypisPocetBodu();
        int MeshVypisPocetElementu();
        void MeshVlozNazvyPromennych(vector<string> NalezeneNazvyPromennych);
        void MeshVlozNazevPromene(string NazevPromenne);
        void MeshVypisNazvyPromennych();
        void MeshVlozPocetPromennych(int NalezenyPocetPromennych);
        void MeshVlozPocetBodu(int NalezenyPocetBodu);
        void MeshVlozPocetElementu(int NalezenuPocetElementu);
        void MeshRealokujPametBodu(const int PocetBodu);
        void MeshRealokujPametElementu(const int PocetElementu);
        void MeshVlozHodnotuDoBodu(int IndexBodu, double Hodnota);
        void MeshVlozHodnotyDoBodu(int IndexBodu, vector<double>& Promenne);
        void MeshVypisHodnotyPromennychVBode(int IndexBodu);
        string MeshVypisNazevPromenne(int IndexPromenne);
        int MeshPrevedNazevNaHodnotuPromenne(string Promenna);
        int MeshVypisVrcholTriangle(int IndexTriangle, string Promenna);
        double MeshVypisHodnotuPromenneVBode(int IndexBodu, string Promenna);
        double MeshVypisPromennouVeVrcholuTriangle(int IndexTriangle, string Vrchol, string Promenna);
        Point MeshPrepisPromenneZBoduDoBodu(Point VkladanyBod);
        void MeshVlozHodnotyDoTriangle(int IndexElementu, vector<int>& VkladaneHodnoty);
};

#endif
