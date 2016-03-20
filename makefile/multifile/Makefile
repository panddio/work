all:sum test
.PHONY:all
sum:sum.o
	gcc -o sum sum.o
sum.o:sum.c
	gcc -o sum.o -c sum.c
source=test.c mymath.c
object=test.o
#.SECONDARY:sec
test:test.c mymath.c

.PHONY:clean cleanobj cleanexe cleanall
clean:
	rm *.o test sum
cleanall:cleanobj cleanexe

cleanobj:
	rm *.o
cleanexe:
	rm test sum

