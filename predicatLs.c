/*  Find                        	predicatLs.c

By : Hugo, deneb					Last Modif : 21/06/11
_____________________________________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>


int print(char* osef, char*path)
{
    printf ("nom complet du fichier : %s \n",path);
    return 1;
}

/*void            print_rights(struct stat statFich)
{
  ((statFich.st_mode & S_IFDIR) != 0) ? putstr("d") : putstr("-");
  ((statFich.st_mode & S_IRUSR) != 0) ? putstr("r") : putstr("-");
  ((statFich.st_mode & S_IWUSR) != 0) ? putstr("w") : putstr("-");
  ((statFich.st_mode & S_IXUSR) != 0) ? putstr("x") : putstr("-");
  ((statFich.st_mode & S_IRGRP) != 0) ? putstr("r") : putstr("-");
  ((statFich.st_mode & S_IWGRP) != 0) ? putstr("w") : putstr("-");
  ((statFich.st_mode & S_IXGRP) != 0) ? putstr("x") : putstr("-");
  ((statFich.st_mode & S_IROTH) != 0) ? putstr("r") : putstr("-");
  ((statFich.st_mode & S_IWOTH) != 0) ? putstr("w") : putstr("-");
  ((statFich.st_mode & S_IXOTH) != 0) ? putstr("x") : putstr("-");
}*/

int ls(char* osef, char* path)
{
     struct stat    statFich;
     stat(path, &statFich);

    char* ptr;
    ptr= malloc(17);
    printf ("Numéro d'inode,Nombre de blocs,type de fichier + permission,nb liens matériels,ID propriétaire,ID groupe,Taille,date de derniere modification,nom complet du fichier\n");
    printf ("%ld ",statFich.st_ino);
    printf ("%ld ",statFich.st_blocks);
    printf ("%d ",statFich.st_mode);/* print_rights(statFich);*/
    printf ("%d ",statFich.st_nlink);
    printf ("%d ",statFich.st_uid);
    printf ("%d ",statFich.st_gid);
    printf ("%lu octets ",statFich.st_size);
    strftime(ptr,17,"%Y-%m-%d %H:%M",localtime(&statFich.st_mtime));
    printf ("%s ",ptr);
    printf ("%s\n",path);
    free(ptr);
    return 1;
}

int exec(char* osef, char*path)
{
	return 1;
}

int prune(char* osef, char*path)
{
	return 1;
}
