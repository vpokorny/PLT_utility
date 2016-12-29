/*
 * =====================================================================================
 *
 *       Filename:  PLT.h
 *
 *    Description:  Header file for object PLT.
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

#ifndef _PLT_H_
#define _PLT_H_

#include "mesh.h"

using namespace std;

class PLT {
    private:
        void PLTPreskocRadky(ifstream& file, int PocetRadku);
        vector<string> PLTNajdiNazvyPromennych(string radek);
        int PLTNajdiPocetBodu(string radek);
        int PLTNajdiPocetElementu(string radek);
        void PLTVlozBody(ifstream& file, Mesh& mesh);
        void PLTVlozElementy(ifstream& file, Mesh& mesh);

    public:
        Mesh PLTNactiSoubor(string Filename);
        void PLTExportujDoPLT(Mesh& mesh, string Filename);
};

#endif
