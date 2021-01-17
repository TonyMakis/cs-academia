main: queue.o restaurant.o input.o
	gcc -o main input.o restaurant.o queue.o

queue.o: queue.c queue.h
	gcc -c queue.c

restaurant.o: restaurant.c queue.h
	gcc -c restaurant.c

input.o: input.c queue.h
	gcc -c input.c

clean:
	@echo "Cleaning up..."
	rm -rvf *.o main