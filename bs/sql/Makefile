OBJ += sql.o
OBJ += sqlite3.o

FLAGS = -std=c99
CC = gcc

sql:$(OBJ)  
	$(CC) $(OBJ) -o $@ $(FLAGS) -lpthread -ldl
%.o:%.c
	$(CC) -c $^ -o $@ $(FLAGS)
.PHONY:clean
clean:
	rm sql *.o -rfv	
