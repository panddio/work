CC := gcc

SRC := $(shell ls *.c)
#OBJ := $(patsubst %.c,%.o,$(SRC))
OBJ := $(SRC:%.c=%.o)
TAG := sql_cgi.cgi
CFLAGS = -Wall -lpthread -ldl

$(TAG):$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY:clean
clean:
	rm -f $(TAG) *.o *~