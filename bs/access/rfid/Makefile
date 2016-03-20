OBJ += main.o
OBJ += sqlite3.o
OBJ += uart_init.o
 
FLAGS = -Wall
CC = arm-linux-gcc

demo:$(OBJ)  
	$(CC) $(OBJ) -o $@ $(FLAGS) -lpthread -ldl -std=c99
	rm *.o
%.o:%.c
	$(CC) -c $^ -o $@ $(FLAGS) -std=c99
.PHONY:clean
clean:
	rm demo *.o -rfv	
