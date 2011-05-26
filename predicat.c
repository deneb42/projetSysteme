#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fnmatch.h>
#include <unistd.h>
//#include <sys/type.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

int stringToInt(char* string);


int true()
{
	return 1;
}

int false()
{
	return 0;
}

int name(char* pattern, char* name)
{
	return !fnmatch(pattern, name, 0);
}

int type(char* typeRef,char* path) // plus compliqué en réalité
{
	struct stat statFich;
	stat(path, &statFich);//manque gestion d'erreur
	
	return stringToInt(typeRef) == statFich.st_mode;
}

int uid(char* refUID,char* path)
{
	struct stat statFich;
	stat(path, &statFich);//manque gestion d'erreur
	
	return statFich.st_uid == stringToInt(refUID);
}

int gid (char* refGID,char* path)
{
	struct stat statFich;
	stat(path, &statFich);//manque gestion d'erreur

	return statFich.st_gid == stringToInt(refGID);
}

int user(char* User,char* path)
{
	struct stat statUser;
	struct passwd* statPUser;
	
	stat(path, &statUser);//manque gestion d'erreur
	statPUser = getpwuid(statUser.st_uid);

	return !strcmp(User, statPUser->pw_name);   
}
    
int group(char* Group,char* path)
{
	struct stat statGroup;
	struct group* statPGroup;
	
	stat(path, &statGroup);//manque gestion d'erreur
	statPGroup = getgrgid(statGroup.st_gid);

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
