#include <stdio.h>
#include <stdlib.h>
#include "predicat.h"
#include "utils.h"


typedef int (*func)(char*,char*);

func funcs[] = {name, type, uid, gid, user, group, aTime, cTime, mTime, perm};


int main(int argc, char* argv[])
{
	int i;
	DIR *test = NULL;
	struct dirent test2 = NULL;
	
	test = opendir(".");
	
	while((test2 = readdir(test))!=NULL)
	{
		printf("%s\n", test2->d_name);
	}
	
	
	/*if(argc != 4)
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
	*/
	
	return 0;
}
