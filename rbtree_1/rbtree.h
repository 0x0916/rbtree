#include <stdio.h>

#define BLACK	0
#define RED	1
typedef struct _RBNode {
	int key;
	int color;
	struct _RBNode *parent, *left, *right;
} RBNode, *RBTree;

static RBNode _NIL = {0, BLACK, NULL, NULL, NULL};
#define LEAF	&_NIL

// Insert
RBNode* insert(RBNode *root, int key);

// Delete
RBNode* delete(RBNode *root, int key);

// Search
RBNode* search(RBNode* root, int key);
RBNode* iterative_search(RBNode* root, int key);

// Print
void inorder_tree_walk(RBNode* root);
