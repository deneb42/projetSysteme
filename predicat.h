
#ifndef PREDICAT_H
#define PREDICAT_H

#include <unistd.h>
#include <sys/stat.h>

int true();
int false();
int name(char* pattern, char* path);
int type(char* refType,char* path);
int uid(char* refUID,char* path);
int gid (char* refGID,char* path);
int user(char* User,char* path);
int group(char* Group,char* path);

int stringToInt(char* string);
void statWOError(char* path, struct stat *statFich);

#endif
