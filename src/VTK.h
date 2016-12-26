/*
 * =====================================================================================
 *
 *       Filename:  VTK.h
 *
 *    Description:  Header file for VTK object.
 *
 *        Version:  1.0
 *        Created:  12/26/2016 01:53:40 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Vaclav Pokorny
 *   Organization:  mat.fs.cvut.cz
 *
 * =====================================================================================
 */

#ifndef _VTK_H_
#define _VTK_H_

#include "mesh.h"
#include "PLT.h"

class VTK
{
    private:

    public:
        VTK();
        ~VTK();
        string VytvorNazevVystupnihoSouboru(string Filename);
        void UlozVTKSoubor(Mesh& mesh, string Filename);
};

#endif
