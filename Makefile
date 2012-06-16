all: twic

twic: twic.c cJSON.o twic.h
	gcc -o twic twic.c `curl-config --libs` cJSON.o -lm -Wall

cJSON.o: cJSON.c
	gcc -c -o cJSON.o cJSON.c -Wall

clean:
	rm twic
	rm *.o
	rm *.obj

