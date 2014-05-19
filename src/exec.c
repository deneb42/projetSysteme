
void decoupe(char *ligne, char** elems)
{
	char *debut = ligne;
	int i=0;
	while(*debut)
	{
		if(!*debut && isspace(debut))
		{
			debut++;
		}
		elems[i] = debut;
		while(*debut && !isspace(*debut))
		{
			debut++;
		}
		if(*debut)
		{
			*debut = 0;
			debut++;
		}
		i++;
	}
	elems[i] = NULL;
}



char ** decoupe2(char** elems, char* sep)
{
	char ** debut = elems;
	char ** res = NULL;
	while(NULL != *debut)
	{
		if( 0 == strcmp(*debut,sep) )
		{
			res = debut + 1;
			*debut = NULL;
			return res;
		}
		debut++;
	}
	return res;
}


int exec ()
{
    char ligne [4096];
	pid_t pid;
	char **elems;
	char **res;
	char **res2;
    int fds[2];
    int returnValue; 
    
    fgets(ligne,4096,stdin);

	/*on decoupe la ligne de commande afin de recuperer les parametre*/
	decoupe(ligne,elems);
	res = decoupe2(elems,">");
	if(res == NULL)
	{
		res2 = decoupe2(elems,"|");
	}
	
	switch(fork())
	{
		case -1:
			perror ( "echec du fork");
			return -1;
		case 0:
			wait(&returnValue);
			return returnValue;
		default:
			if(res != NULL)
			{
				close(1);
				dup(open(*res,O_WRONLY|O_CREAT));
			}
			else
			{
				if(res2 != NULL)
				{
					if(pipe(fds) == -1)
					{
						perror("pipe");
						return -1;
					}
				}
				execvp(elems[0],elems);exit(2)
			}
			break;
	}
}





