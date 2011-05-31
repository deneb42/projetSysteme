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

int type(char* refType,char* path)
{
	struct stat statFich;
	statWOError(path, &statFich);
	int type = statFich.st_mode & S_IFMT;
	
	switch(refType[0])
	{
		case 'f':
			if(type==S_IFREG)
				return 1;
			break;
		case 'd':
			if(type==S_IFDIR)
				return 1;
			break;
		case 'l':
			if(type==S_IFLNK)
				return 1;
			break;
		case 's':
			if(type==S_IFSOCK)
				return 1;
			break;
		case 'b':
			if(type==S_IFBLK)
				return 1;
			break;
		case 'c':
			if(type==S_IFCHR)
				return 1;
			break;
		case 'p':
			if(type==S_IFIFO)
				return 1;
			break;
		default:
			perror("File type not valid error\n");
			exit(EXIT_FAILURE);
			break;
	}
	
	return 0;
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

int user(char* refUser,char* path)
{
	struct stat statFich;
	struct passwd* statUser;
	
	statWOError(path, &statFich);
	statUser = getpwuid(statFich.st_uid);
	if(statUser==NULL) 
	{
		perror("Name lookup error\n");
		exit(EXIT_FAILURE);
	}

	return !strcmp(refUser, statUser->pw_name);   
}
    
int group(char* refGroup,char* path)
{
	struct stat statFich;
	struct group* statGroup;
	
	statWOError(path, &statFich);
	statGroup = getgrgid(statFich.st_gid);
	if(statGroup==NULL) 
	{
		perror("Group lookup error\n");
		exit(EXIT_FAILURE);
	}

	return !strcmp(refGroup, statGroup->gr_name);
}

int atime(char* refTime, char* path)
{
	struct stat statFich;
	statWOError(char* path, struct stat *statFich)
	
	return compTime(statFich.st_atime, refTime);
}

int ctime(char* refTime, char* path)
{
	struct stat statFich;
	statWOError(char* path, struct stat *statFich)
	
	return compTime(statFich.st_ctime, refTime);
}

int mtime(char* refTime, char* path) // voir la passage des paramètres 
{
	struct stat statFich;
	statWOError(char* path, struct stat *statFich)
	
	return compTime(statFich.st_mtime, refTime);
}

int perm(char* refPerm, char* path)
{
	struct stat statFich;
	statWOError(char* path, struct stat *statFich)
	
	
}

int print()
{
	printf("Hugo suce des gros noeud")
	
	return 1;
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
		perror("Stat lookup error\n");
		exit(EXIT_FAILURE);
	}
}

int compTime(time_t reference, char* comparetTo)
{
	int parJours;
	int jours = floor ( difftime(time(), reference) / (3600*24));  //temps en jours
	
	if(comparetTo[0]=='+')
	{
		parJour=stringToInt(comparetTo+1);
		if(jours>=parJours)
			return 1;
	}
	else if(comparetTo[0]=='-')
	{
		parJour=stringToInt(comparetTo+1);
		if(jours<=parJours)
			return 1;
	}
	else
	{
		parJour=stringToInt(comparetTo);
		if(jours==parJours)
			return 1;
	}
	return 0;
}
