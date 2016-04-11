INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib

FLAGS = -Wall
CC = g++                                  # change to gcc if using C
CFLAGS = $(FLAGS) $(INCLUDE)
LIBS =  -lGL -lGLU -lglut

All: simple

simple: simple.o
	    $(CC) simple.o -o simple $(LIBS)

clean:
	        rm simple
		    rm *.o

#g++ simple.cpp -o simple -lGL -lGLU -lglut

