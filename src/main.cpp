/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Program for cutting PLT outputs
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
#include "cstdlib"
#include "mesh.h"
#include "PLT.h"

using namespace std;

int main (int argc, char *argv[])
{

    PLT *plt;
    Mesh mesh = plt->PLTNactiSoubor(argc, argv);

    return 0;
}
