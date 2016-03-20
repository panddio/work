CC := arm-linux-gcc
SRC := $(shell ls *.c)
#OBJ := $(patsubst %.c,%.o,$(SRC))
OBJ := $(SRC:%.c=%.o)
TAG := access.cgi

$(TAG):$(OBJ)
	$(CC) -o $@ $^ -lpthread -ldl -Wall -std=c99
%.o:%.c
	$(CC) -o $@ -c $< -std=c99


.PHONY:clean
clean:
	rm -rf $(TAG) *.o *~
