lab6: project.o matmult.o
	gcc project.o matmult.o -o lab6 -lpthread

project.o: project.c
	gcc -c project.c

matmult.o: matmult.c
	gcc -c matmult.c

clean:
	rm -f *.o lab6
