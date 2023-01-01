.PHONY: all clean

all: test

test: quadTree.o test.o
	@echo "-------------------------"
	@echo "building quad tree..."
	gcc -g -o test quadTree.o test.o
	@echo "building quad tree done."

quadTree.o: quadTree.c
	gcc -o quadTree.o -c quadTree.c

test.o: test.c
	gcc -o test.o -c test.c

cleanobj:
	-rm *.o

clean:
	-rm *.o
	-rm test