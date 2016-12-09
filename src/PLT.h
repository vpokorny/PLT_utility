/*
 * PLT.h -- pack of functions for intersect.c program
 * License: Freeware
 * Author: Václav Pokorný
 * Version: 2015-7-14
 * Updates: write to pokorny.vena@gmail.com
 */

#ifndef _PLT_H_
#define _PLT_H_

#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "mesh.h"

using namespace std;

class PLT {
    private:
        void PLTZkontrolujVstupniParametry(int argc, char* argv[]);
        string PLTZiskejNazevSouboru(char* argv[]);
        void PLTPreskocRadky(ifstream& file, int PocetRadku);
        int PLTNajdiPocetBodu(string radek);
        int PLTNajdiPocetElementu(string radek);
        void PLTVlozBody(ifstream& file, Mesh& mesh);
        void PLTVlozElementy(ifstream& file, Mesh& mesh);

    public:
        Mesh PLTNactiSoubor(int argc, char* argv[]);
};

#endif
