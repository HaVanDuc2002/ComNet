SRC:= $(wildcard server/*.c)
OBJ:= $(patsubst %.c, %.o, $(SRC))

servers: $(OBJ)
	gcc $^ -lpthread -o $@ 

client:
	gcc clients.c -lpthread -o clients

clean:
	rm *.o server/*.o clients servers