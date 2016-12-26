/*
 * =====================================================================================
 *
 *       Filename:  VTK.cpp
 *
 *    Description:  Source code file for VTK object.
 *
 *        Version:  1.0
 *        Created:  12/26/2016 01:56:27 PM
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
#include <iomanip>
#include "VTK.h"

using namespace std;

VTK::VTK()
{
    cout << "Konstruktor" << endl;
}

VTK::~VTK()
{
    cout << "Destruktor" << endl;
}

string VTK::VytvorNazevVystupnihoSouboru(string Filename)
{
    string DeliciZnak = ".";
    string Pripona (".vtk");

    size_t PoziceDelicihoZnaku = 0;

    try
    {
        if((PoziceDelicihoZnaku = Filename.find(DeliciZnak)) != string::npos)
        {
            Filename = Filename.substr(0, PoziceDelicihoZnaku);
            Filename = Filename + Pripona;
            return Filename;
        }
        else throw 1;
    }

    catch (int error)
    {
        cout << "Chyba pri parsovani Nazvu vystupniho souboru ... (Nenalezen delici znak '.')" << endl;
        exit(1);
    }
}

void VTK::UlozVTKSoubor(Mesh& mesh, string Filename)
{
    const int TRIANGLE = 5;
	ofstream file(VytvorNazevVystupnihoSouboru(Filename).c_str());
    //file.setf(ios::fixed, ios::floatfield);

    file << "# vtk DataFile Version 3.0" << endl
         << "Komentar" << endl
         << "ASCII" << endl
         << endl
         << "DATASET UNSTRUCTURED_GRID" << endl
         << "POINTS " << mesh.MeshVypisPocetBodu() << " float" << endl;
	for(int i = 0; i < mesh.MeshVypisPocetBodu(); i++)
        file << mesh.MeshVypisHodnotuPromenneVBode(i, "X") << " " << mesh.MeshVypisHodnotuPromenneVBode(i, "Y") << " 0.0" << endl;

    file << "CELLS " << mesh.MeshVypisPocetElementu() << " " << (TRIANGLE - 1)  * mesh.MeshVypisPocetElementu() << endl;
	for(int i = 0; i < mesh.MeshVypisPocetElementu(); i++)
        file << "3 " << mesh.MeshVypisVrcholTriangle(i, "A") << " " << mesh.MeshVypisVrcholTriangle(i, "B") << " " << mesh.MeshVypisVrcholTriangle(i, "C") << endl;

    file << "CELL_TYPES " << mesh.MeshVypisPocetElementu() << endl;
	for(int i = 0; i < mesh.MeshVypisPocetElementu(); i++)
        file << TRIANGLE << endl;

    file << "POINT_DATA " << mesh.MeshVypisPocetBodu() << endl;
    for(int i = mesh.MeshPrevedNazevNaHodnotuPromenne("Y") + 1; i < mesh.MeshVypisPocetPromennych(); i++)
    {
        file << "SCALARS " << mesh.MeshVypisNazevPromenne(i) << " float" << endl
             << "LOOKUP_TABLE default" << endl;
        for(int j = 0; j < mesh.MeshVypisPocetBodu(); j ++)
            file << mesh.MeshVypisHodnotuPromenneVBode(j, mesh.MeshVypisNazevPromenne(i)) << endl;
    }

	file.close();
	return;
}
