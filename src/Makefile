final: main.o mm.o heap.o
	cc main.o mm.o heap.o -o final
main.o: main.c
	cc -c main.c
mm.o: mm.h mm.c
	cc -c mm.c
heap.o: heap.h heap.c
	cc -c heap.c
clean:
	rm *.o final
