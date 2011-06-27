/*  Find                        	parcour.c

By : deneb							Last Modif : 27/06/11
_____________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "predicat.h"
#include "predicatLs.h"
#include "parcour.h"
#include "param.h"

typedef int (*func)(char*,char*);

func funcs[] = {NULL, NULL, NULL, print, ls, prune, true, false, name, type, uid, gid, user, group, aTime, cTime, mTime, perm, exec};


void parcours(char *path, int minDepth, int maxDepth, int tab[], char* param[], int nbParam)
{
	if(minDepth<1)
		process(path, tab, param, nbParam);
		
	if(maxDepth!=0)
		parcours_recur(path, 1, minDepth, maxDepth, tab, param, nbParam);
}

void parcours_recur(char *path, int depth, int minDepth, int maxDepth, int tab[], char* param[], int nbParam)
{
	DIR *test = NULL;
	struct dirent *test2 = NULL;
	char chemin[1000];
	
	test = opendir(path);
	if(test==NULL)
	{
		printf("> warning : could not load %s\n", path);
		return;
	}
	
	//chemin = (char*)malloc(strlen(path)+strlen(test2->d_name)+2);
	
	while((test2 = readdir(test))!=NULL)
	{
		//chemin = (char*)malloc(strlen(path)+strlen(test2->d_name)+2);
		if(test2->d_name[strlen(test2->d_name)-1]!='.')
		{
			strcpy(chemin, path); 
			if(chemin[strlen(chemin)-1]!='/')
				strcat(chemin, "/");
			strcat(chemin, test2->d_name);
			
			if(depth>=minDepth)
				process(chemin, tab, param, nbParam);

			if(type("d",chemin) && depth!=maxDepth)
				parcours_recur(chemin, depth+1, minDepth, maxDepth, tab, param, nbParam);
		}
	}
	//free(chemin);
	closedir(test);
}

int process(char *chemin, int tab[], char* param[], int nbParam)
{
	int i, isTrue, returnValue, err=0;
	
	if(tab[0]>=END_OP) // si c'est un prédicat (sans not, si on a un oppérateur au début, c'est pas bon
		isTrue = (funcs[tab[0]](param[0], chemin));
	else
		err=1;
		
	for(i=1; i<nbParam && !err;i++)
	{
		//printf("%d, istrue : %d\n", i, isTrue);
		
		returnValue = -1;

		if(tab[i]>0) // >= quand on gèrera not // si la fonction est définie
		{
			if(tab[i]>=END_OP) // si on a affaire a un prédicat
			{
				if(isTrue) // dans le cas d'un et
					returnValue = (funcs[tab[i]](param[i], chemin));
				else
					returnValue=0;
			}
			else // sinon on a affaire a un opperateur
			{
				if(i+1>=nbParam)
				{
					printf("> error : the last parameter cannot be an opperator\n");
					err=1;
				}
				else if (tab[i+1]<END_OP)
				{
					printf("> error : there cannot be two opperators one right after another\n");
					err=1;
				}
				else 
				{
					if(isTrue || tab[i+1]!=PRED_AND) si on a un faux, on n'applique pas la fonction
						returnValue = (funcs[tab[i+1]](param[i+1], chemin));
					else
						returnValue=0;
				}
			}

			if(returnValue<0)
				err=1;
			else
			{
				if(tab[i]==PRED_OR)
				{
					isTrue = isTrue || returnValue;
					i++;
				}
				else
				{
					if(tab[i]==PRED_AND)
						i++;
					isTrue = isTrue && returnValue;
				}
			}
		}
	}
	//printf("%d, istrue : %d\n", i, isTrue);
	
	if(err)
	{
		//printf("error ?\n");
		freeParam(tab, param, nbParam);
		exit(EXIT_FAILURE);
	}
	
	return isTrue;
}
