
#ifndef PREDICAT_H
#define PREDICAT_H

int true();
int false();
int name(char* pattern, char* path);
int type(char* refType,char* path);
int uid(char* refUID,char* path);
int gid (char* refGID,char* path);
int user(char* User,char* path);
int group(char* Group,char* path);

#endif
