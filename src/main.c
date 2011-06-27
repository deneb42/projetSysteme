/*  Find                        	main.c

By : deneb							Last Modif : 21/06/11
_____________________________________________________________*/

#include <stdlib.h>
#include "param.h"
#include "parcour.h"


#include <stdio.h>
#include "utils.h"
// si pas de chemin, chemin courant

// les quittage prusquent ne libèrent pas la mémoire

int main(int argc, char* argv[])
{
	int i, nbPath=0, nbParam=0, *tab=NULL;
	int minDepth = 0, maxDepth =-1;
	char** param=NULL;

	nbParam = getParam(&nbPath, &tab, &param, &minDepth, &maxDepth, argv, argc);
	
	if(nbParam>0) 
	{
		if(nbPath==0)
		{
			
			parcours(argv[0], minDepth, maxDepth, tab, param, nbParam);
		}
		else
			for(i=0;i<nbPath;i++)
				parcours(argv[i+1], minDepth, maxDepth, tab, param, nbParam);
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
	
	freeParam(tab, param, nbParam);
	return EXIT_SUCCESS;
}
