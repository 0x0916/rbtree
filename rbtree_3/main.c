#include <stdio.h>
#include <stdlib.h>
#include "rbtree_augmented.h"

#define NODES	100
#define PERF_LOOPS	100000
#define CHECK_LOOPS	100

struct test_node {
	struct rb_node rb;
	int key;

	int val;
	int augmented;
};

static struct rb_root root = RB_ROOT;
static struct test_node nodes[NODES];

static void insert(struct test_node *node, struct rb_root *root)
{
	struct rb_node **new = &(root->rb_node), *parent = NULL;

	int key = node->key;


	while(*new) {
		parent = *new;
		if (key < rb_entry(parent, struct test_node, rb)->key)
			new = &parent->rb_left;
		else
			new = &parent->rb_right;
	}

	rb_link_node(&node->rb, parent, new);
	rb_insert_color(&node->rb, root);
}

void erase(struct test_node *node, struct rb_root *root)
{
    rb_erase(&node->rb, root);
}

void print_rbtree(struct rb_root *tree)
{
	struct rb_node *node;

	for (node = rb_first(tree); node; node = rb_next(node))
		printf("%d ", rb_entry(node, struct test_node, rb)->key);
	printf("\n");
}

static unsigned  seed;

static void init() {
	int i;

	srand(seed++);
	for (i = 0; i < NODES; i++) {
		nodes[i].key = rand()%1000 + 1;
		nodes[i].val = rand()%1000 + 1;
	}
}

int main(int argc, char *argv[])
{
	int i, j;
	seed = time(NULL);

	for (i = 0; i < PERF_LOOPS; i++) {
		printf("############### %d\n", i);
		init();
		for(j = 0; j < NODES; j++) {
			insert(nodes + j, &root);
		}
		print_rbtree(&root);
		for(j = 0; j < NODES; j++) {
			erase(nodes + j, &root);
		}
	}
	return 0;
}

