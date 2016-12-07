/*
 * horizontal.h -- pack of functions for intersect.c program
 * License: Freeware
 * Author: Václav Pokorný
 * Version: 2015-7-14
 * Updates: write to pokorny.vena@gmail.com
 */

#ifndef _HORIZONTAL_H_
#define _HORIZONTAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "mesh.h"
#include "utilities.h"
#include "functions.h"

//declare constants

//declare type
typedef struct Horizontal_Intersection_Struct
{
  int N_elements, N_functions, N_val;
  double Hor;
  double *Theta, *X, *Y, *Fun;
}horizontal;

//delcare functions
void Horizontal_Allocate(horizontal *);

void Horizontal_Cut(mesh *, horizontal *);

void Horizontal_Quicksort(horizontal *, int, int);

void Horizontal_Unique(horizontal *);

void Horizontal_Print(horizontal *);

void Horizontal_Save(horizontal *, const char *);

void Horizontal_Deallocate(horizontal *);
#endif
