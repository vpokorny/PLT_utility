/*
 * =====================================================================================
 *
 *       Filename:  PLT2VTK.cpp
 *
 *    Description:  Program for conversion PLT files to VTK files.
 *
 *        Version:  1.0
 *        Created:  12/26/2016 01:50:04 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Vaclav Pokorny
 *   Organization:  mat.fs.cvut.cz
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
#include "mesh.h"
#include "PLT.h"
#include "VTK.h"

using namespace std;

inline void ZkontrolujVstupniParametry(int argc, char* argv[])
{
    try
    {
        cout << "Kontroluji vstupni hodnoty ..." << endl;
        if(argc != 2)
            throw 1;
    }

    catch (int x)
    {
        cerr << "Usage: " << argv[0] << " 'InputFilename'" << endl;
		exit(0);
    }

    cout << " Vstupni parametry jsou v poradku ..." << endl;
}

int main (int argc, char* argv[])
{
    ZkontrolujVstupniParametry(argc, argv);

    PLT plt;
    Mesh mesh = plt.PLTNactiSoubor(argv[1]);

	VTK vtk;
	vtk.UlozVTKSoubor(mesh, argv[1]);

    return 0;
}

