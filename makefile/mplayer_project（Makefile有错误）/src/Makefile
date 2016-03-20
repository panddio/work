#Makfefile for src direction

SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "inc") print $$9}')
#INCFAG += -I./inc

#以下同根目录下的makefile的相同代码的解释
CUR_SRCS=${wildcard *.c}
CUR_OBJS=${patsubst %.c, %.o, $(CUR_SRCS)}

all:$(SUBDIRS) $(CUR_OBJS)

$(SUBDIRS):ECHO
	$(MAKE) -C $@
	
$(CUR_OBJS):%.o:%.c
	$(CC) -c $< -o $(OBJS_DIR)/$@ $(INCFAG) $(CFLAGS)
	
ECHO:
	@echo $(SUBDIRS)