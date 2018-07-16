#include "rbtree.h"


RBTree tree;


void myinsert(int value) {
	insert(&tree, value);
	printf("insert %d\n", value);
	printf("inorder walk:");
	inorder_tree_walk(&tree);
	printf("\n-------------------------\n");
}

void mydelete(int value) {
	delete(&tree, value);
	printf("delete %d\n", value);
	printf("inorder walk:");
	inorder_tree_walk(&tree);
	printf("\n-------------------------\n");
}

void test1() {
	tree.root = LEAF;
	tree.nil = LEAF;

	printf("\n/////////////////////////\n");
	myinsert(1);
	myinsert(5);
	myinsert(15);
	myinsert(20);
	myinsert(25);
	myinsert(9);
	myinsert(10);
	myinsert(18);
	myinsert(29);
	myinsert(100);
	myinsert(90);

	mydelete(9);
	mydelete(90);
}

void test2() {
	tree.root = LEAF;
	tree.nil = LEAF;

	printf("\n/////////////////////////\n");
	myinsert(1);
	myinsert(2);
	myinsert(3);
	myinsert(4);
	myinsert(5);
	myinsert(6);
	myinsert(7);
	myinsert(8);

	mydelete(7);
	mydelete(4);
	mydelete(1);
	mydelete(5);
	mydelete(2);
	mydelete(3);
	mydelete(6);
	mydelete(8);
}

void test3() {
	tree.root = LEAF;
	tree.nil = LEAF;
	printf("\n/////////////////////////\n");
	myinsert(10);
	myinsert(85);
	myinsert(15);
	myinsert(70);
	myinsert(20);
	myinsert(60);
	myinsert(30);
	myinsert(50);
	myinsert(65);
	myinsert(80);
	myinsert(90);
	myinsert(40);
	myinsert(5);
	myinsert(55);
	
	mydelete(30);
	mydelete(65);
}

int main(int argc, char **argv)
{
	test1();
	test2();
	test3();

	return 0;
}

