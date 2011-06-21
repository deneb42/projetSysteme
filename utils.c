/*  Find                        	utils.c

By : deneb							Last Modif : 21/06/11
_____________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#include "utils.h"
#include "predicat.h"
#include "predicatLs.h"


typedef int (*func)(char*,char*);

func funcs[] = {print, ls, prune, true, false, name, type, uid, gid, user, group, aTime, cTime, mTime, perm, exec};


void parcours(char *path, int minDepth, int maxDepth, int tab[], char* param[], int nbParam)
{
	if(maxDepth==0)
	{
		//if(process(chemin, tab, param, nbParam))
			printf("%s\n", path); // debug
		return;
	}
	
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
		printf("Erreur au chargement du dossier %s\n", path);
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
			{ // traitement
				//if(process(chemin, tab, param, nbParam))
					printf("%s\n", chemin); // debug
			}

			if(type("d",chemin) && depth!=maxDepth && strcmp("/proc", chemin))
				parcours_recur(chemin, depth+1, minDepth, maxDepth, tab, param, nbParam);
		}
	}
	//free(chemin);
	closedir(test);
}

int process(char *chemin, int tab[], char* param[], int nbParam)
{
	int i, isTrue = 1;
	
	for(i=0; i<nbParam && isTrue;i++)
	{
		isTrue = isTrue && (funcs[tab[i]](param[i], chemin));
	}
	
	return isTrue;
}

int stringToInt(char* string)
{
	int i;
	int stringInt=0;

	for(i=0;string[i]!='\0';i++) 
	{
		stringInt*=10;
		stringInt+= string[i]-'0';//manque gestion d'overFlow
	}
	
	return stringInt;
}

void statWOError(char* path, struct stat *statFich)
{ // buffer func whitch handle errors during the call of stat()
	if(lstat(path, statFich)==-1)
	{
		perror("Stat lookup error");
		exit(EXIT_FAILURE);
	}
}

int compTime(time_t reference, char* comparetTo)
{
	int parJours;
	int jours = ((int)difftime(time(NULL), reference) / (3600*24));  //temps en jours
	
	if(comparetTo[0]=='+')
	{
		parJours=stringToInt(comparetTo+1);
		if(jours>=parJours)
			return 1;
	}
	else if(comparetTo[0]=='-')
	{
		parJours=stringToInt(comparetTo+1);
		if(jours<=parJours)
			return 1;
	}
	else
	{
		parJours=stringToInt(comparetTo);
		if(jours==parJours)
			return 1;
	}
	return 0;
}
