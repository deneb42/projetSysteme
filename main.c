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
// si pas de chemin, chemin courant


//use atexit pour les libérations mémoires


int main(int argc, char* argv[])
{
	int i, n, **tab, nbPath;
	char*** param;
	
	/* test prédicats && parcours

	if(argc != 4)
	{
		//perror("Parametre de type 'n° de function' 'parametre' 'path'\n");
		
		parcours(argv[1], 0, 1, 2);
		//print(argv[1]);
		return 1;
	}
	
	for(i=0;i<argc;i++)
	{
		printf("%s\n", argv[i]);
	}
	
	printf("%d\n", stringToInt(argv[1]));
	
	printf("resultat : %d\n", funcs[stringToInt(argv[1])](argv[2],argv[3]));
	//*/
	
	//test lecture parametres
	tab = (int**)malloc(sizeof(int*));
	param = (char***)malloc(sizeof(char**));

	n = getParam(&nbPath, tab, param, argv, argc);
	
	for(i=0;i<nbPath;i++)
	{
		parcours(argv[i+1], 0, -1, *tab, *param, n);
	}
	
	/* Débug !!! 
	printf(" il y a %d paramètres\n", n);
	for(i=0;i<n;i++)
	{
		printf("fonc no %d, parametre : %s\n", (*tab)[i], (*param)[i]);
	}
	printf("\net %d chemins : \n", nbPath);
	for(i=0;i<nbPath;i++)
	{
		printf("-> %s\n", argv[i+1]);
	}
	//*/
	
	freeParam(*tab, *param, n);
	free(tab);
	free(param);
	return 0;
}
