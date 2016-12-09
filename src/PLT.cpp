/*
 * =====================================================================================
 *
 *       Filename:  PLT.cpp
 *
 *    Description:  
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

#include "PLT.h"

inline void PLT::PLTZkontrolujVstupniParametry(int argc, char* argv[])
{
    cout << "Kontroluji vstupni hodnoty ..." << endl;
    if(argc !=2)
    {
        cerr << "Usage: " << argv[0] << " 'InputFilename'" << endl;
        exit(1);
    }
    cout << " V poradku ..." << endl;
}

inline string PLT::PLTZiskejNazevSouboru(char* argv[])
{
    string inputFilename = argv[1];
    cout << "Nazev vstupniho souboru je: " << inputFilename << endl;
    return inputFilename;
}

void PLT::PLTPreskocRadky(ifstream& file, int PocetRadku)
{
    string radek;

    for(int i = 0; i < PocetRadku; i++)
    {
        if(!getline(file,radek))
        {
            cout << "Jsem na konci souboru -- neni co preskocit ..." << endl;
            exit(1);
        }
    }
}

int PLT::PLTNajdiPocetBodu(string radek)
{
    string PocatecniZnak = "=";
    string KoncovyZnak = ",";
    int PocetBodu = 0;

    size_t PozicePocatecnihoZnaku = 0, PoziceKoncovehoZnaku = 0;

    if((PozicePocatecnihoZnaku = radek.find(PocatecniZnak)) != string::npos && (PoziceKoncovehoZnaku = radek.find(KoncovyZnak)) != string::npos)
    {
        PoziceKoncovehoZnaku = radek.find(KoncovyZnak);
        radek = radek.substr(0, PoziceKoncovehoZnaku);
        PozicePocatecnihoZnaku = radek.find(PocatecniZnak);
        radek = radek.erase(0, PozicePocatecnihoZnaku + PocatecniZnak.length());
        PocetBodu = stoi(radek);
        return PocetBodu;
    }
    else
    {
        cout << "Chyba pri naciatani poctu bodu ... (konec radku)";
        exit(1);
    }
}

int PLT::PLTNajdiPocetElementu(string radek)
{
    string PocatecniZnak = "=";
    string KoncovyZnak = ",";
    int PocetElementu = 0;

    size_t PozicePocatecnihoZnaku = 0, PoziceKoncovehoZnaku = 0;

    PoziceKoncovehoZnaku = radek.find(KoncovyZnak);
    radek = radek.erase(0, PoziceKoncovehoZnaku + KoncovyZnak.length());

    if((PozicePocatecnihoZnaku = radek.find(PocatecniZnak)) != string::npos && (PoziceKoncovehoZnaku = radek.find(KoncovyZnak)) != string::npos)
    {
        PoziceKoncovehoZnaku = radek.find(KoncovyZnak);
        radek = radek.substr(0, PoziceKoncovehoZnaku);
        PozicePocatecnihoZnaku = radek.find(PocatecniZnak);
        radek = radek.erase(0, PozicePocatecnihoZnaku + PocatecniZnak.length());
        //cout << PozicePocatecnihoZnaku << "\t" << PoziceKoncovehoZnaku << endl;
        //cout << radek << endl;
        PocetElementu = stoi(radek);
        return PocetElementu;
    }
    else
    {
        cout << "Chyba pri nacitani poctu elementu ... (konec radku)" << endl;
        exit(1);
    }
}

void PLT::PLTVlozBody(ifstream& file, Mesh& mesh)
{
    const int PocetPromennych = 9;
    vector<double> Input;

    cout << "Nacitam hodnoty promennych ..." << endl;
    Input.resize(PocetPromennych);
    for(int i = 0; i < mesh.MeshVypisPocetBodu(); i++)
    {
        for(int j = 0; j < PocetPromennych; j++)
            if (!(file >> Input.at(j)))
            {
                cerr << "Chyba pri nacitani hodnot promennych ..." << endl;
                exit(1);
            }

        mesh.point[i].PointVlozHodnoty(Input);
        //mesh.point[i].PointVypisHodnoty();
        //cin.get();
    }
    cout << "Hotovo ..." << endl;
}

void PLT::PLTVlozElementy(ifstream& file, Mesh& mesh)
{
    const int PocetVrcholu = 3;
    vector<double> Input;

    cout << "Nacitam vrcholy elementu ..." << endl;
    Input.resize(PocetVrcholu);

    for(int i = 0; i < mesh.MeshVypisPocetElementu(); i++)
    {
        for(int j = 0; j < PocetVrcholu; j++)
            if (!(file >> Input.at(j)))
            {
                cerr << "Chyba pri nacitani vrcholu elementu ..." << endl;
                exit(1);
            }

        mesh.triangle[i].TriangleVlozVrcholy(Input);
        //  mesh.triangle[i].TriangleVypisVrcholy();
        //  cin.get();
    }
    cout << "Hotovo ..." << endl;
}

Mesh PLT::PLTNactiSoubor(int argc, char* argv[])
{
    Mesh mesh;
    string radek;

    PLTZkontrolujVstupniParametry(argc, argv);

    auto filename = PLTZiskejNazevSouboru(argv);
    ifstream file(filename.c_str());

    PLTPreskocRadky(file, 1);
    getline(file, radek);
    mesh.MeshVlozPocetBodu(PLTNajdiPocetBodu(radek));
    mesh.MeshVlozPocetElementu(PLTNajdiPocetElementu(radek));
    mesh.MeshRealokujPamet();

    PLTVlozBody(file, mesh);
    PLTPreskocRadky(file, 1);
    PLTVlozElementy(file, mesh);

    cout << "Posldeni bod je: " << endl;
    mesh.point[mesh.MeshVypisPocetBodu() - 1].PointVypisHodnoty();
    mesh.triangle[mesh.MeshVypisPocetElementu() - 1].TriangleVypisVrcholy();

    //test
    //getline(file, radek);
    //cout << radek << endl;
    //cout <<  x << "\t" <<  y << "\t" <<  u << "\t" << v << "\t" <<  p << "\t" <<  velocity << "\t" <<  vorticity << "\t" <<  k << "\t" << omega << endl;

    file.close();
    return mesh;
}


