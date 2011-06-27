/*  Find                        	parcour.c

By : deneb							Last Modif : 27/06/11
_____________________________________________________________*/

#include <dirent.h>
#include <string.h>

#include "predicat.h"
#include "predicatLs.h"
#include "parcour.h"

typedef int (*func)(char*,char*);

func funcs[] = {print, ls, prune, true, false, name, type, uid, gid, user, group, aTime, cTime, mTime, perm, exec};


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
		printf("> error : could not load %s\n", path);
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
	int i, isTrue = 1, returnValue;
	
	for(i=0; i<nbParam && isTrue;i++)
	{
		if(tab[i]>=0)
		{
			returnValue = (funcs[tab[i]](param[i], chemin));
			
			if(returnValue<0)
			{
				freeParam(tab, param, nbParam);
				return EXIT_FAILURE;
			}
			
			isTrue = isTrue && returnValue;
		}
	}
	
	return isTrue;
}
