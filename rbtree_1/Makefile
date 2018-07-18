all: rbtree rbtree1

rbtree:
	gcc main.c rbtree.c  -g -o rbtree
rbtree1:
	gcc main1.c rbtree.c  -g -o rbtree1

test: all
	./rbtree
	./rbtree1

clean:
	rm -fr rbtree rbtree1 *.o
