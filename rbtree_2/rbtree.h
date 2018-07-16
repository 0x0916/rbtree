#include <stdio.h>

#define BLACK	0
#define RED	1

typedef struct _RBNode {
	int key;
	int color;
	struct _RBNode *parent, *left, *right;
} RBNode ;

typedef struct {
	RBNode *root;
	RBNode *nil;
} RBTree;

static RBNode _NIL = {0, BLACK, NULL, NULL, NULL};
#define LEAF	&_NIL

// Insert
void insert(RBTree *tree, int key);

// Delete
void delete(RBTree *tree, int key);

// Search
RBNode* iterative_search(RBTree *tree, int key);

// Print
void inorder_tree_walk(RBTree* tree);
