#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define SIZE_DATE 17
#define SIZE_BUF 100


int print(char* osef, char* path)
{
   printf ("%s \n",path);
    return 1;
}

int ls(char* osef, char* path) // manque cible du lien
{
	struct stat statFich;
	struct passwd* statUser=NULL;
	struct group* statGroup=NULL;
	
	char smode[]= "----------";
	char date[SIZE_DATE];
	char linkTarget[100] = "?";
	
	if(lstat(path, &statFich)==-1); // tester le succes en lecture
	{
		printf ("     ? ");
		printf ("   ? ");
		printf ("?????????? ");
		printf ("  ? ");
		printf ("?        ");
		printf ("?        ");
		printf ("   ? ");
		printf ("???-??-?? ??:?? ");
		printf ("%s",path);
		return 1;
	}
	
	// perm autre
	if ((statFich.st_mode & S_IXOTH) != 0) smode[9]='x';
	if ((statFich.st_mode & S_IWOTH) != 0) smode[8]='w';
	if ((statFich.st_mode & S_IROTH) != 0) smode[7]='r';
	//perm group
	if ((statFich.st_mode & S_IXGRP) != 0) smode[6]='x';
	if ((statFich.st_mode & S_IWGRP) != 0) smode[5]='w';
	if ((statFich.st_mode & S_IRGRP) != 0) smode[4]='r';
	//perm user
	if ((statFich.st_mode & S_IXUSR) != 0) smode[3]='x';
	if ((statFich.st_mode & S_IWUSR) != 0) smode[2]='w';
	if ((statFich.st_mode & S_IRUSR) != 0) smode[1]='r';

	//type de fichier
	if(S_ISREG(statFich.st_mode)) smode[0]='-';
	else if(S_ISDIR(statFich.st_mode)) smode[0]='d';
	else if(S_ISLNK(statFich.st_mode)) smode[0]='l';
	else if(S_ISSOCK(statFich.st_mode)) smode[0]='s';
	else if(S_ISBLK(statFich.st_mode)) smode[0]='b';
	else if(S_ISFIFO(statFich.st_mode)) smode[0]='c';

	//permissions �tendues
	if((statFich.st_mode & S_ISUID)!=0) smode[3] = (statFich.st_mode & S_IXUSR) ? 's' : 'S';
	if((statFich.st_mode & S_ISGID)!=0) smode[6] = (statFich.st_mode & S_IXGRP) ? 's' : 'S';
	if((statFich.st_mode & S_ISVTX)!=0) smode[9] = (statFich.st_mode & S_IXOTH) ? 't' : 'T';
	
	statUser = getpwuid(statFich.st_uid);
	statGroup = getgrgid(statFich.st_gid);
	strftime(date, SIZE_DATE, "%Y-%m-%d %H:%M", localtime(&statFich.st_mtime));


	printf ("%6ld ",statFich.st_ino);
	// print("%j", (uintmax_t)(var)); // cast en le plus grand int representable et l'affiche
	printf ("%4ld ",statFich.st_blocks);
	printf ("%s ",smode);
	printf ("%3d ",statFich.st_nlink);
	if(statUser==NULL)
		printf ("%-8d ", statFich.st_uid);
	else
		printf ("%-8s ", statUser->pw_name);
	if(statGroup==NULL)
		printf ("%-8d ", statFich.st_gid);
	else
		printf ("%-8s ", statGroup->gr_name);
	printf ("%4lu ",statFich.st_size);
	printf ("%s ",date);
	printf ("%s",path);
	if(smode[0]=='l')
	{
		readlink(path, linkTarget, SIZE_BUF);
		printf("->%s", linkTarget);
	}
	printf("\n");

	return 1;
}



int exec (char* param, char* path)
{/*
    pid_t pid;
	char elem = fgets(
	//find . -exec ls {} \; system(execString);
	
	switch( pid = fork ()){
		case -1 : perror ("fork");return 0;
		case 0 : if (param[0]!= NULL)
				{
					close(1);
					printf("pas de param�tre!");
				}
				
				else  
				{ 
				
				}
		
   }

*/
return 0;
}

int prune (char* param, char* path)
{
	return 1;
}
