SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')

all:
	echo $(SUBDIRS)
