/*
 * =====================================================================================
 *
 *       Filename:  VTK.h
 *
 *    Description:  Header file for VTK object.
 *
 *        Version:  1.0
 *        Created:  12/26/2016 01:53:40 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Vaclav Pokorny
 *   Organization:  mat.fs.cvut.cz
 *
 * =====================================================================================
 */

#ifndef _VTK_H_
#define _VTK_H_

#include "mesh.h"

class VTK
{
    private:
        double VerzeSouboru;
        string TypUlozenychDat;

    public:
        VTK();
        ~VTK();
        void PreskocRadky(ifstream& file, const int PocetRadku);
        double ZjistiVerziSouboruVTK(string Radek);
        void VypisVerziSouboruVTK();
        string ZjistiTypUlozenychDat(string Radek);
        void VypisTypUlozenychDat();
        int ZjistiPocetBodu(string Radek);
        void VlozSouradniceBodu(ifstream& file, Mesh& mesh);
        int ZjistiPocetElementu(string Radek);
        void VlozVrcholyTriangle(ifstream& file, Mesh& mesh);
        string ZjistiNazevPromenne(string Radek);
        void VlozHodnotyPromennychDoBodu(ifstream& file, Mesh& mesh);
        void ExportujDoVTK(Mesh& mesh, string Filename);
        Mesh NactiSoubor(string Filename);
};

#endif
