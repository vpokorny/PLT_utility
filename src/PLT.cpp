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

vector<string> PLT::PLTNajdiNazvyPromennych(string radek)
{
    vector<string> NalezenePromenne;
    string PocatecniZnak = "\"";
    string KoncovyZnak = "\",";
    int PocetPromenych = 0;

    string token;
    size_t PozicePocatecnihoZnaku = 0, PoziceKoncovehoZnaku = 0;

    while((PozicePocatecnihoZnaku = radek.find(PocatecniZnak)) != string::npos)
    {
        radek = radek.erase(0,PozicePocatecnihoZnaku + PocatecniZnak.length());
        if((PoziceKoncovehoZnaku = radek.find(PocatecniZnak)) != string::npos)
        {
            token = radek.substr(0, PoziceKoncovehoZnaku);
            radek = radek.erase(0, PoziceKoncovehoZnaku + KoncovyZnak.length());
        }
        else
            return NalezenePromenne;
        NalezenePromenne.push_back(token);
    }

    /*
    while((PozicePocatecnihoZnaku = radek.find(PocatecniZnak)) != string::npos && (PoziceKoncovehoZnaku = radek.find(KoncovyZnak)) != string::npos)
    {
        token = radek.substr(0, PoziceKoncovehoZnaku);
        token = token.erase(0, PozicePocatecnihoZnaku + PocatecniZnak.length());
        radek = radek.erase(0, PoziceKoncovehoZnaku + KoncovyZnak.length());
        NalezenePromenne.push_back(token);
    }
    */
    //return NalezenePromenne;
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
        cout << "Chyba pri nacitani poctu bodu ... (konec radku)";
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
    vector<double> Input;

    cout << "Nacitam hodnoty promennych ..." << endl
         << "Pocet promenych v bode je: " << mesh.MeshVypisPocetPromennych() << endl;
    Input.resize(mesh.MeshVypisPocetPromennych());
    for(int i = 0; i < mesh.MeshVypisPocetBodu(); i++)
    {
        for(int j = 0; j < mesh.MeshVypisPocetPromennych(); j++)
            if (!(file >> Input.at(j)))
            {
                cerr << "Chyba pri nacitani hodnot promennych ..." << endl;
                exit(1);
            }

        mesh.MeshVlozHodnotyDoBodu(i, Input);
        //mesh.MeshVypisHodnotyPromennychVBode(i);
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

    //PLTPreskocRadky(file, 1);

    getline(file, radek);
    mesh.MeshVlozNazvyPromennych(PLTNajdiNazvyPromennych(radek));
    mesh.MeshVypisNazvyPromennych();
    //mesh.MeshVlozPocetPromennych(PLTNajdiPocetPromennych(radek));

    getline(file, radek);
    mesh.MeshVlozPocetBodu(PLTNajdiPocetBodu(radek));
    cout << "Pocet bodu site je: " << mesh.MeshVypisPocetBodu() << endl;
    mesh.MeshVlozPocetElementu(PLTNajdiPocetElementu(radek));
    cout << "Pocet elementu site je: " << mesh.MeshVypisPocetElementu() << endl;

    mesh.MeshRealokujPamet();

    PLTVlozBody(file, mesh);
    PLTPreskocRadky(file, 1);
    PLTVlozElementy(file, mesh);

    cout << "Posledni bod je: " << endl;
    mesh.MeshVypisHodnotyPromennychVBode(mesh.MeshVypisPocetBodu() - 1);
    mesh.triangle[mesh.MeshVypisPocetElementu() - 1].TriangleVypisVrcholy();

    //test
    //getline(file, radek);
    //cout << radek << endl;
    //cout <<  x << "\t" <<  y << "\t" <<  u << "\t" << v << "\t" <<  p << "\t" <<  velocity << "\t" <<  vorticity << "\t" <<  k << "\t" << omega << endl;
    file.close();
    return mesh;
}


