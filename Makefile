all: List

List: main.o dbl_linked_list.o dump.o
	g++ main.o dbl_linked_list.o dump.o -o List

main.o: main.cpp
	g++ -c main.cpp

dbl_linked_list.o: sourse\\dbl_linked_list.cpp
	g++ -c         sourse\\dbl_linked_list.cpp

dump.o:    sourse\\dump.cpp
	g++ -c sourse\\dump.cpp

clean:
	rm -rf *.o hello
