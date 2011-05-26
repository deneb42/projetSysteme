#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fnmatch.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

int stringToInt(char* string);
void statWOError(char* path, struct stat *statFich);


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

int user(char* User,char* path)
{
	struct stat statUser;
	struct passwd* statPUser;
	
	statWOError(path, &statUser);
	statPUser = getpwuid(statUser.st_uid);
	if(statPUser==NULL) 
	{
		perror("Name recuperation error\n");
		exit(EXIT_FAILURE);
	}

	return !strcmp(User, statPUser->pw_name);   
}
    
int group(char* Group,char* path)
{
	struct stat statGroup;
	struct group* statPGroup;
	
	statWOError(path, &statGroup);
	statPGroup = getgrgid(statGroup.st_gid);
	if(statPGroup==NULL) 
	{
		perror("Group recuperation error\n");
		exit(EXIT_FAILURE);
	}

	return !strcmp(Group, statPGroup->gr_name);
}


// utils ------------------------------------------------------

int stringToInt(char* string)
{
	int i;
	int stringInt=0;

	for(i=0;string[i]!='\0';i++) 
	{
		stringInt+= string[i]-'0';//manque gestion d'erreur
		stringInt*=10;
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
