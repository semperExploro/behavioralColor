CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS) 

mindHive: main.o Category.o
	$(CC) -o mindHive main.o Category.o -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic $(CFLAGS)

main.o: Category.o
	$(CC) -c main.cpp $(CFLAGS)

Category.o: Category.h Category.cpp
	$(CC) -c Category.cpp $(CFLAGS)



.PHONY: clean all
clean:
	rm -f *.o 