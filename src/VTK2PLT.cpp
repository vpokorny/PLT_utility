/*
 * =====================================================================================
 *
 *       Filename:  VTK2PLT.cpp
 *
 *    Description:  Program for conversion VKT files to PLT files.
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
#include "../include/mesh.h"
#include "../include/PLT.h"
#include "../include/VTK.h"

using namespace std;

inline void ZkontrolujVstupniParametry(int argc, char* argv[])
{
    try
    {
        cout << "Kontroluji vstupni hodnoty ..." << endl;
        if(argc != 3)
            throw 1;
    }

    catch (int x)
    {
        cerr << "Usage: " << argv[0] << " 'InputFilename'" << " 'OutputFilename'" << endl;
		exit(0);
    }
    cout << " Vstupni parametry jsou v poradku ..." << endl;
}

int main (int argc, char* argv[])
{
    ZkontrolujVstupniParametry(argc, argv);

	VTK vtk;
    Mesh mesh = vtk.NactiSoubor(argv[1]);

    PLT plt;
	plt.PLTExportujDoPLT(mesh, argv[2]);

    return 0;
}

