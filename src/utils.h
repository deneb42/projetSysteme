/*  Find					utils.h					By : deneb */

#ifndef UTILS_H
#define UTILS_H

	#include <sys/stat.h>

	int stringToInt(char* string); // parse a string into an integer. must be positive integer
	void statWOError(char* path, struct stat *statFich); // buffer func whitch handle errors during the call of stat()
	int compTime(time_t reference, char* comparetTo); // return true if the reference and the string are same (or less, or more) with a day precision

#endif
