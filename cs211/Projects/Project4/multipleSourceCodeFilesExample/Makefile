max3: max3a.o max3b.o
	gcc -o max3 max3a.o max3b.o

max3a.o: max3a.c max3.h
	gcc -c max3a.c

max3b.o: max3b.c max3.h
	gcc -c max3b.c

clean:
	@echo "Cleaning up..."
	rm -rvf *.o max3