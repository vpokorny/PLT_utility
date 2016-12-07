/*
  intersect.h --module for mesh.h provides intersection with mesh in constant X position
  License: Freeware
  Author: Václav Pokorný
  Version: 2015-6-5
  Updates: write for it on pokornt.vena@gmail.com
 */

#ifndef _INTERSECT_H_
#define _INTERSECT_H_

//included official headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//icluded own headers
#include "vertical.h"
#include "horizontal.h"
#include "general.h"

//********************
//Constant declaration
//********************

//****************
//Type declaration
//****************
//Intersect storage struct
typedef struct Intersection_struct
	{
   vertical Vertical;
   horizontal Horizontal;
   general General;
/*
   //Declare number of elements
   int N_elements, N_functions, Cut_Type, N_val;

   //Declare characterstics of cut line
   double A, B, XP, YP, Vert, Hor;

   //Declare pointers
   double *theta, *resultX, *resultY, *functions;*U, *V, *P;*/
	} intersect;

//Function prototypes
void Intersect_Cut(mesh *, const char *, double, double, double, double);
//Solve intersect accoding the type of cut line
#endif
