/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Program for cutting PLT source files
 *
 *        Version:  1.0
 *        Created:  12/07/2016 10:52:38 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Vaclav Pokorny
 *   Organization:  mat.fs.cvut.cz
 *
 * =====================================================================================
 */

#include "mesh.h"
#include "PLT.h"
#include "intersect.h"

using namespace std;

inline void ZkontrolujVstupniParametry(int argc, char* argv[])
{
    try
    {
        cout << "Kontroluji vstupni hodnoty ..." << endl;
        if(argc != 4)
            throw 1;
    }

    catch (int x)
    {
        cerr << "Error number: " << x << endl
             << "Usage: " << argv[0] << "'InputFilename' " << "'Zadany bod rezu ve formatu napr.: X=0.01234, nebo Y=0.01234 ' " << "'Output Filename' " << endl;
    }

    cout << " Vstupni parametry jsou v poradku ..." << endl;
}

int main (int argc, char* argv[])
{
    ZkontrolujVstupniParametry(argc, argv);

    PLT plt;
    Mesh mesh = plt.PLTNactiSoubor(argv[1]);

    Intersection intersection;
    intersection.ProvedRez(argc, argv, mesh);

    return 0;
}
