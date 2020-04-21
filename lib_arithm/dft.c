//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&                   Titre       :   Algorithme de DFT                   &&&
//&&&                   Fichier     :   DFT.c                               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&                   Auteur      :   Pierre BLACHÉ                       &&&
//&&&                   Date        :   Février 2010                        &&&
//&&&                   Version     :   1.0                                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&               Fichiers Requis :   DFT.c & DFT.h                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "types.h"
#include "math.h"

#define PI 3.14159

void dft(double *data_in, double *data_out, u32 N)
{
    u32 i, k;
    complex_t complex[N];
    double angle;
    double w = 2*PI/N;

    // calcul de la transformée
    for (k = 0; k < N; k++)
    {
        complex.re[k] = 0;
        complex.im[k] = 0;
        for (i = 0; i < N; i++)
        {
            angle = w * k * i;
            complex.re[k] += data_in[i] * cos(angle);    // calcul des reels
            complex.im[k] -= data_in[i] * sin(angle);    // calcul des imaginaires
        }
        data_out[k] = complex.re[k] * complex.re[k] + complex.im[k] * complex.im[k];      // calcul du module des amplitudes
    }
}

void idft(double *data_in, double *data_out, u32 N)
{

}



