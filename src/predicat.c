/*  Find                        	predicat.c

By : deneb, Hugo					Last Modif : 27/06/11
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


int name(char* pattern, char* path)
{
	char* name = strrchr(path, '/');
	
	if(name!=NULL)
		return fnmatch(pattern, name+1, 0)==0; 
	else
		return fnmatch(pattern, path, 0)==0; 
}


int type(char* refType,char* path)
{
	struct stat statFich;
	int type;
	
	if(lstat(path, &statFich)==-1)
	{
		printf("> error : stat lookup failure : %s \n", path);
		return -1;
	}
	type = statFich.st_mode & S_IFMT;
	
	
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
			printf("> error : type %c is not valid\n", refType[0]);
			return -1;
	}
	
	return 0;
}


int uid(char* refUID,char* path)
{
	struct stat statFich;
	
	if(lstat(path, &statFich)==-1)
	{
		printf("> error : stat lookup failure : %s \n", path);
		return -1;
	}

	return statFich.st_uid == stringToInt(refUID);
}


int gid (char* refGID,char* path)
{
	struct stat statFich;
	
	if(lstat(path, &statFich)==-1)
	{
		printf("> error : stat lookup failure : %s \n", path);
		return -1;
	}

	return statFich.st_gid == stringToInt(refGID);
}


int user(char* refUser,char* path)
{
	struct stat statFich;
	struct passwd* statUser=NULL;
	
	if(lstat(path, &statFich)==-1)
	{
		printf("> error : stat lookup failure : %s \n", path);
		return -1;
	}
	
	statUser = getpwuid(statFich.st_uid);
	if(statUser==NULL) 
	{
		printf("> error : username lookup failure : %s\n", path);
		return -1;
	}

	return strcmp(refUser, statUser->pw_name)==0;   
}

    
int group(char* refGroup,char* path)
{
	struct stat statFich;
	struct group* statGroup=NULL;
	
	if(lstat(path, &statFich)==-1)
	{
		printf("> error : stat lookup failure : %s \n", path);
		return -1;
	}
	
	statGroup = getgrgid(statFich.st_gid);
	if(statGroup==NULL) 
	{
		printf("> error : group lookup failure : %s\n", path);
		return -1;
	}

	return strcmp(refGroup, statGroup->gr_name)==0;
}


int aTime(char* refTime, char* path)
{
	struct stat statFich;
	
	if(lstat(path, &statFich)==-1)
	{
		printf("> error : stat lookup failure : %s \n", path);
		return -1;
	}
	
	return compTime(statFich.st_atime, refTime);
}


int cTime(char* refTime, char* path)
{
	struct stat statFich;
	
	if(lstat(path, &statFich)==-1)
	{
		printf("> error : stat lookup failure : %s \n", path);
		return -1;
	}
	
	return compTime(statFich.st_ctime, refTime);
}


int mTime(char* refTime, char* path)
{
	struct stat statFich;
	
	if(lstat(path, &statFich)==-1)
	{
		printf("> error : stat lookup failure : %s \n", path);
		return -1;
	}
	
	return compTime(statFich.st_mtime, refTime);
}


int perm(char* refPerm, char* path)
{
	struct stat statFich;
	
	if(lstat(path, &statFich)==-1)
	{
		printf("> error : stat lookup failure : %s \n", path);
		return -1;
	}
	 // a faire
	return 0;
}
