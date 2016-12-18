/*
 * =====================================================================================
 *
 *       Filename:  intersect.h
 *
 *    Description:  Header file for object Intersection.
 *
 *        Version:  1.0
 *        Created:  12/07/2016 09:35:16 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Vaclav Pokorny
 *   Organization:  mat.fs.cvut.cz
 *
 * =====================================================================================
 */

#ifndef _INTERSECT_H_
#define _INTERSECT_H_

#include "mesh.h"

class Intersection
{
    private:
        vector<Point> Rez;

    public:
        Intersection();
        ~Intersection();
        double NajdiZadanyBodRezu(string Vstup);
        string NajdiZadanouPromennouRezu(Mesh& mesh, string Vstup);
        string NajdiPromennouVRezu(Mesh& mesh, string ZadanaPromennaRezu);
        bool IsInRange(double SpodniHranice, double HorniHranice, double ZkoumanaHodnota);
        double VypocitejThetu(double BodRezu, int IndexTriangle, string PocatecniVrchol, string KoncovyVrchol, string Promenna, Mesh& mesh);
        Point VypocitejBodRezu(int IndexTriangle, double Theta, string PocatecniVrchol, string KoncovyVrchol, Mesh& mesh);
        void VymenHodnotyBoduRezu(Mesh& mesh, int PrvniIndex, int DruhyIndex);
        void SetridRezQuicksortemPodlePromenne(Mesh& mesh, string Promenna, int PocatecniIndex, int KoncovyIndex);
        void VypisSekvenciRezu(Mesh& mesh);
        void VypisSekvenciRezuDlePromenne(Mesh& mesh, string Promenna);
        void ZkontrolujVstupniParametryRezu(double DanyPocatecniBod, double DanyKoncovyBod, int DanyPocetRezu);
        bool JsouBodyStejne(Point& BodJedna, Point& BodDva);
        bool JsouSiDoubleRovny(double PrvniCislo, double DruheCislo);
        vector<Point> EliminujDublovaneHodnotyRezu();
        void VlozBodRezuNaPozici(int IndexPozice, Point& VkladanyBod);
        void UlozBodyRezuProGnuplot(Mesh& mesh, string Filename);
        void ProvedRez(int argc, char* argv[], Mesh& mesh);
};

#endif
