P = guiding
CFLAGS = -g -Wall
LDLIBS = -ltsk

guiding : guiding.o guid.o
	g++ -o $(P) guiding.o guid.o $(CFLAGS) $(LDLIBS)

guiding.o : guiding.cpp guid.h
	g++ -c guiding.cpp $(CFLAGS)

guid.o : guid.cpp guid.h
	g++ -c guid.cpp $(CFLAGS)

clean :
	rm *.o 

