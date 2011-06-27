#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#define SIZE_DATE 17


int print(char* osef, char* path)
{
   printf ("%s \n",path);
    return 1;
}

int ls(char* osef, char* path)
{
	struct stat statFich;
	stat(path, &statFich);
	char smode[]= "----------";
	char date[SIZE_DATE];
	
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
	if((statFich.st_mode & S_IFDIR) != 0) smode[0]='d'; // problème : merde a cause du 1 (premier champ du masque)
	else if((statFich.st_mode & S_IFREG) != 0) smode[0]='-';
	else if((statFich.st_mode & S_IFLNK) != 0) smode[0]='l';
	else if((statFich.st_mode & S_IFSOCK) != 0) smode[0]='s';
	else if((statFich.st_mode & S_IFBLK) != 0) smode[0]='b';
	else if((statFich.st_mode & S_IFCHR) != 0) smode[0]='c';

	//permissions étendues
	if((statFich.st_mode & S_ISUID)!=0) smode[3] = (statFich.st_mode & S_IXUSR) ? 's' : 'S';
	if((statFich.st_mode & S_ISGID)!=0) smode[6] = (statFich.st_mode & S_IXGRP) ? 's' : 'S';
	if((statFich.st_mode & S_ISVTX)!=0) smode[9] = (statFich.st_mode & S_IXOTH) ? 't' : 'T';


	// afficher nom d'util et groupe au lieu du uid gid, besoin no ino et nb block ?
	printf ("%ld ",statFich.st_ino);
	// print("%j", (uintmax_t)(var)); // cast en le plus grand int representable et l'affiche
	printf ("%2ld ",statFich.st_blocks);
	printf ("%s ",smode);
	printf ("%d ",statFich.st_nlink);
	printf ("%d ",statFich.st_uid);
	printf ("%d ",statFich.st_gid);
	printf ("%lu",statFich.st_size);
	strftime(date, SIZE_DATE, "%Y-%m-%d %H:%M", localtime(&statFich.st_mtime));
	printf ("%s ",date);
	printf ("%s\n",path);

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
					printf("pas de paramètre!");
				}
				
				else  
				{ 
				
				}
		
   }

*/
return 0;
}

int prune (char* param, char* path)
{/*
 if (depth==0) return 1;

 else */return 0;
}
