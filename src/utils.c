/*  Find                        	utils.c

By : deneb							Last Modif : 27/06/11
_____________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>

#include "utils.h"


int stringToInt(char* string)
{// parse a string into an integer. must be positive integer

	int i;
	int intValue=0;

	for(i=0;string[i]!='\0';i++) 
	{
		if((intValue*10 + string[i]-'0') < INT_MAX)
		{
			intValue*= 10;
			intValue+= string[i]-'0'; // - '0' trasform the ASCII value to int value
		}
		else
		{
			printf("> error : %s must be a integer", string);
			return -1;
		}
	}
	
	return intValue;
}

int compTime(time_t reference, char* comparetTo)
{// return true if the reference and the string are same (or less, or more) with a day precision

	int parJours;
	int jours = ((int)difftime(time(NULL), reference) / (3600*24));  //time in days
	
	if(comparetTo[0]=='+')
	{
		parJours=stringToInt(comparetTo+1);
		if(parJour<0)// gestion erreur
			return -1;
		if(jours>=parJours)
			return 1;
	}
	else if(comparetTo[0]=='-')
	{
		parJours=stringToInt(comparetTo+1);
		if(parJour<0)//gestion erreur
			return -1;
		if(jours<=parJours)
			return 1;
	}
	else
	{
		parJours=stringToInt(comparetTo);
		if(parJour<0)//gestion erreur
			return -1;
		if(jours==parJours)
			return 1;
	}
	return 0;
}
