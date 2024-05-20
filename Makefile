build: main.o hash.o queue.o list.o lirs_cache.o data.o
	g++ main.o hash.o queue.o list.o lirs_cache.o data.o -o programm
main.o: main.cpp hash.h list.h queue.h data.h
	g++ -c main.cpp
hash.o: hash.cpp hash.h queue.h 
	g++ -c hash.cpp
queue.o: queue.c queue.h hash.h 
	g++ -c queue.c
list.o: list.cpp list.h 
	g++ -c list.cpp
lirs_cache.o: lirs_cache.c lirs_cache.h queue.h hash.h list.h
	g++ -c lirs_cache.c
data.o: data.c data.h
	g++ -c data.c

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf programm.exe