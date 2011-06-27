/*  Find                        	predicat.c

By : deneb, Hugo					Last Modif : 21/06/11
_____________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fnmatch.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

#include "utils.h"

int true(char* useless, char* path)
{
	return 1;
}

int false(char* useless, char* path)
{
	return 0;
}

int name(char* pattern, char* path) // on doit retirer les repertoires d'en tete
{
	return !fnmatch(pattern, path, 0); 
	// ! needed because fnmatch return 0 if it match, and here we use 0 as false (like in boolean operation in c)
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
			perror("type given is not a valid type");
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
	struct passwd* statUser=NULL;
	
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
	struct group* statGroup=NULL;
	
	statWOError(path, &statFich);
	statGroup = getgrgid(statFich.st_gid);
	if(statGroup==NULL) 
	{
		perror("Group lookup error\n");
		exit(EXIT_FAILURE);
	}

	return !strcmp(refGroup, statGroup->gr_name);
}

int aTime(char* refTime, char* path)
{
	struct stat statFich;
	statWOError(path, &statFich);
	
	return compTime(statFich.st_atime, refTime);
}

int cTime(char* refTime, char* path)
{
	struct stat statFich;
	statWOError(path, &statFich);
	
	return compTime(statFich.st_ctime, refTime);
}

int mTime(char* refTime, char* path) // voir la passage des paramètres 
{
	struct stat statFich;
	statWOError(path, &statFich);
	
	return compTime(statFich.st_mtime, refTime);
}

int perm(char* refPerm, char* path)
{
	struct stat statFich;
	statWOError(path, &statFich);
	 // a faire
	return 0;
}
