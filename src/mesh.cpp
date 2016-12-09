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
#include "mesh.h"

Mesh::Mesh()
{
    PocetBodu = 0;
    PocetElementu = 0;

    triangle.resize(PocetElementu);
    point.resize(PocetBodu);
}

int Mesh::MeshVypisPocetBodu()
{
    return PocetBodu;
}

int Mesh::MeshVypisPocetElementu()
{
    return PocetElementu;
}

void Mesh::MeshVlozPocetBodu(int NalezenyPocetBodu)
{
    PocetBodu = NalezenyPocetBodu;
}

void Mesh::MeshVlozPocetElementu(int NalezenyPocetElementu)
{
    PocetElementu = NalezenyPocetElementu;
}

void Mesh::MeshRealokujPamet()
{
    cout << "Realokuji pamet pro Body na: " << PocetBodu << endl;
    cout << "Realokuji pamet pro Elementy na: " << PocetElementu << endl;
    triangle.resize(PocetElementu);
    point.resize(PocetBodu);
    cout << "Hotovo ..." << endl;
}
