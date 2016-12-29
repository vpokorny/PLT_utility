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
#include <string>
#include "../include/VTK.h"

using namespace std;

VTK::VTK()
{
    VerzeSouboru = 0;
}

VTK::~VTK()
{
}

void VTK::PreskocRadky(ifstream& file, const int PocetRadku)
{
    string radek;

    for(int i = 0; i < PocetRadku; i++)
    {
        try
        {
            if(!getline(file,radek)) throw 1;
        }

        catch(int Error)
        {
            cerr << "Jsem na konci souboru -- neni co preskocit ..." << endl;
            exit(1);
        }
    }
}

double VTK::ZjistiVerziSouboruVTK(string Radek)
{
    string DeliciZnak = "Version ";
    size_t PoziceDelicihoZnaku = 0;

    try
    {
        if((PoziceDelicihoZnaku = Radek.find(DeliciZnak)) != string::npos)
        {
            Radek = Radek.erase(0, PoziceDelicihoZnaku + DeliciZnak.length());
            return stod(Radek);
        }
        else throw 1;
    }

    catch (int error)
    {
        cerr << "Chyba pri parsovani Verze vystupniho souboru ... (Nenalezen delici znak '.')" << endl;
        exit(1);
    }
}

void VTK::VypisVerziSouboruVTK()
{
    cout << "Verze VTK souboru: " << VerzeSouboru << endl;
}

string VTK::ZjistiTypUlozenychDat(string Radek)
{
    try
    {
        if(Radek.compare("ASCII") == 0)
            return Radek;
        else if(Radek.compare( "BINARY") == 0)
            throw 1;
        else
            throw 2;
    }
    catch (int Error)
    {
        switch(Error)
        {
            case 1:
                cerr << "Chyba vstupniho souboru -> Neumim zpracovat binarni soubor .vtk ..." << endl;
                exit(1);
            case 2:
                cerr << "Chyba vstupniho souboru -> Neidentifikovany typ dat vstupniho souboru .vtk ..." << endl;
                exit(2);
            default:
                break;
        }
    }
}

void VTK::VypisTypUlozenychDat()
{
    cout << "Typ dat: " << TypUlozenychDat << endl;
}

int VTK::ZjistiPocetBodu(string Radek)
{
    string DeliciZnak = "POINTS ";
    string KoncovyZnak = " ";

    size_t PoziceDelicihoZnaku = 0, PoziceKoncovehoZnaku = 0;

    try
    {
        if((PoziceDelicihoZnaku = Radek.find(DeliciZnak)) != string::npos)
        {
            Radek = Radek.erase(0, PoziceDelicihoZnaku + DeliciZnak.length());
            if((PoziceKoncovehoZnaku = Radek.find(KoncovyZnak)) != string::npos)
            {
                Radek = Radek.substr(0, PoziceKoncovehoZnaku);
                return stoi(Radek);
            }
            else throw 2;
        }
        else throw 1;
    }

    catch (int error)
    {
        cerr << "Chyba vstupniho souboru -> Nepodarilo se nacist pocet bodu ..." << endl;
        exit(1);
    }
}

void VTK::VlozSouradniceBodu(ifstream& file, Mesh& mesh)
{
    cout << "Nacitam souradnice bodu ..." << endl;

    mesh.MeshVlozPocetPromennych(2);
    mesh.MeshVlozNazevPromene("X");
    mesh.MeshVlozNazevPromene("Y");

    double Input;

    for(int i = 0; i < mesh.MeshVypisPocetBodu(); i++)
    {
        for(int j = 0; j < mesh.MeshVypisPocetPromennych(); j++)
        {
            try
            {
                if (!(file >> Input))
                    throw 1;
                else
                    mesh.MeshVlozHodnotuDoBodu(i, Input);
            }

            catch (int Error)
            {
                if (Error == 1)
                {
                    cerr << "Chyba vstupniho souboru -> Nelze nacist souradnice bodu ..." << endl;
                    exit(1);
                }
            }
        }
        //Vynechani Z-ove souradnice
        file >> Input;
    }

    cout << "Hotovo ..." << endl;
}

int VTK::ZjistiPocetElementu(string Radek)
{
    string DeliciZnak = "CELLS ";
    string KoncovyZnak = " ";

    size_t PoziceDelicihoZnaku = 0, PoziceKoncovehoZnaku = 0;

    try
    {
        if ((PoziceDelicihoZnaku = Radek.find(DeliciZnak)) != string::npos)
        {
            Radek = Radek.erase(0, PoziceDelicihoZnaku + DeliciZnak.length());
            if ((PoziceKoncovehoZnaku = Radek.find(KoncovyZnak)) != string::npos)
            {
                Radek = Radek.substr(0, PoziceKoncovehoZnaku);
                return stoi(Radek);
            }
            else
                throw 1;
        }
        else
            throw 2;
    }

    catch (int Error)
    {
        switch(Error)
        {
            case 1:
                cerr << "Chyba vstupniho souboru -> Nenalezen pocet elementu, error :" << Error << endl;
                exit(1);
            case 2:
                cerr << "Chyba vstupniho souboru -> Nenalezen pocet elementu, error :" << Error << endl;
                exit(1);
            default:
                break;
        }
    }
}

void VTK::VlozVrcholyTriangle(ifstream& file, Mesh& mesh)
{
    cout << "Nacitam indexy vrcholu trojuhelniku ..." << endl;
    const int Triangle = 3;
    int Input;
    vector<int> IndexyVrcholu;
    IndexyVrcholu.resize(Triangle);

    for(int i = 0; i < mesh.MeshVypisPocetElementu(); i++)
    {
        try
        {
            file >> Input;
            if (Input == Triangle)
            {
                for(int j = 0; j < Triangle; j++)
                    file >> IndexyVrcholu.at(j);
                mesh.MeshVlozHodnotyDoTriangle(i, IndexyVrcholu);
            }
            else throw 1;
        }

        catch (int Error)
        {
            cerr << "Chyba vstupniho souboru -> Nelze nacist indexy vrcholu trojuhelniku ..." << endl;
            exit(1);
        }
    }
    cout << "Hotovo ..." << endl;
}

string VTK::ZjistiNazevPromenne(string Radek)
{
    string DeliciZnak = "SCALARS ";
    string KoncovyZnak = " ";

    size_t PoziceDelicihoZnaku = 0, PoziceKoncovehoZnaku = 0;

    try
    {
        if((PoziceDelicihoZnaku = Radek.find(DeliciZnak)) != string::npos)
        {
            Radek = Radek.erase(0, PoziceDelicihoZnaku + DeliciZnak.length());
            if((PoziceKoncovehoZnaku = Radek.find(KoncovyZnak)) != string::npos)
            {
                Radek = Radek.substr(0, PoziceKoncovehoZnaku);
                cout << "Nazev nove promenne je: " << Radek << endl;
                return Radek;
            }
            else
                throw 2;
        }
        else
            throw 1;
    }

    catch (int Error)
    {
        switch(Error)
        {
            case 1:
                cerr << "Chyba vstupniho souboru -> Nelze nacist nazev promenne v bode - error: " << Error << endl;
                exit(1);
            case 2:
                cerr << "Chyba vstupniho souboru -> Nelze nacist nazev promenne v bode - error: " << Error << endl;
                exit(1);
            default:
                break;
        }
    }
}

void VTK::VlozHodnotyPromennychDoBodu(ifstream& file, Mesh& mesh)
{
    cout << "Nacitam hodnoty promennych do bodu ..." << endl;

    string Radek;
    while(getline(file, Radek))
    {
        mesh.MeshVlozNazevPromene(ZjistiNazevPromenne(Radek));
        PreskocRadky(file, 1);
        try
        {
            double Input;
            for(int i = 0; i < mesh.MeshVypisPocetBodu(); i++)
            {
                if(!(file >> Input))
                    throw 1;
                else
                    mesh.MeshVlozHodnotuDoBodu(i, Input);
            }
            PreskocRadky(file, 1);
        }

        catch (int Error)
        {
            cerr << "Chyba vstupniho souboru -> Nelze nacist hodnoty velicin do bodu ..." << endl;
            exit(1);
        }
    }

    cout << "Hotovo ..." << endl;
}

Mesh VTK::NactiSoubor(string Filename)
{
    cout << "Nacitam soubor " << Filename << endl;

    ifstream file(Filename.c_str());

    Mesh mesh;
    const int TRIANGLE = 5;
    string Radek;

    getline(file, Radek);
    VerzeSouboru = ZjistiVerziSouboruVTK(Radek);
    VypisVerziSouboruVTK();

    PreskocRadky(file, 1);
    getline(file, Radek);
    TypUlozenychDat = ZjistiTypUlozenychDat(Radek);
    VypisTypUlozenychDat();

    PreskocRadky(file, 2);
    getline(file, Radek);
    mesh.MeshVlozPocetBodu(ZjistiPocetBodu(Radek));
    cout << "Pocet bodu je: " << mesh.MeshVypisPocetBodu() << endl;

    mesh.MeshRealokujPametBodu(mesh.MeshVypisPocetBodu());
    VlozSouradniceBodu(file, mesh);

    PreskocRadky(file, 1);
    getline(file, Radek);
    mesh.MeshVlozPocetElementu(ZjistiPocetElementu(Radek));
    cout << "Pocet elementu je: " << mesh.MeshVypisPocetElementu() << endl;

    mesh.MeshRealokujPametElementu(mesh.MeshVypisPocetElementu());
    VlozVrcholyTriangle(file, mesh);

    PreskocRadky(file, mesh.MeshVypisPocetElementu() + 3);
    VlozHodnotyPromennychDoBodu(file, mesh);

    file.close();

    cout << "Hotovo ..." << endl;
    return mesh;
}

void VTK::ExportujDoVTK(Mesh& mesh, string Filename)
{
    cout << "Exportuji do formatu .VTK ..." << endl;

    const int TRIANGLE = 5;
	ofstream file(Filename.c_str());

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
    cout << "Hotovo ..." << endl;
	return;
}
