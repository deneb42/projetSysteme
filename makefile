#|  Makefile for the System project |
#|                                  |
#|  by :deneb                       |
#|  last modif : 21/06/11           |
#/__________________________________/


INC_PATH =
LIB_PATH = 
LIBRARY = 
CFLAGS = -Wall -g -D_FILE_OFFSET_BITS=64
LDFALGS = $(LIB_PATH) $(LIBRARY)
GCC=gcc

# Name of the files (more .o)
OBJS = utils.o param.o predicat.o predicatLs.o main.o
# Path where the bin will be
PGM_PATH = ./
# Name of the bin
PGM = find


# For the generic utilisation, 
# DO NOT TOUCH ANYTHING UNDER THIS LINE !!!
# ___________________________________________

# $(OBJS: =.o ) 
all : $(OBJS) 
	$(GCC) -g -o $(PGM_PATH)$(PGM) $(OBJS) $(LDFALGS) 

# generic method for all the .o
%.o : %.c
	$(GCC) $(CFLAGS) $(INC_PATH) -c $< 

run :
	$(PGM_PATH)$(PGM)

clean :
	-rm *.o *~ $(PGM_PATH)$(PGM)
