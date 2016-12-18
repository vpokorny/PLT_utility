/*
 * =====================================================================================
 *
 *       Filename:  intersect.cpp
 *
 *    Description:  File of source code of methods for object Intersect.
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

#include <iostream>
#include <fstream>
#include <cmath>
#include "intersect.h"
#include "mesh.h"

using namespace std;

Intersection::Intersection()
{
    cout << "Konstruuji objekt Intersection ..." << endl;
    Rez.resize(0);
    cout << "Hotovo ..." << endl;
}

Intersection::~Intersection()
{
    cout << "Destruuji objekt Intersection ..." << endl;
    cout << "Hotovo ..." << endl;
}

double Intersection::VypocitejThetu(double BodRezu, int IndexTriangle, string PocatecniVrchol, string KoncovyVrchol, string Promenna, Mesh& mesh)
{
        return (BodRezu - mesh.MeshVypisPromennouVeVrcholuTriangle(IndexTriangle, PocatecniVrchol, Promenna)) / (mesh.MeshVypisPromennouVeVrcholuTriangle(IndexTriangle, KoncovyVrchol, Promenna) - mesh.MeshVypisPromennouVeVrcholuTriangle(IndexTriangle, PocatecniVrchol, Promenna));
}

Point Intersection::VypocitejBodRezu(int IndexTriangle, double Theta, string PocatecniVrchol, string KoncovyVrchol, Mesh& mesh)
{
    /*
    cout << "Vypis Bodu Rezu:" << endl
         << "---------------" << endl
         << "Theta je: " << Theta << endl;
         */

    Point BodRezu;
    for(int i = 0; i < mesh.MeshVypisPocetPromennych(); i++)
    {
        BodRezu.PointVlozHodnotuPromenne(Theta * mesh.MeshVypisPromennouVeVrcholuTriangle(IndexTriangle, KoncovyVrchol, mesh.MeshVypisNazevPromenne(i)) + (1 - Theta) * mesh.MeshVypisPromennouVeVrcholuTriangle(IndexTriangle, PocatecniVrchol, mesh.MeshVypisNazevPromenne(i)));
        //cout << "Promenna: " << mesh.MeshVypisNazevPromenne(i) << " --> " << BodRezu.PointVypisHodnotuPromenne(i) << endl;
    }
    /*
    cout << "Konec vypisu." << endl
         << "-------------" << endl;
         */
    return BodRezu;
}

bool Intersection::IsInRange(double SpodniHranice, double HorniHranice, double ZkoumanaHodnota)
{
    return (SpodniHranice <= ZkoumanaHodnota && ZkoumanaHodnota <= HorniHranice) ? true : false;
}

void Intersection::ZkontrolujVstupniParametryRezu(double DanyPocatecniBod, double DanyKoncovyBod, int DanyPocetRezu)
{
    try
    {
        if (DanyPocetRezu == 0)
            throw 2;
        if (DanyPocatecniBod == DanyKoncovyBod)
            throw 3;
    }

    catch (int Error)
    {
        switch(Error)
        {
            case 2:
                cerr << "Chyba - pocet rezu musi byt nenulovy ..." << endl;
                exit(1);
            case 3:
                DanyPocetRezu = 1;
                cerr << "Zadali jste stejny pocatecni a koncovy bod ... " << endl
                     << " Menim pocet rezu na: " << DanyPocetRezu << endl;
                break;
            default:
                break;
        }
    }
}

void Intersection::VypisSekvenciRezu(Mesh& mesh)
{
    for(int i = 0; i < Rez.size(); i++)
    {
        cout << "Bod: " << i + 1 << endl;
        for(int j = 0; j < mesh.MeshVypisPocetPromennych(); j++)
            cout << Rez.at(i).PointVypisHodnotuPromenne(j) << endl;
    }
}

void Intersection::VypisSekvenciRezuDlePromenne(Mesh& mesh, string Promenna)
{
    for(int i = 0; i < Rez.size(); i++)
    {
        cout << "Bod: " << i + 1 << endl;
        cout << "Promenna: " << Promenna << " je: " << Rez.at(i).PointVypisHodnotuPromenne(mesh.MeshPrevedNazevNaHodnotuPromenne(Promenna)) << endl;
    }
}


bool Intersection::JsouSiDoubleRovny(double PrvniCislo, double DruheCislo)
{
    double Epsilon = 1e-13;
    if(abs(PrvniCislo - DruheCislo) < Epsilon)
        return true;
}

bool Intersection::JsouBodyStejne(Point& BodJedna, Point& BodDva)
{
    for(int i = 0; i < BodJedna.PointVypisVelikostVektoru(); i++)
        if( not(JsouSiDoubleRovny(BodJedna.PointVypisHodnotuPromenne(i), BodDva.PointVypisHodnotuPromenne(i))))
            return false;

    return true;
}

void Intersection::VymenHodnotyBoduRezu(Mesh& mesh, int PrvniIndex, int DruhyIndex)
{
        Point Nosic = mesh.MeshPrepisPromenneZBoduDoBodu(Rez.at(PrvniIndex));
        Rez.at(PrvniIndex) = mesh.MeshPrepisPromenneZBoduDoBodu(Rez.at(DruhyIndex));
        Rez.at(DruhyIndex) = mesh.MeshPrepisPromenneZBoduDoBodu(Nosic);
}

void Intersection::SetridRezQuicksortemPodlePromenne(Mesh& mesh, string Promenna, int PocatecniIndex, int KoncovyIndex)
{
    int boundary = 0;

	if (PocatecniIndex < KoncovyIndex)
	{
		boundary = PocatecniIndex;
		for(int i = PocatecniIndex + 1; i <= KoncovyIndex; i++)
            if(Rez.at(i).PointVypisHodnotuPromenne(mesh.MeshPrevedNazevNaHodnotuPromenne(Promenna)) < Rez.at(PocatecniIndex).PointVypisHodnotuPromenne(mesh.MeshPrevedNazevNaHodnotuPromenne(Promenna)))
                VymenHodnotyBoduRezu(mesh, i, ++boundary);

        VymenHodnotyBoduRezu(mesh, PocatecniIndex, boundary);
        SetridRezQuicksortemPodlePromenne(mesh, Promenna, PocatecniIndex, boundary);
        SetridRezQuicksortemPodlePromenne(mesh, Promenna, ++boundary, KoncovyIndex);
	}
}

void Intersection::VlozBodRezuNaPozici(int IndexPozice, Point& VkladanyBod)
{
    Rez.at(IndexPozice) = VkladanyBod;
}

vector<Point> Intersection::EliminujDublovaneHodnotyRezu()
{
    vector<Point> VyeliminovanyRez;

    VyeliminovanyRez.push_back(Rez.at(0));

    for(int i = 0; i < (Rez.size()/2); i++)
        VyeliminovanyRez.push_back(Rez.at(2 * i + 1));

    return VyeliminovanyRez;
}

void Intersection::UlozBodyRezuProGnuplot(Mesh& mesh, string Filename)
{
    ofstream file(Filename.c_str());

    file << "#Vystup pro visualizaci programem Gnuplot" << endl;

    file << "#Promenne: ";
        for(int i = 0; i < mesh.MeshVypisPocetPromennych(); i++)
            file << mesh.MeshVypisNazevPromenne(i) << "\t";
    file << endl;

    for(int i = 0; i < Rez.size(); i++)
    {
        for(int j = 0; j < mesh.MeshVypisPocetPromennych(); j++)
            file << Rez.at(i).PointVypisHodnotuPromenne(j) << "\t";
        file << endl;
    }

    file.close();
}

double Intersection::NajdiZadanyBodRezu(string Vstup)
{
    string DeliciZnak = "=";
    double ZadanyBodRezu;

    size_t PoziceDelicihoZnaku = 0;

    PoziceDelicihoZnaku = Vstup.find(DeliciZnak);
    Vstup = Vstup.erase(0, PoziceDelicihoZnaku + DeliciZnak.length());
    if( ZadanyBodRezu = stod(Vstup) )
    {
        cout << "Zadany bod rezu je: " << ZadanyBodRezu << endl;
        return ZadanyBodRezu;
    }
    else
    {
        cout << "Chyba pri nacitani bodu rezu ... (neprovedeny parsing)" << endl;
        exit(1);
    }
}

string Intersection::NajdiZadanouPromennouRezu(Mesh& mesh, string Vstup)
{
    string DeliciZnak = "=";

    size_t PoziceDelicihoZnaku = 0;

    PoziceDelicihoZnaku = Vstup.find(DeliciZnak);
    Vstup = Vstup.erase(PoziceDelicihoZnaku, Vstup.length());
    try
    {
        for(int i = 0; i < mesh.MeshVypisPocetPromennych(); i++)
            if(Vstup.compare(mesh.MeshVypisNazevPromenne(i)) == 0)
            {
                cout << "Zadana promenna rezu je: " << Vstup << endl;
                return Vstup;
            }
        throw -1;
    }

    catch (int Error)
    {
        cerr << "Nenalezena schoda s nactenymi promennymi ... fatal error" << Error << " (Nacteni promenne rezu ze vstupu.)" << endl;
        exit(1);
    }
}

string Intersection::NajdiPromennouVRezu(Mesh& mesh, string ZadanaPromennaRezu)
{
    string PromennaJedna = "X";
    string PromennaDva = "Y";
    string PromennaVRezu;

    try
    {
    if(ZadanaPromennaRezu.compare(PromennaJedna) == 0)
    {
        PromennaVRezu = "Y";
        cout << "Rez je vertikalni ---> Promena v Rezu je: " << PromennaVRezu << endl;
        return PromennaVRezu;
    }
    else if(ZadanaPromennaRezu.compare(PromennaDva) == 0)
    {
        PromennaVRezu = "X";
        cout << "Rez je horizontalni ---> Promenna v Rezu je: " << PromennaVRezu << endl;
        return PromennaVRezu;
    }
    else throw -1;
    }

    catch (int Error)
    {
        cerr << "NajdiPromennouVRezu: Error: " << Error << "Nenalezena schoda se Zadanou Promennou Rezu ... fatal error" << endl;
        exit(1);
    }
}

void Intersection::ProvedRez(int argc, char* argv[], Mesh& mesh)
{
    double BodRezu = NajdiZadanyBodRezu(argv[2]);
    string ZadanaPromennaRezu = NajdiZadanouPromennouRezu(mesh, argv[2]);
    string PromennaVRezu = NajdiPromennouVRezu(mesh, ZadanaPromennaRezu);

    double Theta = 0.0;
    for(int IndexElementu = 0; IndexElementu < mesh.MeshVypisPocetElementu() - 1; IndexElementu++)
    {
        Theta = VypocitejThetu(BodRezu, IndexElementu, "A", "B", ZadanaPromennaRezu, mesh);
        if(IsInRange(0.0, 1.0, Theta))
        {
            Rez.push_back(VypocitejBodRezu(IndexElementu, Theta, "A", "B", mesh));
            //cout << "Poradi pridaneho bodu je:" << Rez.size() << endl;
        }

        Theta = VypocitejThetu(BodRezu, IndexElementu, "B", "C", ZadanaPromennaRezu, mesh);
        if(IsInRange(0.0, 1.0, Theta))
        {
            Rez.push_back(VypocitejBodRezu(IndexElementu, Theta, "B", "C", mesh));
            //cout << "Poradi pridaneho bodu je:" << Rez.size() << endl;
        }

        Theta = VypocitejThetu(BodRezu, IndexElementu, "C", "A", ZadanaPromennaRezu, mesh);
        if(IsInRange(0.0, 1.0, Theta))
        {
            Rez.push_back(VypocitejBodRezu(IndexElementu, Theta, "C", "A", mesh));
            //cout << "Poradi pridaneho bodu je:" << Rez.size() << endl;
        }
    }

    SetridRezQuicksortemPodlePromenne(mesh, PromennaVRezu, 0, Rez.size() - 1);
    Rez = EliminujDublovaneHodnotyRezu();

    UlozBodyRezuProGnuplot(mesh, argv[3]);
}
