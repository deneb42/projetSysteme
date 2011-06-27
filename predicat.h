/*  Find					predicat.h					By : deneb, Hugo */

#ifndef PREDICAT_H
#define PREDICAT_H

int true(char* osef, char* path);
int false(char* osef, char* path);
int name(char* pattern, char* path);
int type(char* refType,char* path);
int uid(char* refUID,char* path);
int gid (char* refGID,char* path);
int user(char* refUser,char* path);
int group(char* refGroup,char* path);
int aTime(char* refTime, char* path);
int cTime(char* refTime, char* path);
int mTime(char* refTime, char* path);
int perm(char* refPerm, char* path);

int print();

#endif
