/*
M�thode de Lagrange (fonctions it_pol_lagrange et it_coef_lagrange). 

Deux fonctions doivent �tre appel�es successivement :


Fonction it_coef_lagrange 
Les param�tres d'appel de cette fonction sont : 

	n : le nombre de points d'interpolation moins 1 (c'est-�-dire l'indice du dernier) ; 
	x : un tableau contenant les abscisses d'interpolation ; 
	f : un tableau contenant les valeurs de la fonction f(x) aux points d'interpolation ; 
	d : un tableau qui renvoie les coefficients des polyn�mes de base. 
	Elle calcule dans le tableau d les coefficients des polyn�mes de base 
	associ�s aux  n+1 valeurs distinctes de la variable donn�es par le param�tre x.


Fonction it_pol_lagrange 
Les param�tres d'appel de cette fonction sont : 

	n : le nombre de points d'interpolation moins 1 (c'est-�-dire l'indice du dernier) ; 
	d : un tableau contenant les coefficients des polyn�mes de base ; 
	x : un tableau contenant les abscisses d'interpolation ; 
	alpha : la valeur de la variable. 
Elle renvoie, pour la valeur donn�e de la variable, la valeur du polyn�me 
d'interpolation calcul�e � partir des �l�ments du tableau des coefficients des polyn�mes de base.


La constante enti�re NMAX est �gale au nombre maximum de points d'interpolation. */

void coef_lagrange(int n, double x[NMAX], double f[NMAX], double d[NMAX])
{
	int i,j;
	for(i=0; i<=n; i++)
	{
		d[i]=f[i];
		for(j=0; j<=n; j++)
		if(j!=i) d[i]/=x[i]-x[j];
	}
}


double pol_lagrange(int n, double d[NMAX], double x[NMAX], double alpha)
{
	int i,j;
	double l,p;
	p=0;
	for(i=0; i<=n; i++)
	{
		l=d[i];
		for(j=0; j<=n; j++)
			if(j!=i) l*=alpha-x[j];
		p=p+l;
	}
	return(p);
}
