/*  Find                        	main.c

By : deneb							Last Modif : 21/06/11
_____________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "predicat.h"
#include "predicatLs.h"
#include "utils.h"
#include "param.h"
#include "parcour.h"
// si pas de chemin, chemin courant

// problème : trop de free (pas besoin de free quand pas de params)

// les quittage prusquent ne libèrent pas la mémoire

int main(int argc, char* argv[])
{
	int i, **tab, nbPath, nbParam;
	int minDepth = 0, maxDepth =-1;
	char*** param;
	
	tab = (int**)malloc(sizeof(int*));
	param = (char***)malloc(sizeof(char**));

	nbParam = getParam(&nbPath, tab, param, &minDepth, &maxDepth, argv, argc);
	
	if(nbParam>0)
		for(i=0;i<nbPath;i++)
		{
			parcours(argv[i+1], minDepth, maxDepth, *tab, *param, nbParam);
		}
	
	/* Débug !!! 
	printf(" il y a %d paramètres\n", nbParam);
	for(i=0;i<nbParam;i++)
	{
		printf("fonc no %d, parametre : %s\n", (*tab)[i], (*param)[i]);
	}
	printf("\net %d chemins : \n", nbPath);
	for(i=0;i<nbPath;i++)
	{
		printf("-> %s\n", argv[i+1]);
	}
	//*/
	
	freeParam(*tab, *param, nbParam);
	free(tab);
	free(param);
	return EXIT_SUCCESS;
}
