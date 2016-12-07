//general.c -- See general.h for Copyright and more info

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "general.h"

//declare functions
//*************************************
//General Allocate
//*************************************
void General_Allocate(general *General)
{
  General->Theta = (double *)calloc(General->N_elements, sizeof(double));
  General->X = (double *)calloc(General->N_elements, sizeof(double));
  General->Y = (double *)calloc(General->N_elements, sizeof(double));
  General->Fun = (double *)calloc(General->N_elements * General->N_functions, sizeof(double));
  return;
}

//******************************************************************************************************
//General Cut Triangle
//******************************************************************************************************
static void General_Cut_Triangle(general *General, triangle_store *Triangle_store, int idx_A, int idx_B)
{
  double A, B;

  if (Utilities_Equalization(Triangle_store->X[idx_A], Triangle_store->X[idx_B]))
  {
    General->XP = Triangle_store->X[idx_A];
    General->YP = General->XP * General->A + General->B;
    General->Theta[General->N_val] = (General->YP - Triangle_store->Y[idx_A]) / (Triangle_store->Y[idx_B] - Triangle_store->Y[idx_A]);
  }
  else if (Utilities_Equalization(Triangle_store->Y[idx_A], Triangle_store->Y[idx_B]))
  {
    General->YP = Triangle_store->Y[idx_A];
    General->XP = (General->YP - General->B) / General->A;
    General->Theta[General->N_val] = (General->XP - Triangle_store->X[idx_A]) / (Triangle_store->X[idx_B] - Triangle_store->X[idx_A]);
  }
  else
  {
    A = (Triangle_store->Y[idx_A] - Triangle_store->Y[idx_B]) / (Triangle_store->X[idx_A] - Triangle_store->X[idx_B]);
    B = Triangle_store->Y[idx_B] - A * Triangle_store->X[idx_B];
    if(Utilities_Equalization(A, General->A))
    {
      if(Utilities_Equalization(B, General->B))
      {
        General->XP = Triangle_store->X[idx_A];
        General->YP = Triangle_store->Y[idx_A];
        General->Theta[General->N_val] = 0;
      }
      else
      {
        General->Theta[General->N_val] = -1;
      }
    }
    else 
    {
      General->XP = (B - General->B) / (General->A - A);
      General->YP = General->A * General->XP + General->B;
      General->Theta[General->N_val] = (General->XP - Triangle_store->X[idx_A]) / (Triangle_store->X[idx_B] - Triangle_store->X[idx_A]);
    }
  }
  return;
}

//************************************************************************************************************
//General Cut Quadrangle
//************************************************************************************************************
static void General_Cut_Quadrangle(general *General, quadrangle_store *Quadrangle_store, int idx_A, int idx_B)
{
  double A, B;

  if (Utilities_Equalization(Quadrangle_store->X[idx_A], Quadrangle_store->X[idx_B]))
  {
    General->XP = Quadrangle_store->X[idx_A];
    General->YP = General->XP * General->A + General->B;
    General->Theta[General->N_val] = (General->YP - Quadrangle_store->Y[idx_A]) / (Quadrangle_store->Y[idx_B] - Quadrangle_store->Y[idx_A]);
  }
  else if (Utilities_Equalization(Quadrangle_store->Y[idx_A], Quadrangle_store->Y[idx_B]))
  {
    General->YP = Quadrangle_store->Y[idx_A];
    General->XP = (General->YP - General->B) / General->A;
    General->Theta[General->N_val] = (General->XP - Quadrangle_store->X[idx_A]) / (Quadrangle_store->X[idx_B] - Quadrangle_store->X[idx_A]);
  }
  else
  {
    A = (Quadrangle_store->Y[idx_A] - Quadrangle_store->Y[idx_B]) / (Quadrangle_store->X[idx_A] - Quadrangle_store->X[idx_B]);
    B = Quadrangle_store->Y[idx_B] - A * Quadrangle_store->X[idx_B];
    if(Utilities_Equalization(A, General->A))
    {
      if(Utilities_Equalization(B, General->B))
      {
        General->XP = Quadrangle_store->X[idx_A];
        General->YP = Quadrangle_store->Y[idx_A];
        General->Theta[General->N_val] = 0;
      }
      else
      {
        General->Theta[General->N_val] = -1;
      }
    }
    else 
    {
      General->XP = (B - General->B) / (General->A - A);
      General->YP = General->A * General->XP + General->B;
      General->Theta[General->N_val] = (General->XP - Quadrangle_store->X[idx_A]) / (Quadrangle_store->X[idx_B] - Quadrangle_store->X[idx_A]);
    }
  }
  return;
}

//****************************************************************************************************
//General Triangle
//****************************************************************************************************
static void General_Triangle(general *General, functions_store *Functions_store, int idx_A, int idx_B)
{
  int i;

  if (0.0 <= General->Theta[General->N_val] && General->Theta[General->N_val] <= 1.0)
  {
    General->X[General->N_val] = General->XP;
    General->Y[General->N_val] = General->YP;
    for(i = 0; i < General->N_functions; i++)
      General->Fun[General->N_val + i * General->N_elements] = General->Theta[General->N_val] * Functions_store->Node_values[idx_B + 3 * i] + (1 - General->Theta[General->N_val]) * Functions_store->Node_values[idx_A + 3 * i];
    General->N_val++;
  }
  return;
}

//******************************************************************************************************
//General Quadrangle
//******************************************************************************************************
static void General_Quadrangle(general *General, functions_store *Functions_store, int idx_A, int idx_B)
{
  int i;

  if (0.0 <= General->Theta[General->N_val] && General->Theta[General->N_val] <= 1.0)
  {
    General->X[General->N_val] = General->XP;
    General->Y[General->N_val] = General->YP;
    for(i = 0; i < General->N_functions; i++)
      General->Fun[General->N_val + i * General->N_elements] = General->Theta[General->N_val] * Functions_store->Node_values[idx_B + 4 * i] + (1 - General->Theta[General->N_val]) * Functions_store->Node_values[idx_A + 4 * i];
    General->N_val++;
  }
  return;
}

//**********************************************
//General Reallocate
//**********************************************
static void General_Reallocate(general *General)
{
  int i, j;

  General->X = (double *)realloc(General->X, General->N_val * sizeof(double));
  General->Y = (double *)realloc(General->Y, General->N_val * sizeof(double));
  General->Theta = (double *)realloc(General->Theta, General->N_val * sizeof(double));

  for(j = 1; j < General->N_functions; j++)
    for(i = 0; i < General->N_val; i++)
      General->Fun[i + j * General->N_val] = General->Fun[i + j * General->N_elements];
  General->Fun = (double *)realloc(General->Fun, General->N_val * General->N_functions * sizeof(double));
  
  General->N_elements = General->N_val;
  return;
}

//********************************************
//General Cut
//********************************************
void General_Cut(mesh *Mesh, general *General)
{
  int i;
  triangle_store Triangle_store;
  quadrangle_store Quadrangle_store;
  functions_store Functions_store;

  Functions_Store_Allocate(&Mesh->Functions, &Functions_store);
  General->N_val = 0;
  for(i = 0; i < Mesh->Triangle_element.N_triangles; i++)
  {
    Triangle_Store(&Mesh->Points, &Mesh->Triangle_element, &Triangle_store, i);
    Functions_Triangle_Store(&Mesh->Points, &Mesh->Triangle_element, &Mesh->Functions, &Functions_store, i); 
    General_Cut_Triangle(General, &Triangle_store, 0, 1);
    General_Triangle(General, &Functions_store, 0, 1); 
    General_Cut_Triangle(General, &Triangle_store, 1, 2);
    General_Triangle(General, &Functions_store, 1, 2); 
    General_Cut_Triangle(General, &Triangle_store, 2, 0);
    General_Triangle(General, &Functions_store, 2, 0); 
  }

  for(i = 0; i < Mesh->Quadrangle_element.N_quadrangles; i++)
  {
    Quadrangle_Store(&Mesh->Points, &Mesh->Quadrangle_element, &Quadrangle_store, 0, 0, i);
    Functions_Quadrangle_Store(&Mesh->Points, &Mesh->Quadrangle_element, &Mesh->Functions, &Functions_store, i);
    General_Cut_Quadrangle(General, &Quadrangle_store, 0, 1);
    General_Quadrangle(General, &Functions_store, 0, 1); 
    General_Cut_Quadrangle(General, &Quadrangle_store, 1, 2);
    General_Quadrangle(General, &Functions_store, 1, 2); 
    General_Cut_Quadrangle(General, &Quadrangle_store, 2, 3);
    General_Quadrangle(General, &Functions_store, 2, 3); 
    General_Cut_Quadrangle(General, &Quadrangle_store, 3, 0);
    General_Quadrangle(General, &Functions_store, 3, 0); 
  }
  Functions_Store_Deallocate(&Functions_store);
  General_Reallocate(General);
  return;
}

//**********************************************************************
//General Quicksort Swap
//**********************************************************************
static void General_Quicksort_Swap(general *General, int start, int end)
{
  double k;
  int i;

  //swap
 	k = General->X[start];
  General->X[start] = General->X[end];
  General->X[end] = k;

  k = General->Y[start];
  General->Y[start] = General->Y[end];
  General->Y[end] = k;

  for(i = 0; i < General->N_functions; i++) 
  {
    k = General->Fun[start + i * General->N_elements];
    General->Fun[start + i * General->N_elements] = General->Fun[end + i * General->N_elements];
    General->Fun[end + i * General->N_elements] = k;
  }
  return;
}

//**********************************************************
//General Quicksort
//**********************************************************
void General_Quicksort(general *General, int start, int end)
{
	int i = 0, boundary = 0;

	if (start < end)
	{
		boundary = start;
		for (i = start + 1; i <= end; i++)
    if (General->Y[i] < General->Y[start])
      General_Quicksort_Swap(General, i, ++boundary);

		General_Quicksort_Swap(General, start, boundary);
		General_Quicksort(General, start, boundary);
		General_Quicksort(General, ++boundary, end);
	}
	return;
}

//**********************************************************************
//General Rewrite Values
//**********************************************************************
static void General_Rewrite_Values(general *General, int idx1, int idx2)
{
  int i;

  General->Y[idx2] = General->Y[idx1];
  General->X[idx2] = General->X[idx1];
  for(i = 0; i < General->N_functions; i++)
    General->Fun[idx2 + i * General->N_elements] = General->Fun[idx1 + i * General->N_elements];
  return;
}


//***********************************
//General Unique
//***********************************
void General_Unique(general *General)
{
  int i, j = 1;

  for(i = 1; i < General->N_elements; i++)
    if (Utilities_Non_Equalization(General->X[i], General->X[j - 1]) || Utilities_Non_Equalization(General->Y[i], General->Y[j - 1]))
    {
      General_Rewrite_Values(General, i, j);
      j++;
    }

  if (j == 1)
    printf("Defined Cut line does not intersect given mesh. Please choose better coordinates of cut line points.\n");
  else
    General->N_val = j;
    General_Reallocate(General);
  return;
}

//**********************************
//General Print
//**********************************
void General_Print(general *General)
{
  int i, j;
  for (i = 0; i < General->N_elements; i++)
  {
    printf("X = %24.16lf Y = %24.16lf ", General->X[i], General->Y[i]);
    for(j = 0; j < General->N_functions; j++)
      printf("Fun%d = %24.16lf ", j + 1, General->Fun[i + j * General->N_elements]);
    printf("\n");
  }
  return;
}

//*******************************************************
//General Save
//*******************************************************
void General_Save(general *General, const char *Filename)
{
	//declare stream
	FILE *fid_save;

	//declare variables
	int i, j;

	//openning stream
	fid_save = fopen(Filename, "w");

 printf("N_elements to save = %d\n", General->N_elements);

	for (i = 0; i < General->N_elements; i++)
 {
		fprintf(fid_save, "%24.16lf %24.16lf", General->X[i], General->Y[i]);
  for(j = 0; j < General->N_functions; j++)
    fprintf(fid_save, " %24.16lf", General->Fun[i + j * General->N_elements]);
  fprintf(fid_save, "\n");
	}

	fclose(fid_save);
	return;
}

//***************************************
//General Deallocate
//***************************************
void General_Deallocate(general *General)
{
  free(General->Theta);
  free(General->X);
  free(General->Y);
  free(General->Fun);
  return;
}
