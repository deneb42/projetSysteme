/*  Find                        	utils.c

By : deneb							Last Modif : 31/05/11
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

void parcours(char *path, int depth, int minDepth, int maxDepth)
{
	DIR *test = NULL;
	struct dirent *test2 = NULL;
	char chemin[100] = "";
	
	test = opendir(path);
	if(test==NULL)
	{
		printf("Erreur au chargement du fichier %s\n", path);
		exit(EXIT_FAILURE);
	}
	
	while((test2 = readdir(test))!=NULL)
	{
		if(test2->d_name[0]!='.')
		{
		chemin[0]= '\0';
		strcat(chemin, path); strcat(chemin, "/");
		strcat(chemin, test2->d_name);
		
		if(depth>=minDepth)
		{ // traitement
			printf("%s\n", chemin);
		}
		if(type("d",chemin) && depth<maxDepth)
			parcours(chemin, depth+1, minDepth, maxDepth);
		}
	}
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
	if(stat(path, statFich)==-1)
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
