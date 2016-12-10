/*
 * =====================================================================================
 *
 *       Filename:  mesh.cpp
 *
 *    Description:  Mesh object source code
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
#include "mesh.h"

Mesh::Mesh()
{
    PocetBodu = 0;
    PocetElementu = 0;

    triangle.resize(PocetElementu);
    point.resize(PocetBodu);
}

void Mesh::MeshVlozNazvyPromennych(vector<string> NalezeneNazvyPromennych)
{
    for(int i = 0; i < NalezeneNazvyPromennych.size(); i++)
        NazevPromennych.push_back(NalezeneNazvyPromennych[i]);
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

void Mesh::MeshRealokujPamet()
{
    cout << "Realokuji pamet pro Body na: " << PocetBodu << endl;
    cout << "Realokuji pamet pro Elementy na: " << PocetElementu << endl;
    triangle.resize(PocetElementu);
    point.resize(PocetBodu);
    cout << "Hotovo ..." << endl;
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
