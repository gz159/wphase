/***************************************************************************
*
*                     W phase source inversion package              
*                               -------------
*
*        Main authors: Zacharie Duputel, Luis Rivera and Hiroo Kanamori
*                      
* (c) California Institute of Technology and Universite de Strasbourg / CNRS 
*                                  April 2013
*
*    Neither the name of the California Institute of Technology (Caltech) 
*    nor the names of its contributors may be used to endorse or promote 
*    products derived from this software without specific prior written 
*    permission
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "proto_alloc.h"
#include "read_i_files.h"

#ifndef DEG2RAD
#define DEG2RAD (M_PI/180.)
#endif

void set_mt(double *vm, double **TM);
void jacobi(double **a,int n, int np, double *d, double **v, int *nrot) ;
void eigsrt(double *d, double **v, int n) ;


void vn2sdr(double *vn, double *vs, double *strike, double *dip, double *rake)
{
    const float EPSI = 0.001;
    int   i;
    /* printf("%f %f %f\n", vn[0], vn[1], vn[2]); */
    if (vn[0] < 0.)              // Upwards normal
        for(i=0; i<3; i++)
        {
             vn[i] *= -1.;
             vs[i] *= -1.;
        }

    if ( vn[0] > 1. - EPSI )     // Horizontal plane
    {
        *strike = 0.;
        *dip = 0.;
        *rake = atan2(-vs[2], -vs[1]);
    }

    else if ( vn[0] < EPSI )    // Vertical plane
    {
        *strike = atan2(vn[1], vn[2]);
        *dip = M_PI/2.;
        *rake = atan2(vs[0], -vs[1]*vn[2] + vs[2]*vn[1]);
    }

    else                        // Oblique plane
    { 
        *strike = atan2(vn[1], vn[2]);
        *dip = acos(vn[0]);
        *rake = atan2((-vs[1]*vn[1] - vs[2]*vn[2]), (-vs[1]*vn[2] + vs[2]*vn[1])*vn[0]);
    }

    *strike /= (double)DEG2RAD;
    if ((*strike) < 0.) 
        (*strike) += 360.;
    *dip /= (double)DEG2RAD;
    *rake /= (double)DEG2RAD;
    return;
}

void get_planes(double *vm, double *eval3, double **evec3, double *strike1,double *dip1,double *rake1, double *strike2, double *dip2, double *rake2)
{
    int    nrot, i ;
    double *vn1, *vn2 ;
    double **TM;
  
    /* Memory allocation */
    vn1 = double_alloc(3)    ;
    vn2 = double_alloc(3)    ;
    TM  = double_alloc2(3,3) ;
  
    /* Tensor representation */
    set_mt(vm,TM) ;

    /* Get eigvalues and eigvectors*/
    jacobi(TM,3,3,eval3,evec3,&nrot) ;
    eigsrt(eval3,evec3,3) ;

    for(i=0 ; i<3 ; i++)
    {
         vn1[i] = (evec3[i][0]+evec3[i][2])/sqrt(2.) ;
         vn2[i] = (evec3[i][0]-evec3[i][2])/sqrt(2.) ;
    }
    vn2sdr(vn1, vn2, strike1, dip1, rake1); 
    vn2sdr(vn2, vn1, strike2, dip2, rake2); 
  
    /* Memory Freeing */
    free((void*)vn1) ;
    free((void*)vn2) ;
    for(i=0;i<3;i++)
	free((void*)TM[i]);
    free((void*)TM);
}

void set_mt(double *vm, double **TM)
{
    TM[0][0] =   vm[0] ;
    TM[1][1] =   vm[1] ;
    TM[2][2] =   vm[2] ; 
    TM[0][1] =   vm[3] ;
    TM[0][2] =   vm[4] ;
    TM[1][2] =   vm[5] ;
    TM[1][0] = TM[0][1] ;
    TM[2][0] = TM[0][2] ;
    TM[2][1] = TM[1][2] ;
}
