#Makfefile for gtk direction

SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "inc" && $$9 != "image") print $$9}')
#CUR_DIR = $(shell pwd)
#INCFAG += -I$(CUR_DIR)/inc
#INCFAG += -I./inc

#以下同根目录下的makefile的相同代码的解释
CUR_SRCS=${wildcard *.c}
CUR_OBJS=${patsubst %.c, %.o, $(CUR_SRCS)}

all:$(SUBDIRS) $(CUR_OBJS)

$(SUBDIRS):ECHO
	$(MAKE) -C $@
	
$(CUR_OBJS):%.o:%.c
	$(CC) -c $^ -o $(OBJS_DIR)/$@ $(CFLAGS) $(INCFAG)
	
ECHO:
	@echo $(SUBDIRS)