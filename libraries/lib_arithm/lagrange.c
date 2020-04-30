/*
Méthode de Lagrange (fonctions it_pol_lagrange et it_coef_lagrange). 

Deux fonctions doivent être appelées successivement :


Fonction it_coef_lagrange 
Les paramètres d'appel de cette fonction sont : 

	n : le nombre de points d'interpolation moins 1 (c'est-à-dire l'indice du dernier) ; 
	x : un tableau contenant les abscisses d'interpolation ; 
	f : un tableau contenant les valeurs de la fonction f(x) aux points d'interpolation ; 
	d : un tableau qui renvoie les coefficients des polynômes de base. 
	Elle calcule dans le tableau d les coefficients des polynômes de base 
	associés aux  n+1 valeurs distinctes de la variable données par le paramètre x.


Fonction it_pol_lagrange 
Les paramètres d'appel de cette fonction sont : 

	n : le nombre de points d'interpolation moins 1 (c'est-à-dire l'indice du dernier) ; 
	d : un tableau contenant les coefficients des polynômes de base ; 
	x : un tableau contenant les abscisses d'interpolation ; 
	alpha : la valeur de la variable. 
Elle renvoie, pour la valeur donnée de la variable, la valeur du polynôme 
d'interpolation calculée à partir des éléments du tableau des coefficients des polynômes de base.


La constante entière NMAX est égale au nombre maximum de points d'interpolation. */

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
