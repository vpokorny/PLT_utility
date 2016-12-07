/*
 * vertical.h -- pack of functions to solve vertical cut in intersect.c
 * License: Freeware
 * Author:Václav Pokorný
 * Version: 2015-7-13
 * Updates: write to pokorny.vena@gmail.com
 */

#ifndef _VERTICAL_H_
#define _VERTICAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "mesh.h"
#include "utilities.h"

//declare constants

//declare types
typedef struct Vertical_Intersection_struct
{
  int N_elements, N_functions, N_val;
  double Vert;
  double *Theta, *X, *Y, *Fun;
}vertical;

//declare functions
void Vertical_Allocate(vertical *);

void Vertical_Cut(mesh *, vertical *);

void Vertical_Quicksort(vertical *, int, int);

void Vertical_Unique(vertical *);

void Vertical_Print(vertical *);

void Vertical_Save(vertical *, const char *);

void Vertical_Deallocate(vertical *);

#endif
