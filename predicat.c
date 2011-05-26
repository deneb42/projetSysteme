#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fnmatch.h>
#include <unistd.h>
#include <sys/type.h>
#include <sys/stat.h>
#include <pwd.h>

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
	struct stat statFich;
	stat(path, &statFich);//manque gestion d'erreur

	return !fnmatch(pattern, statFich.name, 0);
}

int type(char* typeRef,char* path)
{
	struct stat statFich;
	stat(path, &statFich);//manque gestion d'erreur
	
	return !strcmp(typeRef, statFich.type);
}

int uid(char* refUID,char* path)
{
	struct stat statFich;
	stat(path, &statFich);//manque gestion d'erreur
	
	return stat.uid_t == stringToInt(refUID);
}

int gid (char* refGID,char* path)
{
	struct stat statFich;
	stat(path, &statFich);//manque gestion d'erreur

	return stat.gid_t == stringToInt(refGID);
}

int user(char* User,char* path)
{
	struct stat statUser;
	struct passwd statPUser;
	
	stat(path, statUser);//manque gestion d'erreur
	getpwuid(statUser.uid_t, &statPUser);

	return !strcmp(User, statPUser.pw_name);   
}
    
int group(char* Group,char* path)
{
	struct stat statGroup;
	struct group statPGroup;
	
	stat(path, statGroup);//manque gestion d'erreur
	getgrnam(statGroup.gid_t, &statPGroup);

	return !strcmp(Group, statPGroup.gr_name);
}


// utils ------------------------------------------------------

int stringToInt(char* string)
{
	int i;
	int stringInt=0;

	for(i=0;string[i]!='\0';i++) 
	{
		stringInt+= string[i]-'0';//manque gestion d'erreur
		strinInt*=10;
	}
	
	return stringInt;
}
