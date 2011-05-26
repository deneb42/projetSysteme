#include <stdio.h>
#include <stdlib.h>
#include "predicat.h"


typedef int (*func)(char*,char*);

func funcs[] = {name, type, uid, gid, user, group};


int main(int argc, char* argv[])
{
	int i;
	
	if(argc != 4)
	{
		perror("Parametre de type 'n° de function' 'parametre' 'path'\n");
		return 1;
	}
	
	for(i=0;i<argc;i++)
	{
		printf("%s\n", argv[i]);
	}
	
	printf("%d\n", stringToInt(argv[1]));
	
	printf("resultat : %d\n", funcs[stringToInt(argv[1])](argv[2],argv[3]));
	
	return 0;
}
