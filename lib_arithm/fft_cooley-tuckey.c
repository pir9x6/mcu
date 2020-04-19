/*
Méthode de Cooley-Tukey (fonction tf_cooley_tukey). 
Deux fonctions doivent être appelées successivement :


Fonction tf_reversion 
Les paramètres d'appel de cette fonction sont : 

indice : un entier sans signe ; 
nb : le nombre de chiffres binaires que comporte indice transcodé en base 2. 
Elle renvoie un entier sans signe obtenu en inversant les chiffres de la représentation binaire de l'entier indice.


Fonction tf_cooley_tukey 
Les paramètres d'appel de cette fonction sont : 

r : un entier tel que le nombre d'échantillons soit 2r ; 
n : le nombre d'échantillons, qui doit être égal à 2r ; 
f : un tableau de dimension NMAX*2 contenant les valeurs échantillonnées (une valeur par ligne, la 1e colonne contenant la partie réelle et la 2e colonne la partie imaginaire) ; 
t : un tableau de dimension NMAX*2 . 
Elle renvoie dans le tableau t la transformation de Fourier discrète des valeurs de f par la méthode de Cooley-Tukey (une valeur par ligne, la 1e colonne contenant la partie réelle et la 2e colonne la partie imaginaire) .


La constante réelle PI est égale à 3.1415926535897932385. 

La constante entière NMAX est égale au nombre maximum d'échantillons. 
*/

unsigned int tf_reversion(unsigned int indice,int nb)
{
    unsigned int p, k, i, size;
    size=32;
    p=indice >> nb-1;
    for(i=1; i<nb; i++)
    {
        k=indice << i+size-nb;
        k=k >> size-1;
        k=k << i;
        p+=k;
    }
    return(p);
}

void tf_cooley_tukey(int r,unsigned int n,double f[NMAX][2],double t[NMAX][2])
{
    int k;
    unsigned int ne,ns,n1,n2,i,j,tj;
    double arg,tr1,ti1,tr2,ti2,cr,ci;
    double tcos[NMAX],tsin[NMAX];
    n2=n/2;
    arg=PI/n2;

    for(i=0;i<n2;i++)
    {
        tcos[i]=cos(-arg*i);
        tcos[i+n2]=-tcos[i];
        tsin[i]=sin(-arg*i);
        tsin[i+n2]=-tsin[i];
    }

    for (i=0;i<n;i++)
    {
        j=tf_reversion(i,r);
        t[j][0]=f[i][0];
        t[j][1]=f[i][1];
    }

    ne=1;n1=2;ns=n;
    for (k=0;k<r;k++)
    {
        for (i=0;i<=n-n1;i+=n1)
        {
            for(j=i;j<=i+ne-1;j++)
            {
                tj=j*n2;
                while (tj>=n) tj-=n;
                cr=tcos[tj];
                ci=tsin[tj];
                tr1=t[j][0]+cr*t[j+ne][0]-ci*t[j+ne][1];
                ti1=t[j][1]+cr*t[j+ne][1]+ci*t[j+ne][0];
                tj=(j+ne)*n2;
                while (tj>=n) tj-=n;
                cr=tcos[tj];
                ci=tsin[tj];
                tr2=t[j][0]+cr*t[j+ne][0]-ci*t[j+ne][1];
                ti2=t[j][1]+cr*t[j+ne][1]+ci*t[j+ne][0];
                t[j][0]=tr1;t[j][1]=ti1;
                t[j+ne][0]=tr2;t[j+ne][1]=ti2;
            }
        }
        ne=n1;
        n1=2*ne;
        ns=n2;
        n2=ns/2;
    }
}
