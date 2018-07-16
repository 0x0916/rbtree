#include "rbtree.h"


RBNode *root = NULL;


void myinsert(int value) {
	root = insert(root, value);
	printf("insert %d\n", value);
	printf("inorder walk:");
	inorder_tree_walk(root);
	printf("\n-------------------------\n");
}

void mydelete(int value) {
	root = delete(root, value);
	printf("delete %d\n", value);
	printf("inorder walk:");
	inorder_tree_walk(root);
	printf("\n-------------------------\n");
}

void test1() {
	root = NULL;
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
	root = NULL;
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

int main(int argc, char **argv)
{
	test1();
	test2();

	return 0;
}
