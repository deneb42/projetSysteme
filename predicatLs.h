#ifndef PREDICATLS_H
#define PREDICATLS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>


int print(char* osef, char*path);
void print_rights(struct stat statFich);
int ls(char* osef, char* path);
int exec(char* osef, char*path);
int prune(char* osef, char*path);

#endif
