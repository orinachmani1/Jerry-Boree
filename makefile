CC=gcc

OBJ = JerryBoreeMain.o LinkedList.o KeyValuePair.o HashTable.o Jerry.o MultiValueHashTable.o

%.o: %.c
	$(CC) -c -o $@ $<

JerryBoree: $(OBJ)
	$(CC) -o $@ $^
	
clean:
	rm *.o
