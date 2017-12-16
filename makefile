all : main.o compress.o decompress.o header.o
	gcc -Wall main.o compress.o decompress.o header.o -o huff; make clean;

debug : main.o compress.o decompress.o header.o
	gcc -Wall main.c compress.c decompress.c header.c -O0 -g -o huff

main.o : main.c compress.c decompress.c header.c
	gcc -c main.c -o main.o

compress.o : header.o
	gcc -c compress.c -o compress.o

decompress.o : header.o
	gcc -c decompress.c -o decompress.o

header.o :
	gcc -c header.c -o header.o

clean:
	rm -rf *.o

mrproper: clean
	rm -rf main
