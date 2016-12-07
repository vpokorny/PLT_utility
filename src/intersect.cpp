// intersection.c -- See intersection.h for copyright and info

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

//own header
#include "vertical.h"
#include "horizontal.h"
#include "general.h"
#include "intersect.h"

//************************************************************
//Allocate Intersect Memory
//************************************************************
/*
void Intersect_Allocate(intersect *Intersect)
{
  Intersect->resultX = (double *)calloc(Intersect->N_elements, sizeof(double));
  Intersect->resultY = (double *)calloc(Intersect->N_elements, sizeof(double));
  Intersect->theta = (double *)calloc(Intersect->N_elements, sizeof(double));
  Intersect->functions = (double *)calloc(Intersect->N_elements * Intersect->N_functions, sizeof(double));
  return;
}
*/

//****************************************************************************
//Intersect Quicksort swap
//****************************************************************************
//Function swaps elements when condition in Intersect_Quicksort is fulfilled
/*
static void Intersect_Quicksort_Swap(intersect *Intersect, int start, int end)
{
	//declaration of help variable
	double k;
 int i;

	//swap
	k = Intersect->resultX[start];
	Intersect->resultX[start] = Intersect->resultX[end];
	Intersect->resultX[end] = k;

 k = Intersect->resultY[start];
	Intersect->resultY[start] = Intersect->resultY[end];
	Intersect->resultY[end] = k;

 for(i = 0; i < Intersect->N_fucntions; i++) 
 {
   k = Intersect->functions[start + i * Intersect->N_elements];
   Intersect->functions[start + i * Intersect->N_elements] = Intersect->functions[end + i * Intersect->N_elements];
   Intersect->functions[end + i * Intersect->N_elements] = k;
 }
	return;
}
*/

//***********************************************************************
//Intersect Quicksort
//***********************************************************************
//Function for sorting intersection nodes
/*
static void Intersect_Quicksort(intersect *Intersect, int start, int end)
{
	int i = 0, boundary = 0;

	if (start < end)
	{
		boundary = start;
		for (i = start + 1; i <= end; i++)
		{
    switch(Intersect->Cut_Type)
    {
      case Vertical:
        if (Intersect->resultY[i] < Intersect->resultY[start])
        {
          Intersect_Quicksort_Swap(Intersect, i, ++boundary);
        }
        break;

      case Horizontal:
        if (Intersect->resultX[i] < Intersect->resultX[start])
        {
          Intersect_Quicksort_Swap(Intersect, i, ++boundary);
        }
        break;

      case General:
        if (Intersect->resultY[i] < Intersect->resultY[start])
        {
          Intersect_Quicksort_Swap(Intersect, i, ++boundary);
        }
        break;

      default:
        printf("Unidentificated type of cut!\n");
        exit(0);
        break;
    }
  }
		Intersect_Quicksort_Swap(Intersect, start, boundary);
		Intersect_Quicksort(Intersect, start, boundary);
		Intersect_Quicksort(Intersect, ++boundary, end);
	}
	return;
}
*/

//********************************************************
//Makro for equalization
//********************************************************
//Function for evaluating double numbers (diff 1e-14)
/*
bool Intersect_Makro_Equal(double num_one, double num_two)
{
	bool equal = false;

	if(fabs(num_one - num_two) <= (1e-14))
	{
		equal = true;
	}
	return(equal);
}
*/

//*****************************************************************
//Makro for non equalization
//*****************************************************************
//Function for evaluating difference of double numbers (diff 1e-14)
/*
bool Intersect_Makro_Non_Equal(double num_one, double num_two)
{
	bool equal = false;

	if(fabs(num_one - num_two) > (1e-14))
	{
		equal = true;
	}
	return(equal);
}
*/

//****************************************************************************
//Intersect Rewrite Values
//****************************************************************************
/*
static void Intersect_Rewrite_Values(intersect *Intersect, int idx1, int idx2)
{
  int i;

  Intersect->resultY[idx2] = Intersect->resultY[idx1];
  Intersect->resultX[idx2] = Intersect->resultX[idx1];
  for(i = 0; i < Intersect->N_functions; i++)
  {
    Intersect->Functions[idx2 + i * Intersect->N_elements] = Intersect->Functions[idx1 + 1 * Intersect->N_elements];
  }
  return;
}
*/

//************************************************************
//Intersect elimination of double values
//************************************************************
//Function eliminating double values in sorted intersect nodes
/*
static void Intersect_Eliminate(intersect *Intersect)
{
	int i, j = 1, k;

	for(i = 1; i < Intersect->N_elements; i++)
	{
   switch(Intersect->Cut_Type)
   {
     case Vertical:
       if (Intersect_Makro_Non_Equal(Intersect->resultY[i], Intersect->resultY[j - 1]))
       {
         Intersect_Rewrite_Values(Intersect, i, j);
         j++;
       }
       break;

     case Horizontal:
       if (Intersect_Makro_Non_Equal(Intersect->resultX[i], Intersect->resultX[j - 1]))
       {
         Intersect_Rewrite_Values(Intersect, i, j);
         j++;
       }
       break;

     case General:
       if (Intersect_Makro_Non_Equal(Intersect->resultX[i], Intersect->resultX[j - 1]) || Intersect_Makro_Non_Equal(Intersect->resultY[i], Intersect->resultY[j - 1]))
       {
         Intersect_Rewrite_Values(Intersect, i, j);
         j++;
       }
       break;

     default:
       printf("Unidentificated type of cut!\n");
       exit(0);
       break;
   }
 }

 if (j == 1)
 {
   printf("Defined Cut line does not intersect given mesh. Please choose better coordinates of cut line points.\n");
 }
 else
 {
   Intersect->N_elements = j;
 }
	return;
}
*/

//*************************************************************************************************
//Intersect General Cut
//*************************************************************************************************
//Solve intersection of line and Cut line
/*
static void Intersect_General_Cut(intersect *Intersect, double X1, double Y1, double X2, double Y2)
{
  double A, B;

  if (Intersect_Makro_Equal(X1, X2))
  {
    Intersect->XP = X1;
    Intersect->YP = Intersect->XP * Intersect->A + Intersect->B;
    Intersect->theta[Intersect->N_elements] = (Intersect->YP - Y1) / (Y2 - Y1);
  }
  else if (Intersect_Makro_Equal(Y1, Y2))
  {
    Intersect->YP = Y1;
    Intersect->XP = (Intersect->YP - Intersect->B) / Intersect->A;
    Intersect->theta[Intersect->N_elements] = (Intersect->XP - X1) / (X2 - X1);
  }
  else
  {
    A = (Y1 - Y2) / (X1 - X2);
    B = Y2 - A * X2;
    if(Intersect_Makro_Equal(A, Intersect->A))
    {
      if(Intersect_Makro_Equal(B, Intersect->B))
      {
        Intersect->XP = X1;
        Intersect->YP = Y1;
        Intersect->theta[Intersect->N_elements] = 0;
      }
      else
      {
        Intersect->theta[Intersect->N_elements] = -1;
      }
    }
    else 
    {
      Intersect->XP = (B - Intersect->B) / (Intersect->A - A);
      Intersect->YP = Intersect->A * Intersect->XP + Intersect->B;
      Intersect->theta[Intersect->N_elements] = (Intersect->XP - X1) / (X2 - X1);
    }
  }
  return;
}
*/

//*************************************************************************************************************************************************
//Vertical Intersect Triangle
//*************************************************************************************************************************************************
/*
static void Intersect_Triangle_Vertical(intersect *Intersect, triangle_store *Triangle_store, functions_store *Funstions_store, int idxA, int idxB)
{
  int i;

  Intersect->theta[Intersect->N_Val] = (Intersect->Vert - Triangle_store->Nodes[idxA]) / (Triangle_store->Nodes[idxB] - Triangle_store->Nodes[idxA]);
  if (0.0 <= Intersect->theta[Intersect->N_val] && Intersect->theta[Intersect->N_val] <= 1.0)
  {
    Intersect->resultX[Intersect->N_val] = Intersect->Vert;
    Intersect->resultY[Intersect->N_val] = Intersect->theta[Intersect->N_val] * Triangle_store->Nodes[idxB + 3] + (1 - Intersect->theta[Intersect->N_val]) * Triangle_store->Nodes[idxA + 3];

    for(i = 0; i < Intersect->N_functions; i++)
      Intersect->Functions[Intersect->N_val + i * Intersect->N_elements] = Intersect->theta[Intersect->N_val] * Functions_store->Values[idxB + 4 * i] + (1 - Intersect->theta[Intersect->N_val]) * Functions_store->Values[idxA + 4 * i];
    Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->U_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Tri->U_val_A;
    Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->V_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Tri->V_val_A;
    Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->P_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Tri->P_val_A;
    printf("I:%d\n", Intersect->N_elements);
    printf("Theta = %24.16lf \t ResultX = %24.16lf \t ResultY = %24.16lf \t U = %24.16lf \t V = %24.16lf \t P = %24.16lf \n", Intersect->theta[Intersect->N_elements], Intersect->resultX[Intersect->N_elements], Intersect->resultY[Intersect->N_elements], Intersect->U[Intersect->N_elements], Intersect->V[Intersect->N_elements], Intersect->P[Intersect->N_elements]);
    Intersect->N_val++;
  }
  return;
}
*/

//***************************************************************************************************************************************************
//Horizontal Intersect Triangle
//***************************************************************************************************************************************************
/*
static void Intersect_Triangle_Horizontal(intersect *Intersect, triangle_store *Triangle_store, functions_store *Funstions_store, int idxA, int idxB)
{
  int i;

  Intersect->theta[Intersect->N_Val] = (Intersect->Hor - Triangle_store->Nodes[idxA + 3]) / (Triangle_store->Nodes[idxB + 3] - Triangle_store->Nodes[idxA + 3]);
  if (0.0 <= Intersect->theta[Intersect->N_val] && Intersect->theta[Intersect->N_val] <= 1.0)
  {
    Intersect->resultX[Intersect->N_val] = Intersect->theta[Intersect->N_val] * Triangle_store->Nodes[idxB] + (1 - Intersect->theta[Intersect->N_val]) * Triangle_store->Nodes[idxA];
    Intersect->resultY[Intersect->N_val] = Intersect->Hor;
    
    for(i = 0; i < Intersect->N_functions; i++)
      Intersect->Functions[Intersect->N_val + i * Intersect->N_elements] = Intersect->theta[Intersect->N_val] * Functions_store->Values[idxB + 4 * i] + (1 - Intersect->theta[Intersect->N_val]) * Functions_store->Values[idxA + 4 * i];
    Intersect->N_val++;
  }
  return;
   Intersect->theta[Intersect->N_elements] = (Intersect->Hor - Tri->YA)/(Tri->YB - Tri->YA);
   if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
   {
   Intersect->resultX[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->XB + (1 - Intersect->theta[Intersect->N_elements]) * Tri->XA;
   Intersect->resultY[Intersect->N_elements] = Intersect->Hor;
   Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->U_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Tri->U_val_A;
   Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->V_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Tri->V_val_A;
   Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->P_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Tri->P_val_A;
   printf("I:%d\n", Intersect->N_elements);
   printf("Theta = %24.16lf \t ResultX = %24.16lf \t ResultY = %24.16lf \t U = %24.16lf \t V = %24.16lf \t P = %24.16lf \n", Intersect->theta[Intersect->N_elements], Intersect->resultX[Intersect->N_elements], Intersect->resultY[Intersect->N_elements], Intersect->U[Intersect->N_elements], Intersect->V[Intersect->N_elements], Intersect->P[Intersect->N_elements]);
   Intersect->N_elements++;
   }
}
*/

//****************************************************************************************************************
//General Intersect Triangle
//****************************************************************************************************************
/*
static void Intersect_Triangle_General(intersect *Intersect, functions_store *Functions_store, int idxA, int idxB)
{
  int i;

  if (0.0 <= Intersect->theta[Intersect->N_val] && Intersect->theta[Intersect->N_val] <= 1.0)
  {
    Intersect->resultX[Intersect->N_val] = Intersect->XP;
    Intersect->resultY[Intersect->N_val] = Intersect->YP;
    for(i = 0; i < Intersect->N_functions; i++)
      Intersect->functions[Intersect->N_val + i * Intersect->N_elements] = Intersect->theta[Intersect->N_val] * Functions_store->Values[idxB + 4 * i] + (1 - Intersect->theta[Intersect->N_val]) * Functions_store->Values[idxA + 4 * i];
    Intersect->N_val++;
  }
  return;
}
*/

//************************************************************
//Triangle intersection
//************************************************************
//Function for finding intersection nodes with triangles
/*
static void Intersect_Triangle(intersect *Intersect, triangle_store *Triangle_store, functions_store *Functions_store)
{
	int i;

	for (i = 0; i <= Triangle; i++)
	{
		switch(i)
		{
			case 0:
     switch(Intersect->Cut_Type)
     {
       case Vertical:
         Intersect_Triangle_Vertical(Intersect, Triangle_store, Functions_store, 0, 1);
         break;

       case Horizontal:
         Intersect_Triangle_Horizontal(Intersect, Triangle_store, Functions_store, 0, 1);
         break;
       
       case General:
         Intersect_General_Cut(Intersect, Triangle_store->Nodes[0], Triangle_store->Nodes[3], Triangle_store->Nodes[1], Triangle_store->Nodes[4]);
         Intersect_Triangle_General(Intersect, Functions_store, 0, 1);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->XP;
           Intersect->resultY[Intersect->N_elements] = Intersect->YP;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->U_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Tri->U_val_A;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->V_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Tri->V_val_A;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->P_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Tri->P_val_A;
           //printf("I:%d\n", Intersect->N_elements);
           //printf("Theta = %24.16lf \t ResultX = %24.16lf \t ResultY = %24.16lf \t U = %24.16lf \t V = %24.16lf \t P = %24.16lf \n", Intersect->theta[Intersect->N_elements], Intersect->resultX[Intersect->N_elements], Intersect->resultY[Intersect->N_elements], Intersect->U[Intersect->N_elements], Intersect->V[Intersect->N_elements], Intersect->P[Intersect->N_elements]);
           Intersect->N_elements++;
         }
         break;

       default:
         printf("Unidentificated type of cut!\n");
         exit(0);
         break;
     }    
			break;

   case 1:
     switch(Intersect->Cut_Type)
     {
       case Vertical:
         Intersect_Triangle_Vertical(Intersect, Triangle_store, Functions_store, 1, 2);
         Intersect->theta[Intersect->N_elements] = (Intersect->Vert - Tri->XB)/(Tri->XC - Tri->XB);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->Vert;
           Intersect->resultY[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->YC + (1 - Intersect->theta[Intersect->N_elements]) * Tri->YB;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->U_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Tri->U_val_B;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->V_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Tri->V_val_B;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->P_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Tri->P_val_B;
           //printf("I:%d\n", Intersect->N_elements);
           //printf("Theta = %24.16lf \t ResultX = %24.16lf \t ResultY = %24.16lf \t U = %24.16lf \t V = %24.16lf \t P = %24.16lf \n", Intersect->theta[Intersect->N_elements], Intersect->resultX[Intersect->N_elements], Intersect->resultY[Intersect->N_elements], Intersect->U[Intersect->N_elements], Intersect->V[Intersect->N_elements], Intersect->P[Intersect->N_elements]);
           Intersect->N_elements++;
         }
         break;

       case Horizontal:
         Intersect_Triangle_Horizontal(Intersect, Triangle_store, Functions_store, 1, 2);
         Intersect->theta[Intersect->N_elements] = (Intersect->Hor - Tri->YB)/(Tri->YC - Tri->YB);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           
           Intersect->resultX[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->XC + (1 - Intersect->theta[Intersect->N_elements]) * Tri->XB;
           Intersect->resultY[Intersect->N_elements] = Intersect->Hor;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->U_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Tri->U_val_B;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->V_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Tri->V_val_B;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->P_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Tri->P_val_B;
           //printf("I:%d\n", Intersect->N_elements);
           //printf("Theta = %24.16lf \t ResultX = %24.16lf \t ResultY = %24.16lf \t U = %24.16lf \t V = %24.16lf \t P = %24.16lf \n", Intersect->theta[Intersect->N_elements], Intersect->resultX[Intersect->N_elements], Intersect->resultY[Intersect->N_elements], Intersect->U[Intersect->N_elements], Intersect->V[Intersect->N_elements], Intersect->P[Intersect->N_elements]);
           Intersect->N_elements++;
         }
         break;

       case General:
         Intersect_General_Cut(Intersect, Tri->XB, Tri->YB, Tri->XC, Tri->YC);
         Intersect_Triangle_General(Intersect, Functions_store, 1, 2);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->XP;
           Intersect->resultY[Intersect->N_elements] = Intersect->YP;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->U_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Tri->U_val_B;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->V_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Tri->V_val_B;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->P_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Tri->P_val_B;
           //printf("I:%d\n", Intersect->N_elements);
           //printf("Theta = %24.16lf \t ResultX = %24.16lf \t ResultY = %24.16lf \t U = %24.16lf \t V = %24.16lf \t P = %24.16lf \n", Intersect->theta[Intersect->N_elements], Intersect->resultX[Intersect->N_elements], Intersect->resultY[Intersect->N_elements], Intersect->U[Intersect->N_elements], Intersect->V[Intersect->N_elements], Intersect->P[Intersect->N_elements]);
           Intersect->N_elements++;
         }
         break;

       default:
         printf("Unidentificated type of cut!\n");
         exit(0);
         break;
     }
     break;

			case 2:
     switch(Intersect->Cut_Type)
     {
       case Vertical:
         Intersect_Triangle_Vertical(Intersect, Triangle_store, Functions_store, 2, 0);
         Intersect->theta[Intersect->N_elements] = (Intersect->Vert - Tri->XC)/(Tri->XA - Tri->XC);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->Vert;
           Intersect->resultY[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->YA + (1 - Intersect->theta[Intersect->N_elements]) * Tri->YC;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->U_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Tri->U_val_C;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->V_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Tri->V_val_C;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->P_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Tri->P_val_C;
           //printf("I:%d\n", Intersect->N_elements);
           //printf("Theta = %24.16lf \t ResultX = %24.16lf \t ResultY = %24.16lf \t U = %24.16lf \t V = %24.16lf \t P = %24.16lf \n", Intersect->theta[Intersect->N_elements], Intersect->resultX[Intersect->N_elements], Intersect->resultY[Intersect->N_elements], Intersect->U[Intersect->N_elements], Intersect->V[Intersect->N_elements], Intersect->P[Intersect->N_elements]);
           Intersect->N_elements++;
         }
         break;

       case Horizontal:
         Intersect_Triangle_Horizontal(Intersect, Triangle_store, Functions_store, 2, 0);
         Intersect->theta[Intersect->N_elements] = (Intersect->Hor - Tri->YC)/(Tri->YA - Tri->YC);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->XA + (1 - Intersect->theta[Intersect->N_elements]) * Tri->XC;
           Intersect->resultY[Intersect->N_elements] = Intersect->Hor;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->U_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Tri->U_val_C;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->V_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Tri->V_val_C;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->P_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Tri->P_val_C;
           //printf("I:%d\n", Intersect->N_elements);
           //printf("Theta = %24.16lf \t ResultX = %24.16lf \t ResultY = %24.16lf \t U = %24.16lf \t V = %24.16lf \t P = %24.16lf \n", Intersect->theta[Intersect->N_elements], Intersect->resultX[Intersect->N_elements], Intersect->resultY[Intersect->N_elements], Intersect->U[Intersect->N_elements], Intersect->V[Intersect->N_elements], Intersect->P[Intersect->N_elements]);
           Intersect->N_elements++;
         }
         break;

       case General:
         Intersect_General_Cut(Intersect, Tri->XC, Tri->YC, Tri->XA, Tri->YA);
         Intersect_Triangle_General(Intersect, Functions_store, 2, 0);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->XP;
           Intersect->resultY[Intersect->N_elements] = Intersect->YP;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->U_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Tri->U_val_C;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->V_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Tri->V_val_C;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Tri->P_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Tri->P_val_C;
           //printf("I:%d\n", Intersect->N_elements);
           //printf("Theta = %24.16lf \t ResultX = %24.16lf \t ResultY = %24.16lf \t U = %24.16lf \t V = %24.16lf \t P = %24.16lf \n", Intersect->theta[Intersect->N_elements], Intersect->resultX[Intersect->N_elements], Intersect->resultY[Intersect->N_elements], Intersect->U[Intersect->N_elements], Intersect->V[Intersect->N_elements], Intersect->P[Intersect->N_elements]);
           Intersect->N_elements++;
         }
         break;

       default:
         printf("Unidentificated type of cut!\n");
         exit(0);
         break;
     }
     break;

   default:
     break;
  }
 }
	return;
}
*/

//****************************************************************
//Quadrangle intersection
//****************************************************************
//Function for finding intersect nodes with quadrangles
/*
static void Intersect_Quadrangle(intersect *Intersect, quad *Quad)
{
	int j = 0;

	for (j = 0; j <= Quadrangle; j++)
	{
		switch(j)
		{
			case 0:
     switch(Intersect->Cut_Type)
     {
       case Vertical:
         Intersect->theta[Intersect->N_elements] = (Intersect->Vert - Quad->XA)/(Quad->XB - Quad->XA);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->Vert;
           Intersect->resultY[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->YB + (1 - Intersect->theta[Intersect->N_elements]) * Quad->YA;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_A;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_A;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_A;
           Intersect->N_elements++;
         }
         break;
         
       case Horizontal:
         Intersect->theta[Intersect->N_elements] = (Intersect->Hor - Quad->YA)/(Quad->YB - Quad->YA);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->XB + (1 - Intersect->theta[Intersect->N_elements]) * Quad->XA;
           Intersect->resultY[Intersect->N_elements] = Intersect->Hor;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_A;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_A;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_A;
           Intersect->N_elements++;
         }
         break;

       case General:
         Intersect_General_Cut(Intersect, Quad->XA, Quad->YA, Quad->XB, Quad->YB);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->XP;
           Intersect->resultY[Intersect->N_elements] = Intersect->YP;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_A;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_A;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_B + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_A;
           Intersect->N_elements++;
         }
         break;

       default:
         printf("Unidentificated type of cut!\n");
         exit(0);
         break;
     }
     break;

			case 1:
     switch(Intersect->Cut_Type)
     {
       case Vertical:
         Intersect->theta[Intersect->N_elements] = (Intersect->Vert - Quad->XB)/(Quad->XC - Quad->XB);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->Vert;
           Intersect->resultY[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->YC + (1 - Intersect->theta[Intersect->N_elements]) * Quad->YB;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_B;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_B;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_B;
           Intersect->N_elements++;
         }
         break;

       case Horizontal:
         Intersect->theta[Intersect->N_elements] = (Intersect->Hor - Quad->YB)/(Quad->YC - Quad->YB);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {           
           Intersect->resultX[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->XC + (1 - Intersect->theta[Intersect->N_elements]) * Quad->XB;
           Intersect->resultY[Intersect->N_elements] = Intersect->Hor;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_B;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_B;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_B;
           Intersect->N_elements++;
         }
         break;

       case General:
         Intersect_General_Cut(Intersect, Quad->XB, Quad->YB, Quad->XC, Quad->YC);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->XP;
           Intersect->resultY[Intersect->N_elements] = Intersect->YP;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_B;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_B;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_C + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_B;
           Intersect->N_elements++;
         }
         break;

       default:
         printf("Unidentificated type of cut!\n");
         exit(0);
         break;
     }
     break;

			case 2:
     switch(Intersect->Cut_Type)
     {
       case Vertical:       
         Intersect->theta[Intersect->N_elements] = (Intersect->Vert - Quad->XC)/(Quad->XD - Quad->XC);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->Vert;
           Intersect->resultY[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->YD + (1 - Intersect->theta[Intersect->N_elements]) * Quad->YC;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_D + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_C;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_D + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_C;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_D + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_C;
           Intersect->N_elements++;
         }
         break;

       case Horizontal:
         Intersect->theta[Intersect->N_elements] = (Intersect->Hor - Quad->YC)/(Quad->YD - Quad->YC);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {           
           Intersect->resultX[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->XD + (1 - Intersect->theta[Intersect->N_elements]) * Quad->XC;
           Intersect->resultY[Intersect->N_elements] = Intersect->Hor;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_D + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_C;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_D + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_C;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_D + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_C;
           Intersect->N_elements++;
         }
         break;

       case General:
         Intersect_General_Cut(Intersect, Quad->XC, Quad->YC, Quad->XD, Quad->YD);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->XP;
           Intersect->resultY[Intersect->N_elements] = Intersect->YP;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_D + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_C;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_D + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_C;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_D + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_C;
           Intersect->N_elements++;
         }
         break;

       default:
         printf("Unidentificated type of cut!\n");
         exit(0);
         break;
     }
     break;

			case 3:
     switch(Intersect->Cut_Type)
     {
       case Vertical:
         Intersect->theta[Intersect->N_elements] = (Intersect->Vert - Quad->XD)/(Quad->XA - Quad->XD);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->Vert;
           Intersect->resultY[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->YA + (1 - Intersect->theta[Intersect->N_elements]) * Quad->YD;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_D;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_D;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_D;
           Intersect->N_elements++;
         }
         break;

       case Horizontal:
         Intersect->theta[Intersect->N_elements] = (Intersect->Hor - Quad->YD)/(Quad->YA - Quad->YD);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->XA + (1 - Intersect->theta[Intersect->N_elements]) * Quad->XD;
           Intersect->resultY[Intersect->N_elements] = Intersect->Hor;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_D;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_D;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_D;
           Intersect->N_elements++;
         }
         break;

       case General:
         Intersect_General_Cut(Intersect, Quad->XD, Quad->YD, Quad->XA, Quad->YA);
         if (0.0 <= Intersect->theta[Intersect->N_elements] && Intersect->theta[Intersect->N_elements] <= 1.0)
         {
           Intersect->resultX[Intersect->N_elements] = Intersect->XP;
           Intersect->resultY[Intersect->N_elements] = Intersect->YP;
           Intersect->U[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->U_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Quad->U_val_D;
           Intersect->V[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->V_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Quad->V_val_D;
           Intersect->P[Intersect->N_elements] = Intersect->theta[Intersect->N_elements] * Quad->P_val_A + (1 - Intersect->theta[Intersect->N_elements]) * Quad->P_val_D;
           Intersect->N_elements++;
         }
         break;

       default:
         printf("Unidentificated type of cut!\n");
         exit(0);
         break;
     }
     break;

			default:
     break;
  }
 }
	return;
}
*/

//******************************************************************************
//Intersect Save Result
//******************************************************************************
//Function for saving found intersect nodes with function values
/*
void Intersect_Save_Result(intersect *Intersect, const char *Filename_intersect)
{
	//declare stream
	FILE *fid_intersect;

	//declare variables
	int i;

	//openning stream
	fid_intersect = fopen(Filename_intersect, "w");

 printf("N_elements to save = %d\n", Intersect->N_elements);
	for (i = 0; i < Intersect->N_elements; i++)
	{
		fprintf(fid_intersect, "%24.16lf %24.16lf %24.16lf %24.16lf %24.16lf\n", Intersect->resultX[i], Intersect->resultY[i], Intersect->U[i], Intersect->V[i], Intersect->P[i]);
	}

	fclose(fid_intersect);
	return;
}
*/

//*********************************************
//Reallocate Intersect Memory
//*********************************************
//Reallocate memory of intersect
/*
void Intersect_Reallocate(intersect *Intersect)
{
  Intersect->resultX = (double *)realloc(Intersect->resultX, Intersect->N_elements * sizeof(double));
  Intersect->resultY = (double *)realloc(Intersect->resultY, Intersect->N_elements * sizeof(double));
  Intersect->theta = (double *)realloc(Intersect->theta, Intersect->N_elements * sizeof(double));
  Intersect->U = (double *)realloc(Intersect->U, Intersect->N_elements * sizeof(double));
  Intersect->V = (double *)realloc(Intersect->V, Intersect->N_elements * sizeof(double));
  Intersect->P = (double *)realloc(Intersect->P, Intersect->N_elements * sizeof(double));
  return;
}
*/

//*******************************************************
//Print Intersection Results
//*******************************************************
//Print intersection results
/*
static void Intersect_Print_Results(intersect *Intersect)
{
  int i;
  for (i = 0; i < Intersect->N_elements; i++)
  {
    printf("ResultX = %24.16lf\t\
        ResultY = %24.16lf\t\
        U = %24.16lf\t\
        V = %24.16lf\t\
        p = %24.16lf\n", Intersect->resultX[i], Intersect->resultY[i], Intersect->U[i], Intersect->V[i], Intersect->P[i]);
  }
  return;
}
*/

//*******************************************************************************
//Intersect Cut
//*******************************************************************************
//Solve cut of mesh
/*
static void Intersect_Cut(mesh *Mesh, intersect *Intersect)
{
  int i;

  Intersect->N_elements = 0;
  for (i = 0; i < (Mesh->N_tri + Mesh->N_quad); i++)
  {
    Mesh_Fill_Object(Mesh, Tri, Quad, i);

    switch(Mesh->typ[i])
    {
      case Triangle:
        Intersect_Triangle(Intersect, Tri);
        break;

      case Quadrangle:
        Intersect_Quadrangle(Intersect, Quad);
        break;

      default:
        printf("Error, invalid objects for evaluating intersection!!!\n");
        exit(0);
        break;
    }
  }

  //Reallocate memory of intersect
  Intersect_Reallocate(Intersect);

  //Sort intersect result
  Intersect_Quicksort(Intersect, 0, Intersect->N_elements - 1);

  //Eliminate double values in intersection result
  Intersect_Eliminate(Intersect);

  //Print results
  Intersect_Print_Results(Intersect);

  return;
}
*/

//*************************************************************************************************************************
//Intersect Cut
//*************************************************************************************************************************
//Count characteric numbers of cut line
void Intersect_Cut(mesh *Mesh, const char *Filename, double X1, double Y1, double X2, double Y2)
{
  intersect Intersect;

  Intersect.Vertical.N_elements = (Mesh->Triangle_element.N_triangles + Mesh->Quadrangle_element.N_quadrangles) * 2;
  Intersect.Horizontal.N_elements = (Mesh->Triangle_element.N_triangles + Mesh->Quadrangle_element.N_quadrangles) * 2;
  Intersect.General.N_elements = (Mesh->Triangle_element.N_triangles + Mesh->Quadrangle_element.N_quadrangles) * 2;
  Intersect.Vertical.N_functions = Mesh->Functions.N_functions;
  Intersect.Horizontal.N_functions = Mesh->Functions.N_functions;
  Intersect.General.N_functions = Mesh->Functions.N_functions;

 if ((Utilities_Equalization(X1,X2)) && (Utilities_Equalization(Y1,Y2)))
 {
   printf("Unable to find function of cut line. Line is defined by two different points.\n");
   exit(0);
 }
 else if (Utilities_Equalization(X1,X2))
 {
   printf("Vertical Cut defined.\n");
   Intersect.Vertical.Vert = X1;
   Intersect.Vertical.N_elements = 3 * Mesh->Triangle_element.N_triangles + 4 * Mesh->Quadrangle_element.N_quadrangles;
   Vertical_Allocate(&Intersect.Vertical);
   Vertical_Cut(Mesh, &Intersect.Vertical);
   Vertical_Print(&Intersect.Vertical);
   Vertical_Quicksort(&Intersect.Vertical, 0, Intersect.Vertical.N_elements - 1);
   Vertical_Unique(&Intersect.Vertical);
   Vertical_Print(&Intersect.Vertical);
   Vertical_Save(&Intersect.Vertical, Filename);
   Vertical_Deallocate(&Intersect.Vertical);
 }
 else if (Utilities_Equalization(Y1,Y2))
 {
   printf("Horizontal Cut defined.\n");
   Intersect.Horizontal.Hor = Y1;
   Intersect.Horizontal.N_elements = 3 * Mesh->Triangle_element.N_triangles + 4 * Mesh->Quadrangle_element.N_quadrangles;
   Horizontal_Allocate(&Intersect.Horizontal);
   Horizontal_Cut(Mesh, &Intersect.Horizontal);
   Horizontal_Quicksort(&Intersect.Horizontal, 0, Intersect.Horizontal.N_elements - 1);
   Horizontal_Unique(&Intersect.Horizontal);
   Horizontal_Print(&Intersect.Horizontal);
   Horizontal_Save(&Intersect.Horizontal, Filename);
   Horizontal_Deallocate(&Intersect.Horizontal);
 }
 else
 {
   if (Utilities_Equalization(X2, 0.0))
   {
     Intersect.General.B = Y2;
     Intersect.General.A = (Y1 - Intersect.General.B) / X1;
   }
   else if (Utilities_Equalization(X1, 0.0))
   {
     Intersect.General.B = Y1;
     Intersect.General.A = (Y2 - Intersect.General.B) / X2;
   }
   else 
   {
     Intersect.General.A = (Y1 - Y2) / (X1 - X2);
     Intersect.General.B = Y2 - Intersect.General.A * X2;
   }
   printf("General Cut defined.\n");
   Intersect.General.N_elements = 3 * Mesh->Triangle_element.N_triangles + 4 * Mesh->Quadrangle_element.N_quadrangles;
   General_Allocate(&Intersect.General);
   General_Cut(Mesh, &Intersect.General);
   General_Quicksort(&Intersect.General, 0, Intersect.General.N_elements - 1);
   General_Unique(&Intersect.General);
   General_Print(&Intersect.General);
   General_Save(&Intersect.General, Filename);
   General_Deallocate(&Intersect.General);
 }
 return;
}

//*********************************************
//Deallocate Intersect Memory
//*********************************************
//Deallocate memory of intersect
/*
void Intersect_Deallocate(intersect *Intersect)
{
	//deallocating memory of intersect structure
 free(Intersect->resultX);
	free(Intersect->resultY);
	free(Intersect->theta);
	free(Intersect->U);
	free(Intersect->V);
	free(Intersect->P);

	return;
}
*/
