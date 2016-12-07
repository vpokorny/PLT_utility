//vertical.c -- See vertical.h for Copyright and more info

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "vertical.h"

//declare functions
//****************************************
//Vertical Allocate
//****************************************
void Vertical_Allocate(vertical *Vertical)
{
  Vertical->Theta = (double *)calloc(Vertical->N_elements, sizeof(double));
  Vertical->X = (double *)calloc(Vertical->N_elements, sizeof(double));
  Vertical->Y = (double *)calloc(Vertical->N_elements, sizeof(double));
  Vertical->Fun = (double *)calloc(Vertical->N_functions * Vertical->N_elements, sizeof(double));
  return;
}

//********************************************************************************************************************************
//Vertical Triangle
//********************************************************************************************************************************
void Vertical_Triangle(vertical *Vertical, triangle_store *Triangle_store, functions_store *Functions_store, int idx_A, int idx_B)
{
  int i;

  Vertical->Theta[Vertical->N_val] = (Vertical->Vert - Triangle_store->X[idx_A]) / (Triangle_store->X[idx_B] - Triangle_store->X[idx_A]);
  if((0.0 <= Vertical->Theta[Vertical->N_val]) && (Vertical->Theta[Vertical->N_val] <= 1.0))
  {
    Vertical->X[Vertical->N_val] = Vertical->Vert;
    Vertical->Y[Vertical->N_val] = Vertical->Theta[Vertical->N_val] * Triangle_store->Y[idx_B] + (1 - Vertical->Theta[Vertical->N_val]) * Triangle_store->Y[idx_A];

    for(i = 0; i < Vertical->N_functions; i++)
      Vertical->Fun[Vertical->N_val + i * Vertical->N_elements] = Vertical->Theta[Vertical->N_val] * Functions_store->Node_values[idx_B + 3 * i] + (1 - Vertical->Theta[Vertical->N_val]) * Functions_store->Node_values[idx_A + 3 * i];
    Vertical->N_val++;
  }
  return;
}

//*************************************************************************************************************************************
//Vertical Quadrangle
//*************************************************************************************************************************************
void Vertical_Quadrangle(vertical *Vertical, quadrangle_store *Quadrangle_store, functions_store *Functions_store, int idx_A, int idx_B)
{
  int i;

  Vertical->Theta[Vertical->N_val] = (Vertical->Vert - Quadrangle_store->X[idx_A]) / (Quadrangle_store->X[idx_B] - Quadrangle_store->X[idx_A]);
  if((0.0 <= Vertical->Theta[Vertical->N_val]) && (Vertical->Theta[Vertical->N_val] <= 1.0))
  {
    Vertical->X[Vertical->N_val] = Vertical->Vert;
    Vertical->Y[Vertical->N_val] = Vertical->Theta[Vertical->N_val] * Quadrangle_store->Y[idx_B] + (1 - Vertical->Theta[Vertical->N_val]) * Quadrangle_store->Y[idx_A];

    for(i = 0; i < Vertical->N_functions; i++)
      Vertical->Fun[Vertical->N_val + i * Vertical->N_elements] = Vertical->Theta[Vertical->N_val] * Functions_store->Node_values[idx_B + 4 * i] + (1 - Vertical->Theta[Vertical->N_val]) * Functions_store->Node_values[idx_A + 4 * i];
    Vertical->N_val++;
  }
  return;
}

//*************************************************
//Vertical Reallocate
//*************************************************
static void Vertical_Reallocate(vertical *Vertical)
{
  int i, j;

  printf("N_elements: %d N_val = %d\n", Vertical->N_elements, Vertical->N_val);
  Vertical->X = (double *)realloc(Vertical->X, Vertical->N_val * sizeof(double));
  Vertical->Y = (double *)realloc(Vertical->Y, Vertical->N_val * sizeof(double));
  Vertical->Theta = (double *)realloc(Vertical->Theta, Vertical->N_val * sizeof(double));

  for(j = 1; j < Vertical->N_functions; j++)
    for(i = 0; i < Vertical->N_val; i++)
      Vertical->Fun[i + j * Vertical->N_val] = Vertical->Fun[i + j * Vertical->N_elements];

  Vertical->Fun = (double *)realloc(Vertical->Fun, Vertical->N_val * Vertical->N_functions * sizeof(double));
  
  Vertical->N_elements = Vertical->N_val;
  Vertical->N_val = 0;
  return;
}

//***********************************************
//Vertical Cut
//***********************************************
void Vertical_Cut(mesh *Mesh, vertical *Vertical)
{
  int i;
  triangle_store Triangle_store;
  quadrangle_store Quadrangle_store;
  functions_store Functions_store;

  Functions_Store_Allocate(&Mesh->Functions, &Functions_store);
  Vertical->N_val = 0;
  for(i = 0; i < Mesh->Triangle_element.N_triangles; i++)
  {
    Triangle_Store(&Mesh->Points, &Mesh->Triangle_element, &Triangle_store, i);
    Functions_Triangle_Store(&Mesh->Points, &Mesh->Triangle_element, &Mesh->Functions, &Functions_store, i); 
    Vertical_Triangle(Vertical, &Triangle_store, &Functions_store, 0, 1); 
    Vertical_Triangle(Vertical, &Triangle_store, &Functions_store, 1, 2); 
    Vertical_Triangle(Vertical, &Triangle_store, &Functions_store, 2, 0); 
  }

  for(i = 0; i < Mesh->Quadrangle_element.N_quadrangles; i++)
  {
    Quadrangle_Store(&Mesh->Points, &Mesh->Quadrangle_element, &Quadrangle_store, 0, 0, i);
    Functions_Quadrangle_Store(&Mesh->Points, &Mesh->Quadrangle_element, &Mesh->Functions, &Functions_store, i);
    Vertical_Quadrangle(Vertical, &Quadrangle_store, &Functions_store, 0, 1);
    Vertical_Quadrangle(Vertical, &Quadrangle_store, &Functions_store, 1, 2);
    Vertical_Quadrangle(Vertical, &Quadrangle_store, &Functions_store, 2, 3);
    Vertical_Quadrangle(Vertical, &Quadrangle_store, &Functions_store, 3, 0);
  }
  Functions_Store_Deallocate(&Functions_store);
  Vertical_Reallocate(Vertical);
  return;
}

//*************************************************************************
//Vertical Quicksort Swap
//*************************************************************************
static void Vertical_Quicksort_Swap(vertical *Vertical, int start, int end)
{
  double k;
  int i;

  //swap
 	k = Vertical->X[start];
  Vertical->X[start] = Vertical->X[end];
  Vertical->X[end] = k;

  k = Vertical->Y[start];
  Vertical->Y[start] = Vertical->Y[end];
  Vertical->Y[end] = k;

  for(i = 0; i < Vertical->N_functions; i++) 
  {
    k = Vertical->Fun[start + i * Vertical->N_elements];
    Vertical->Fun[start + i * Vertical->N_elements] = Vertical->Fun[end + i * Vertical->N_elements];
    Vertical->Fun[end + i * Vertical->N_elements] = k;
  }
  return;
}

//*************************************************************
//Vertical Quicksort
//*************************************************************
void Vertical_Quicksort(vertical *Vertical, int start, int end)
{
	int i, boundary;

	if (start < end)
	{
		boundary = start;
		for (i = start + 1; i <= end; i++)
    if (Vertical->Y[i] < Vertical->Y[start])
      Vertical_Quicksort_Swap(Vertical, i, ++boundary);

		Vertical_Quicksort_Swap(Vertical, start, boundary);
		Vertical_Quicksort(Vertical, start, boundary);
		Vertical_Quicksort(Vertical, ++boundary, end);
	}
	return;
}

//*************************************************************************
//Vertical Rewrite Values
//*************************************************************************
static void Vertical_Rewrite_Values(vertical *Vertical, int idx1, int idx2)
{
  int i;

  Vertical->Y[idx2] = Vertical->Y[idx1];
  Vertical->X[idx2] = Vertical->X[idx1];
  for(i = 0; i < Vertical->N_functions; i++)
    Vertical->Fun[idx2 + i * Vertical->N_elements] = Vertical->Fun[idx1 + i * Vertical->N_elements];
  return;
}

//***********************************************
//Vertical Print Functions
//***********************************************
void Vertical_Print_Functions(vertical *Vertical)
{
  int i;

  for(i = 0; i < Vertical->N_functions * Vertical->N_elements; i++)
    printf("Index: %d Fun: %24.16lf\n", i, Vertical->Fun[i]);
  return;
}

//**************************************
//Vertical Unique
//**************************************
void Vertical_Unique(vertical *Vertical)
{
  int i;

  Vertical->N_val = 1;
  for(i = 1; i < Vertical->N_elements; i++)
    if(Utilities_Non_Equalization(Vertical->Y[i], Vertical->Y[Vertical->N_val - 1]))
    {
      Vertical_Rewrite_Values(Vertical, i, Vertical->N_val);
      Vertical->N_val++;
    }

  if (Vertical->N_val == 1)
    printf("Defined Cut line does not intersect given mesh. Please choose better coordinates of cut line points.\n");
  else
    Vertical_Print_Functions(Vertical);
    Vertical_Reallocate(Vertical);
    Vertical_Print_Functions(Vertical);
  return;
}

//*************************************
//Vertical Print
//*************************************
void Vertical_Print(vertical *Vertical)
{
  int i, j;
  for (i = 0; i < Vertical->N_elements; i++)
  {
    printf("X = %24.16lf Y = %24.16lf ", Vertical->X[i], Vertical->Y[i]);
    for(j = 0; j < Vertical->N_functions; j++)
      printf("Fun%d = %24.16lf ", j + 1, Vertical->Fun[i + j * Vertical->N_elements]);
    printf("\n");
  }
  return;
}

//**********************************************************
//Vertical Save
//**********************************************************
void Vertical_Save(vertical *Vertical, const char *Filename)
{
	//declare stream
	FILE *fid_save;

	//declare variables
	int i, j;

	//openning stream
	fid_save = fopen(Filename, "w");

 printf("N_elements to save = %d\n", Vertical->N_elements);

	for (i = 0; i < Vertical->N_elements; i++)
 {
		fprintf(fid_save, "%24.16lf %24.16lf", Vertical->X[i], Vertical->Y[i]);
  for(j = 0; j < Vertical->N_functions; j++)
    fprintf(fid_save, " %24.16lf", Vertical->Fun[i + j * Vertical->N_elements]);
  fprintf(fid_save, "\n");
	}

	fclose(fid_save);
	return;
}

//******************************************
//Vertical Deallocate
//******************************************
void Vertical_Deallocate(vertical *Vertical)
{
  free(Vertical->Theta);
  free(Vertical->X);
  free(Vertical->Y);
  free(Vertical->Fun);
  return;
}
