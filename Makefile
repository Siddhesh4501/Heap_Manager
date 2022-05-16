final: main.o mm.o
	cc main.o mm.o -o final
main.o: main.c
	cc -c main.c
mm.o: mm.h mm.c
	cc -c mm.c
clean:
	rm *.o final
