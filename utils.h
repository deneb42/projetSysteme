/*  Find					utils.h					By : deneb */

#ifndef UTILS_H
#define UTILS_H

#include <sys/stat.h>

void parcours(char *path, int minDepth, int maxDepth, int tab[], char* param[], int nbParam);
void parcours_recur(char *path, int depth, int minDepth, int maxDepth, int tab[], char* param[], int nbParam);
int process(char *chemin, int tab[], char* param[], int nbParam);
int stringToInt(char* string);
void statWOError(char* path, struct stat *statFich);
int compTime(time_t reference, char* comparetTo);

#endif
