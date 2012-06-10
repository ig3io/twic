all: twic

twic: twic.c cJSON.o twic.h
	gcc -o twic twic.c `curl-config --libs` cJSON.o -lm

cJSON.o: cJSON.c
	gcc -c -o cJSON.o cJSON.c

clean:
	rm twic
	rm *.o
	rm *.obj

