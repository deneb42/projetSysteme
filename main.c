/*  Find                        	main.c

By : deneb							Last Modif : 15/06/11
_____________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include "predicat.h"
#include "predicatLs.h"
#include "utils.h"
#include "param.h"


typedef int (*func)(char*,char*);

func funcs[] = {name, type, uid, gid, user, group, aTime, cTime, mTime, perm};


int main(int argc, char* argv[])
{
	int i, n, **tab;
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
	
	//* test lecture parametres
	tab = (int**)malloc(sizeof(int*));
	param = (char***)malloc(sizeof(char**));
	
	n = getParam(tab, param, argv, argc);
	printf(" il y a %d paramètres\n", n);
	for(i=0;i<n;i++)
	{
		printf("fonc no %d, parametre : %s\n", (*tab)[i], (*param)[i]);
	}
	
	freeParam(*tab, *param, n);
	free(tab);
	free(param);
	// */
	
	return 0;
}
