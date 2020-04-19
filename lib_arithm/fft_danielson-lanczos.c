//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&               Calcul d'une FFT 
//&&&    avec l'algorithme de Danielson-Lanczos
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "maths.h"

#define PI = 3.141592653
#define    SWAP(a,b) {wr=a; a=b; b=wr;}

void FFT (int N, double *data)
{
    double wt, wr, wi, wpr, wpi, tempi, tempr;
    int i, j, m, n;
    int mmax, istep;
    mmax=2;
    n = 2*N;
    j=0;

    for (i=2; i<N; i+=2)
    {
        m=N;
        while (j>=m)
        {
            j-=m;
            m>>=1;
        }
        j+=m;

        if (j>i)
        {
            SWAP (data[j], data[i]);
            SWAP (data[j+1], data[i+1]);
            if (j<N)
            {
                SWAP (data[n-j-2], data[n-i-2]);
                SWAP (data[n-j-1], data[n-i-1]);
            }
        }
    }

    while (n>mmax)
    {
        istep = mmax<<1;
        wpr = cos (2.0*PI/mmax)
        wpi = sin (2.0*PI/mmax)
        wr = 1.0;
        wi = 0.0;
        for (m=1; m<mmax; m+=2)
        {
            for (i=m; i<=n; i+=istep)
            {
                j = i+mmax;
                tempr = wr*data[j-1] + wi*data[j];
                tempi = wr*data[j] - wi*data[j-1];
                data[j-1] = data[i-1] - tempr;
                data[j] = data[i] - tempi;
                data[i-1] += tempr;
                data[i] += tempi;
            }
            wt = wr;
            wr = wt*wpr - wi*wpi;
            wi = wi*wpr + wt*wpi;
        }
        mmax = istep;
    }
}