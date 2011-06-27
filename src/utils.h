/*  Find					utils.h					By : deneb */

#ifndef UTILS_H
#define UTILS_H

	int stringToInt(char* string); // parse a string into an integer. must be positive integer
	int compTime(time_t reference, char* comparetTo); // return true if the reference and the string are same (or less, or more) with a day precision

#endif
