/*  Find                        	param.c

By : deneb, Hugo					Last Modif : 15/06/11
_____________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *nom[] = {
	"print", "ls", "prune","true","false", "name", "type", "uid", "gid", "user", "group", "atime", "ctime", "mtime", "perm", "exec"
} ;

#define NNAMES (sizeof(nom) / sizeof(nom[0]))
#define WOARG 4

int getParam(int** tab, char*** param, char* argv[], int argc)
{
	int i, n=0, nbParam=0;
	
	
	for (i=0;i<argc;i++)
	{
		if(argv[i][0]=='-')
			nbParam++;
	}
	(*tab) = (int*)malloc(nbParam*sizeof(int));
	(*param) = (char**)malloc(nbParam*sizeof(char*));
	
	for (i=0;i<argc;i++)
	{
		if(argv[i][0]=='-')
		{
			int j,index=-1;
			
			for(j=0;j<NNAMES && index<0;j++)
			{
				if(!strcmp(argv[i]+1,nom[j]))
					index = j;
			}
			
			if(index<0)
			{
				printf("Parametre incorrect : %s\n", argv[i]+1);
				for(i=0;i<n;i++)
					free((*param)[i]);
				free(*tab);
				free(tab);
				free(*param);
				free(param);
				exit(EXIT_FAILURE);
			}
			
			(*tab)[n]=index;
			if(index>WOARG)
			{
				(*param)[n] = (char*)malloc(strlen(argv[i+1])+1); // voir a utiliser sizeof()
				strcpy((*param)[n], argv[i+1]);
				i++;
			}
			n++;	
		}
	}
	return nbParam;
}

void freeParam(int tab[], char* param[], int nbParam)
{
	int i;
	free(tab);
	for(i=0;i<nbParam;i++)
		free(param[i]);
	free(param);
}
