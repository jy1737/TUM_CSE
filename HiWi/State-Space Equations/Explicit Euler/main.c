/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  Implicit Euler solver for State Space systems                              */                                                                                                
/*                                                                             */  
/*  Developer:  Jiho Yang (MEng)                                               */
/*              M.Sc. candidate, Computational Science & Engineering           */
/*              Technische Universitat Munchen                                 */
/*                                                                             */ 
/*  Work conducted as a student job (HiWi)                                     */
/*  under Seungyong Oh (Dipl.-Ing)                                             */
/*  at Lehrstuhl fur Fordertechnik Materialfluss Logistik                      */
/*  Dept of Mechanical Engineering                                             */
/*  Technische Universitat Munchen, Germany                                    */
/*                                                                             */
/*  Final update date: 29/07/2016                                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/ 

/* step size must be chosen based on matrix A (in better words, A shouldn't be ill-conditioned) */
/* i should always be row, and j should always be columns */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "helper.h"
#include "explicit_euler.h"
#include "visual.h"

int main(int argn, char **args){   

    int num_body = 1;        /*Number of bodies in the system*/
    double dt = 0.1;         /*Step size*/
    double t_end = 10.0;     /*End time*/
    int itermax = 500;       /*Maximum number of Newton iteration*/
    int i;

    double **x, *u;          /*2D array will be used so as to store solution for each time step*/
    double **A, **B;

    /*Allocate memory*/
    x = matrix(0, num_body * 2 - 1, 0, t_end / dt);
    A = matrix(0, num_body * 2 - 1, 0, num_body * 2 - 1);
    B = matrix(0, num_body * 2 - 1, 0, num_body * 2 - 1);
    u = malloc((num_body * 2 - 1) * sizeof(double));

    /*Initialise matrices*/
    init_matrix(x, 0, num_body * 2 - 1, 0, t_end / dt, 0);
    init_matrix(A, 0, num_body * 2 - 1, 0, num_body * 2 - 1, 10);
    init_matrix(B, 0, num_body * 2 - 1, 0, num_body * 2 - 1, 20); 

    /*Physics*/
    double mass = 1;
    double k    = 1;
    double c    = 1; 

    /*Manually set stiff and source matrices for a single body mass-spring-damper system with m,c,k,F = 1*/
    A[0][0] = 0;
    A[0][1] = 1;
    A[1][0] = (-1)*mass/k;
    A[1][1] = (-1)*c/mass; 

    B[0][0] = 0;
    B[0][1] = 0;
    B[1][0] = 0;
    B[1][1] = 1;

    /*Initialise source vector*/
    for (i = 0; i <= num_body * 2 - 1; i++){

        u[i] = 1;
    
    }

    /*Explicit Euler*/
    explicit_euler(x, u, A, B, t_end, dt, itermax, num_body);

    /*Export results*/
    export_result("Explicit_Euler", t_end, dt, x);

    /*Free memory allocation*/
    free_matrix(x, 0, num_body * 2 - 1, 0, t_end / dt);
    free_matrix(A, 0, num_body * 2 - 1, 0, num_body * 2 - 1);
    free_matrix(B, 0, num_body * 2 - 1, 0, num_body * 2 - 1);
    free(u);

    return 0;

}

