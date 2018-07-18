#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "rbtree.h"

static RBTree tree;
static int nnodes = 100;
static int perf_loops = 1000;
static int *nodes = NULL;

static unsigned  seed;
static void init() {
	int i;

	tree.root = LEAF;
	tree.nil = LEAF;
	srand(seed++);
	for (i = 0; i < nnodes; i++) {
		nodes[i] = rand()%1000 + 1;
	}
}

int main(int argc, char **argv)
{
	int i,j;

	seed = time(NULL);
	nodes = calloc(nnodes, sizeof(*nodes));
	if (!nodes) {
		printf("calloc failed: no memory\n");
		return 1;
	}

	for (i = 0; i < perf_loops; i++) {
		printf("############### %d\n", i);
		init();
		for(j = 0; j < nnodes; j++) {
//			printf("insert: %d\n", nodes[j]);
			insert(&tree, nodes[j]);
		}
		inorder_tree_walk(&tree);
		printf("\n");
		for(j = 0; j < nnodes; j++) {
//			printf("delete: %d\n", nodes[j]);
			delete(&tree, nodes[j]);
		}
	}
	return 0;
}

