/*  Find					utils.h					By : deneb */

#ifndef UTILS_H
#define UTILS_H

#include <sys/stat.h>

int stringToInt(char* string);
void statWOError(char* path, struct stat *statFich);
int compTime(time_t reference, char* comparetTo);

#endif
