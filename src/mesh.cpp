/*
 * =====================================================================================
 *
 *       Filename:  mesh.cpp
 *
 *    Description:  File of source code for object Mesh.
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

#include "../include/mesh.h"

Mesh::Mesh()
{
    PocetBodu = 0;
    PocetElementu = 0;
    PocetHran = 0;

    triangle.resize(PocetElementu);
    point.resize(PocetBodu);
    //edge.resize(PocetHran);
}

Mesh::~Mesh()
{

}

void Mesh::MeshVlozNazvyPromennych(vector<string> NalezeneNazvyPromennych)
{
    for(int i = 0; i < NalezeneNazvyPromennych.size(); i++)
        NazevPromennych.push_back(NalezeneNazvyPromennych[i]);
}

void Mesh::MeshVlozNazevPromene(string NazevPromenne)
{
    NazevPromennych.push_back(NazevPromenne);
}

void Mesh::MeshVlozPocetPromennych(int NalezenyPocetPromennych)
{
    PocetPromennych = NalezenyPocetPromennych;
}

void Mesh::MeshVlozPocetBodu(int NalezenyPocetBodu)
{
    PocetBodu = NalezenyPocetBodu;
}

void Mesh::MeshVlozPocetElementu(int NalezenyPocetElementu)
{
    PocetElementu = NalezenyPocetElementu;
}

int Mesh::MeshVypisPocetPromennych()
{
    return NazevPromennych.size();
}

int Mesh::MeshVypisPocetBodu()
{
    return PocetBodu;
}

int  Mesh::MeshVypisPocetElementu()
{
    return PocetElementu;
}

void Mesh::MeshVypisNazvyPromennych()
{
    cout << "-----------------------------" << endl
         << "Vypis nalezenych promennych :" << endl
         << "-----------------------------" << endl;

    for(int i = 0; i < NazevPromennych.size(); i++)
        cout << NazevPromennych[i] << endl;

    cout << "--------------" << endl
         << "Konec vypisu." << endl
         << "--------------" << endl;
}

void Mesh::MeshRealokujPametBodu(const int PocetBodu)
{
    cout << "Realokuji pamet pro Body na: " << PocetBodu << endl;
    point.resize(PocetBodu);
    cout << "Hotovo ..." << endl;
}

void Mesh::MeshRealokujPametElementu(const int PocetElementu)
{
    cout << "Realokuji pamet pro Elementy na: " << PocetElementu << endl;
    triangle.resize(PocetElementu);
    cout << "Hotovo ..." << endl;
}

void Mesh::MeshVlozHodnotuDoBodu(int IndexBodu, double Hodnota)
{
    point.at(IndexBodu).PointVlozHodnotuPromenne(Hodnota);
}

void Mesh::MeshVlozHodnotyDoBodu(int IndexBodu, vector<double>& Promenne)
{
    if(Promenne.size() == NazevPromennych.size())
        for(int j = 0; j < NazevPromennych.size(); j++)
            point[IndexBodu].PointVlozHodnotuPromenne(Promenne[j]);
    else
    {
        cerr << "Cout Pocet promennych neni shodny s poctem vkladanych hodnot Promennych ..." << endl;
        exit(1);
    }
}

void Mesh::MeshVypisHodnotyPromennychVBode(int IndexBodu)
{
    cout << "Vypis hodnot promennych v bode " << IndexBodu << " :" << endl
        << "----------------------------------" << endl;
    for(int i = 0; i < MeshVypisPocetPromennych(); i++)
        cout << NazevPromennych[i] << " : " << point[IndexBodu].PointVypisHodnotuPromenne(i) << endl;

    cout << "--------------------------------" << endl
        << "Konec vypisu." << endl;

}

string Mesh::MeshVypisNazevPromenne(int IndexPromenne)
{
    return NazevPromennych.at(IndexPromenne);
}

int Mesh::MeshPrevedNazevNaHodnotuPromenne(string Promenna)
{
    for(int i = 0; i < MeshVypisPocetPromennych(); i++)
    {
        if(MeshVypisNazevPromenne(i).compare(Promenna) == 0)
        {
            //cout << "Nalezena shoda: " << Promenna << " je " << i << "-ty prvek vektoru" << endl;
            return i;
        }
    }
    cerr << Promenna << " nenalezena v seznamu promennych ... exit " << endl;
    exit(1);
}

double Mesh::MeshVypisHodnotuPromenneVBode(int IndexBodu, string Promenna)
{
    return point.at(IndexBodu).PointVypisHodnotuPromenne(MeshPrevedNazevNaHodnotuPromenne(Promenna));
}

int Mesh::MeshVypisVrcholTriangle(int IndexTriangle, string Promenna)
{
    return triangle.at(IndexTriangle).TriangleVypisIndexVrcholu(Promenna);
}

double Mesh::MeshVypisPromennouVeVrcholuTriangle(int IndexTriangle, string Vrchol, string Promenna)
{
    return MeshVypisHodnotuPromenneVBode(MeshVypisVrcholTriangle(IndexTriangle, Vrchol), Promenna);
}

Point Mesh::MeshPrepisPromenneZBoduDoBodu(Point VkladanyBod)
{
    Point Nosic;

    for(int i = 0; i < VkladanyBod.PointVypisVelikostVektoru(); i++)
        Nosic.PointVlozHodnotuPromenne(VkladanyBod.PointVypisHodnotuPromenne(i));

    return Nosic;
}

void Mesh::MeshVlozHodnotyDoTriangle(int IndexElementu, vector<int>& VkladaneHodnoty)
{
    triangle.at(IndexElementu).TriangleVlozVrcholy(VkladaneHodnoty);
}
