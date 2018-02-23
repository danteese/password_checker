passcheck : passcheck.o
	gcc -o passcheck passcheck.o

passcheck.o: passcheck.c
	gcc -c passcheck.c

clean:
	rm *.o
