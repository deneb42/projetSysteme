#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fnmatch.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

#include "predicat.h"

int true()
{
	return 1;
}

int false()
{
	return 0;
}

int name(char* pattern, char* path)
{
	return !fnmatch(pattern, path, 0);
}

int type(char* refType,char* path) // plus compliqué en réalité
{
	struct stat statFich;
	statWOError(path, &statFich);
	
	return statFich.st_mode == stringToInt(refType);
}

int uid(char* refUID,char* path)
{
	struct stat statFich;
	statWOError(path, &statFich);

	return statFich.st_uid == stringToInt(refUID);
}

int gid (char* refGID,char* path)
{
	struct stat statFich;
	statWOError(path, &statFich);

	return statFich.st_gid == stringToInt(refGID);
}

int user(char* user,char* path)
{
	struct stat statFich;
	struct passwd* statUser;
	
	statWOError(path, &statFich);
	statUser = getpwuid(statFich.st_uid);
	if(statUser==NULL) 
	{
		perror("Name recuperation error\n");
		exit(EXIT_FAILURE);
	}

	return !strcmp(user, statUser->pw_name);   
}
    
int group(char* group,char* path)
{
	struct stat statFich;
	struct group* statGroup;
	
	statWOError(path, &statFich);
	statGroup = getgrgid(statFich.st_gid);
	if(statGroup==NULL) 
	{
		perror("Group recuperation error\n");
		exit(EXIT_FAILURE);
	}

	return !strcmp(group, statGroup->gr_name);
}

int atime(char* time, char* path)
{
struct stat statFich;
	statWOError(char* path, struct stat *statFich)
}

int ctime(char* time, char* path)
{
struct stat statFich;
	statWOError(char* path, struct stat *statFich)
}

int mtime(char* time, char* path)
{
struct stat statFich;
	statWOError(char* path, struct stat *statFich)
}



// utils ------------------------------------------------------

int stringToInt(char* string)
{
	int i;
	int stringInt=0;

	for(i=0;string[i]!='\0';i++) 
	{
		stringInt*=10;
		stringInt+= string[i]-'0';//manque gestion d'erreur
	}
	
	return stringInt;
}

void statWOError(char* path, struct stat *statFich)
{ // buffer func whitch handle errors during the call of stat()
	if(stat(path, statFich)==-1)
	{
		perror("Stat recuperation error\n");
		exit(EXIT_FAILURE);
	}
}
