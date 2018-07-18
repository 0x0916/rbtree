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

void test3() {
	root = NULL;
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

void test4() 
{
	root = NULL;
	printf("\n/////////////////////////\n");
	myinsert(212);
	myinsert(334);
	myinsert(432);
	myinsert(331);
	myinsert(263);
	myinsert(506);
	myinsert(8);
	myinsert(570);
	myinsert(187);
	myinsert(892);
	
	mydelete(212);
	mydelete(334);
	mydelete(432);
	mydelete(331);
	mydelete(263);
	mydelete(506);
	mydelete(8);
	mydelete(570);
	mydelete(187);
	mydelete(892);
}

int main(int argc, char **argv)
{
	test1();
	test2();
	test3();
	test4();
	return 0;
}
