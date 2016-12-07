// horizontal.c -- See horizontal.h for copyright and more info

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "horizontal.h"

//declare functions
//**********************************************
//Horizontal Allocate
//**********************************************
void Horizontal_Allocate(horizontal *Horizontal)
{
  Horizontal->X = (double *)calloc(Horizontal->N_elements, sizeof(double));
  Horizontal->Y = (double *)calloc(Horizontal->N_elements, sizeof(double));
  Horizontal->Theta = (double *)calloc(Horizontal->N_elements, sizeof(double));
  Horizontal->Fun = (double *)calloc(Horizontal->N_elements * Horizontal->N_functions, sizeof(double));
  return;
}

//*********************************************************************************************************************************************
//Horizontal Triangle
//*********************************************************************************************************************************************
void Horizontal_Triangle(horizontal *Horizontal, triangle_store *Triangle_store, functions_store *Functions_store, int idx_A, int idx_B)
{
  int i;

  Horizontal->Theta[Horizontal->N_val] = (Horizontal->Hor - Triangle_store->Y[idx_A]) / (Triangle_store->Y[idx_B] - Triangle_store->Y[idx_A]);
  if (0.0 <= Horizontal->Theta[Horizontal->N_val] && Horizontal->Theta[Horizontal->N_val] <= 1.0)
  {
    Horizontal->X[Horizontal->N_val] = Horizontal->Theta[Horizontal->N_val] * Triangle_store->X[idx_B] + (1 - Horizontal->Theta[Horizontal->N_val]) * Triangle_store->X[idx_A];
    Horizontal->Y[Horizontal->N_val] = Horizontal->Hor;
    
    for(i = 0; i < Horizontal->N_functions; i++)
      Horizontal->Fun[Horizontal->N_val + i * Horizontal->N_elements] = Horizontal->Theta[Horizontal->N_val] * Functions_store->Node_values[idx_B + 3 * i] + (1 - Horizontal->Theta[Horizontal->N_val]) * Functions_store->Node_values[idx_A + 3 * i];
    Horizontal->N_val++;
  }
  return;
}

//***************************************************************************************************************************************************
//Horizontal Quadrangle
//***************************************************************************************************************************************************
static void Horizontal_Quadrangle(horizontal *Horizontal, quadrangle_store *Quadrangle_store, functions_store *Functions_store, int idx_A, int idx_B)
{
  int i;

  Horizontal->Theta[Horizontal->N_val] = (Horizontal->Hor - Quadrangle_store->Y[idx_A]) / (Quadrangle_store->Y[idx_B] - Quadrangle_store->Y[idx_A]);
  if((0.0 <= Horizontal->Theta[Horizontal->N_val]) && (Horizontal->Theta[Horizontal->N_val] <= 1.0))
  {
    Horizontal->Y[Horizontal->N_val] = Horizontal->Hor;
    Horizontal->X[Horizontal->N_val] = Horizontal->Theta[Horizontal->N_val] * Quadrangle_store->X[idx_B] + (1 - Horizontal->Theta[Horizontal->N_val]) * Quadrangle_store->X[idx_A];

    for(i = 0; i < Horizontal->N_functions; i++)
      Horizontal->Fun[Horizontal->N_val + i * Horizontal->N_elements] = Horizontal->Theta[Horizontal->N_val] * Functions_store->Node_values[idx_B + 4 * i] + (1 - Horizontal->Theta[Horizontal->N_val]) * Functions_store->Node_values[idx_A + 4 * i];
    Horizontal->N_val++;
  }
  return;
}

//*******************************************************
//Horizontal Reallocate
//*******************************************************
static void Horizontal_Reallocate(horizontal *Horizontal)
{
  int i, j;

  Horizontal->X = (double *)realloc(Horizontal->X, Horizontal->N_val * sizeof(double));
  Horizontal->Y = (double *)realloc(Horizontal->Y, Horizontal->N_val * sizeof(double));
  Horizontal->Theta = (double *)realloc(Horizontal->Theta, Horizontal->N_val * sizeof(double));

  for(j = 1; j < Horizontal->N_functions; j++)
    for(i = 0; i < Horizontal->N_val; i++)
      Horizontal->Fun[i + j * Horizontal->N_val] = Horizontal->Fun[i + j * Horizontal->N_elements];
  Horizontal->Fun = (double *)realloc(Horizontal->Fun, Horizontal->N_val * Horizontal->N_functions * sizeof(double));
  
  Horizontal->N_elements = Horizontal->N_val;
  return;
}

//*****************************************************
//Horizontal Cut
//*****************************************************
void Horizontal_Cut(mesh *Mesh, horizontal *Horizontal)
{
  int i;
  triangle_store Triangle_store;
  quadrangle_store Quadrangle_store;
  functions_store Functions_store;

  Functions_Store_Allocate(&Mesh->Functions, &Functions_store);
  Horizontal->N_val = 0;
  for(i = 0; i < Mesh->Triangle_element.N_triangles; i++)
  {
    Triangle_Store(&Mesh->Points, &Mesh->Triangle_element, &Triangle_store, i);
    Functions_Triangle_Store(&Mesh->Points, &Mesh->Triangle_element, &Mesh->Functions, &Functions_store, i);
    Horizontal_Triangle(Horizontal, &Triangle_store, &Functions_store, 0, 1);
    Horizontal_Triangle(Horizontal, &Triangle_store, &Functions_store, 1, 2);
    Horizontal_Triangle(Horizontal, &Triangle_store, &Functions_store, 2, 0);
  }

  for(i = 0; i < Mesh->Quadrangle_element.N_quadrangles; i++)
  {
   Quadrangle_Store(&Mesh->Points, &Mesh->Quadrangle_element, &Quadrangle_store, 0, 0, i);
   Functions_Quadrangle_Store(&Mesh->Points, &Mesh->Quadrangle_element, &Mesh->Functions, &Functions_store, i);
   Horizontal_Quadrangle(Horizontal, &Quadrangle_store, &Functions_store, 0, 1);
   Horizontal_Quadrangle(Horizontal, &Quadrangle_store, &Functions_store, 1, 2);
   Horizontal_Quadrangle(Horizontal, &Quadrangle_store, &Functions_store, 2, 3);
   Horizontal_Quadrangle(Horizontal, &Quadrangle_store, &Functions_store, 3, 0);
  } 
  Functions_Store_Deallocate(&Functions_store);
  Horizontal_Reallocate(Horizontal);
  return;
}

//*******************************************************************************
//Horizontal Quicksort Swap
//*******************************************************************************
static void Horizontal_Quicksort_Swap(horizontal *Horizontal, int start, int end)
{
  double k;
  int i;

  //swap
 	k = Horizontal->X[start];
  Horizontal->X[start] = Horizontal->X[end];
  Horizontal->X[end] = k;

  k = Horizontal->Y[start];
  Horizontal->Y[start] = Horizontal->Y[end];
  Horizontal->Y[end] = k;

  for(i = 0; i < Horizontal->N_functions; i++) 
  {
    k = Horizontal->Fun[start + i * Horizontal->N_elements];
    Horizontal->Fun[start + i * Horizontal->N_elements] = Horizontal->Fun[end + i * Horizontal->N_elements];
    Horizontal->Fun[end + i * Horizontal->N_elements] = k;
  }
  return;
}

//*******************************************************************
//Horizontal Quicksort
//*******************************************************************
void Horizontal_Quicksort(horizontal *Horizontal, int start, int end)
{
	int i, boundary;

	if (start < end)
	{
		boundary = start;
		for (i = start + 1; i <= end; i++)
    if (Horizontal->X[i] < Horizontal->X[start])
      Horizontal_Quicksort_Swap(Horizontal, i, ++boundary);

		Horizontal_Quicksort_Swap(Horizontal, start, boundary);
		Horizontal_Quicksort(Horizontal, start, boundary);
		Horizontal_Quicksort(Horizontal, ++boundary, end);
	}
	return;
}

//*******************************************************************************
//Horizontal Rewrite Values
//*******************************************************************************
static void Horizontal_Rewrite_Values(horizontal *Horizontal, int idx1, int idx2)
{
  int i;

  Horizontal->Y[idx2] = Horizontal->Y[idx1];
  Horizontal->X[idx2] = Horizontal->X[idx1];
  for(i = 0; i < Horizontal->N_functions; i++)
    Horizontal->Fun[idx2 + i * Horizontal->N_elements] = Horizontal->Fun[idx1 + i * Horizontal->N_elements];
  return;
}


//********************************************
//Horizontal Unique
//********************************************
void Horizontal_Unique(horizontal *Horizontal)
{
  int i, j = 1;
 
  for(i = 1; i < Horizontal->N_elements; i++)
    if(Utilities_Non_Equalization(Horizontal->X[i], Horizontal->X[j - 1]))
    {
      Horizontal_Rewrite_Values(Horizontal, i, j);
      j++;
    }

  if (j == 1)
    printf("Defined Cut line does not intersect given mesh. Please choose better coordinates of cut line points.\n");
  else
    Horizontal->N_val = j;
    Horizontal_Reallocate(Horizontal);
  return;
}

//*******************************************
//Horizontal Print
//*******************************************
void Horizontal_Print(horizontal *Horizontal)
{
  int i, j;
  for (i = 0; i < Horizontal->N_elements; i++)
  {
    printf("X = %24.16lf Y = %24.16lf ", Horizontal->X[i], Horizontal->Y[i]);
    for(j = 0; j < Horizontal->N_functions; j++)
      printf("Fun%d = %24.16lf ", j + 1, Horizontal->Fun[i + j * Horizontal->N_elements]);
    printf("\n");
  }
  return;
}

//****************************************************************
//Horizontal Save
//****************************************************************
void Horizontal_Save(horizontal *Horizontal, const char *Filename)
{
	//declare stream
	FILE *fid_save;

	//declare variables
	int i, j;

	//openning stream
	fid_save = fopen(Filename, "w");

 printf("N_elements to save = %d\n", Horizontal->N_elements);

	for (i = 0; i < Horizontal->N_elements; i++)
	{
		fprintf(fid_save, "%24.16lf %24.16lf", Horizontal->X[i], Horizontal->Y[i]);
  for(j = 0; j < Horizontal->N_functions; j++)
    fprintf(fid_save, " %24.16lf", Horizontal->Fun[i + j * Horizontal->N_elements]);
  fprintf(fid_save, "\n");
	}

	fclose(fid_save);
	return;
}

//************************************************
//Horizontal Deallocate
//************************************************
void Horizontal_Deallocate(horizontal *Horizontal)
{
  free(Horizontal->X);
  free(Horizontal->Y);
  free(Horizontal->Theta);
  free(Horizontal->Fun);
  return;
}
