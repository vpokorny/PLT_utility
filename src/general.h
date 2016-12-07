/*
 * general.h -- pack of functions for general cut in intersect.c
 * License: Freeware
 * Author: Václav Pokorný
 * Version: 2015-7-15
 * Updates: write to pokorny.vena@gmail.com
 */

#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "mesh.h"
#include "utilities.h"

//declare constants

//declare types
typedef struct General_Intersection_Struct
{
  int N_elements, N_functions, N_val;
  double A, B, XP, YP;
  double *Theta, *X, *Y, *Fun;
}general;

//declare functions
void General_Allocate(general *);

void General_Cut(mesh *, general *);

void General_Quicksort(general *, int, int);

void General_Unique(general *);

void General_Print(general *);

void General_Save(general *, const char *);

void General_Deallocate(general *);
#endif
