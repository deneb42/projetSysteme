/*  Find                        	param.c

By : deneb, Hugo					Last Modif : 21/06/11
_____________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "param.h"

const char *nom[] = {
	"not", "o", "a", "print", "ls", "prune","true","false", "name", "type", "uid", "gid", "user", "group", "atime", "ctime", "mtime", "perm", "exec"
} ;

#define NNAMES (sizeof(nom) / sizeof(nom[0]))
#define WO_ARG 7

int getParam(int* nbPath, int** tab, char*** param, int* minDepth, int* maxDepth, char* argv[], int argc)
{
	int i=1, n=0, nbParam=0;
	int boolTraitement=0;
	(*nbPath)=0;
	
	while(i<argc && argv[i][0]!='-')
	{
		(*nbPath)++;
		i++;
	}
	
	for (;i<argc;i++)
	{
		if(argv[i][0]=='-')
			nbParam++;
	}
	
	nbParam++; //(au cas ou il faille ajouter un traitement), gestion mémoire pas optimale mais évite des segfault
	
	(*tab) = (int*)malloc(nbParam*sizeof(int));
	(*param) = (char**)malloc(nbParam*sizeof(char*));
		
	for (i=(*nbPath) ;i<argc;i++) // on commence au dernier path
	{
		if(argv[i][0]=='-')
		{
			int j,index=-1;
			
			for(j=0;j<NNAMES && index<0;j++)
			{
				if(strcmp(argv[i]+1,nom[j])==0) // arjv[i]+1 pour ignorer le -
					index = j; // pour éviter les oppérateurs
			}
			
			(*tab)[n]=index;		
			if(index==PRED_PRINT || index==PRED_LS || index==PRED_EXEC) // on retient si il y a un traitement
				boolTraitement=1;
			
			if(index<0)
			{
				if(strcmp(argv[i]+1, "mindepth")==0)
				{
					(*minDepth) = stringToInt(argv[i+1]);
					i++;
				}
				else if(strcmp(argv[i]+1, "maxdepth")==0)
				{
					if((*maxDepth) >= 0)
					{
						printf("> error : maxdepth and prune are not compatible and can be set only once\n");
						return -n;
					}
					(*maxDepth) = stringToInt(argv[i+1]);
					i++;
				}
				else
				{
					printf("> error : %s is not a valid parameter\n", argv[i]+1);
					return -n;
				}
			}
			else {
				if(index>WO_ARG)
				{
					(*param)[n] = (char*)malloc(strlen(argv[i+1])+1);
					strcpy((*param)[n], argv[i+1]);
					i++;
				}
				else 
				{
					(*param)[n]=NULL;
					
					if(index == PRED_PRUNE) // si prune
					{
						if(maxDepth>=0)
						{
							printf("> error : maxdepth and prune are not compatible and can be set only once\n");
							return -n;
						}
						(*maxDepth) = 1;
					}
				}
			}
			n++;
		}
	}
	(*param)[n]=NULL;
	
	if(!boolTraitement) // si il n'y a pas eu de print ou de ls ou de exec
		(*tab)[n]=PRED_PRINT; // on ajoute print
	else
		(*tab)[n]=-1;

	return nbParam;
}

void freeParam(int tab[], char* param[], int nbParam)
{
	int i, n;
	
	n= nbParam>0 ? nbParam : -nbParam;
	
	free(tab);
	for(i=0;i<n;i++)
		if(param[i]!=NULL)
			free(param[i]);
	free(param);
}
