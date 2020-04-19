//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&                   Titre       :   Interpolation Cosinusoïdale         &&&
//&&&                   Fichier     :   FFT.c                               &&&
//&&&                   Description :   Programme principal                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&                   Auteur      :   Pierre BLACHÉ                       &&&
//&&&                   Date        :   Février 2010                        &&&
//&&&                   Version     :   1.0                                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&               Fichiers Requis :   main.c                              &&&
//&&&                                   p33FJ128MC802.gld                   &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "p33Fxxxx.h"
#include "math.h"

#define PI  3.14159
#define N   8
//----------------------- Configuration du processeur -------------------------
_FOSCSEL(FNOSC_PRI);                // Primary (XT, HS, EC) Oscillator
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON  & POSCMD_HS);
                                    // Clock Switching is enabled
                                    // OSC2 Pin Function : OSC2 is Clock Output
                                    // Primary Oscillator Mode : HS crystals
_FWDT(FWDTEN_OFF);                  // watchdog is off
_FICD(JTAGEN_OFF);                  // desactiver le module JTAG
_FPOR(ALTI2C_OFF);                  // pattes SDA et SCL

//-------------------------------- Variables ----------------------------------
double data[N]={1, 5, 18, 3, 9, 20, 7, 4};
double data_out[N+N-1];

double CosineInterpo (double y1, double y2, double mu);
double CubicInterpol(double y0, double y1, double y2, double y3, double mu);

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Main Program ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
int main (void)
{
    while (1)
    {
        unsigned i;

        // rempliçage du tableau
        for (i = 0; i < (N+N-1); i++)
        {
            if (i%2)
            {
                data_out[i] = 0;
            }
            else
            {
                data_out[i] = data[i/2];
            }
        }

        // calcul de l'interpolation
        for (i = 0; i < (N+N-1); i++)
        {
            if (i%2)
            {
            //  data_out[i] = CosineInterpo(i-1, i+1, 0.5);
                data_out[i] = CubicInterpol(i-2, i-1, i+1, i+2, 0.5);
            }
        }
        asm ("nop");
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------- Calcul de l'interpolation cosinusoïdale --------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
double CosineInterpo (double y1, double y2, double mu)
{
    double mu2;
    mu2 = (1 - cos(mu * PI)) / 2;
    return (y1 * (1 - mu2) + y2 * mu2);
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Calcul de l'interpolation cubic -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
double CubicInterpol(double y0, double y1, double y2, double y3, double mu)
{
   double a0,a1,a2,a3,mu2;

   mu2 = mu*mu;
   a0 = y3 - y2 - y0 + y1;
   a1 = y0 - y1 - a0;
   a2 = y2 - y0;
   a3 = y1;

   return(a0*mu*mu2+a1*mu2+a2*mu+a3);
}