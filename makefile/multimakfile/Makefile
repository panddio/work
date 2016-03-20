SUB_DIRS = $(shell ls -l | grep ^d | awk '{if($$9 == "gtk" || $$9 == "src") print $$9}')
#SUB_DIRS = ./src ./gtk
ROOT_DIR = $(shell pwd)

INCS_DIR := $(ROOT_DIR)/inc
SRCS_DIR := $(ROOT_DIR)/src
OBJS_DIR := $(ROOT_DIR)/obj

CUR_SRCS = $(wildcard *.c)  
CUR_OBJS = $(patsubst %.c,%.o,$(CUR_SRCS)) 

OBJS := $(wildcard $(OBJS_DIR)/*.o)
TARGET = mplayer
#BIN_TARGET = ${DIR_BIN}/${TARGET} # 目标存放在 bin目录
BIN_TARGET = ./${TARGET}  # 目标存放在当前目录

CC = gcc
INCFAG = -I$(INCS_DIR) -I$(ROOT_DIR)/gtk/inc -I$(ROOT_DIR)/src/inc
CFLAGS = `pkg-config --cflags --libs gtk+-2.0 gmodule-export-2.0`

#将以下变量导出到子shell中，本次相当于导出到子目录下的makefile中
export CC ROOT_DIR OBJS_DIR CFLAGS INCFAG

.PHONY:all
all:$(SUB_DIRS) $(CUR_OBJS) $(BIN_TARGET)

$(SUB_DIRS):ECHO
	$(MAKE) -C $@
	
ECHO:
	@echo $(SUB_DIRS)
	
#将当前目录的c文件编译为o文件，并放在指定目录中即OBJS_DIR
$(CUR_OBJS):%.o:%.c
	$(CC) -c $^ -o $(OBJS_DIR)/$@ $(INCFAG) $(CFLAGS)
	
$(BIN_TARGET):
	$(CC) $(OBJS_DIR)/*.o -o $@ $(INCFAG) $(CFLAGS)
		
.PHONY:clean
clean:
	rm ${OBJS_DIR}/* ${TARGET}
	
	