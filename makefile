#|  Makefile for the System project |
#|                                  |
#|  by :deneb                       |
#|  last modif : 26/05/11           |
#/__________________________________/


LIBPATH = 
LIBRARY = 
CFLAGS = -Wall
LDFALGS = $(LIBPATH) $(LIBRARY)
GCC=gcc

# Name of the files (more .o)
OBJS = utils.o predicat.o main.o
# Path where the bin will be
PATH_PGM = ./
# Name of the bin
PGM = testSystem


# For the generic utilisation, 
# DO NOT TOUCH ANYTHING UNDER THIS LINE !!!
# ___________________________________________

all : $(OBJS) 
	$(GCC) -o $(PATH_PGM)$(PGM) $(OBJS) $(LDFALGS) 

# generic method for all the .o
%.o : %.c
	$(GCC) $(CFLAGS) $(INC_PATH) -c $< 

run :
	$(PATH_PGM)$(PGM)

clean :
	-rm *.o *~ $(PATH_PGM)$(PGM)
