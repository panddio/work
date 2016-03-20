OBJ += table_cgi.o
OBJ += sqlite3.o

FLAGS = -Wall -std=c99
CC = gcc

_table.cgi:$(OBJ)  
	$(CC) $(OBJ) -o $@ $(FLAGS) -lpthread -ldl
%.o:%.c
	$(CC) -c $^ -o $@ $(FLAGS)
.PHONY:clean
clean:
	rm _table.cgi *.o -rfv	
