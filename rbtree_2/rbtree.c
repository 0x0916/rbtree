#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rbtree.h"

RBNode* parent(RBNode *n) {
	return n->parent;
}

RBNode* grandparent(RBNode *n) {
	RBNode *p = parent(n);
	if (p == NULL)
		return NULL;// no parent means no grandparent
	return parent(p);
}

RBNode* slibing(RBNode *n) {
	RBNode *p = parent(n);
	if (p == NULL)
		return NULL;// no parent means no slibing 
	if (n == p->left)
		return p->right;
	else
		return p->left;
}

RBNode* uncle(RBNode* n) {
	RBNode *p = parent(n);
	RBNode *g = grandparent(n);

	if (g == NULL)
		return NULL; // No grandparent means no uncle

	return slibing(p);
}

void rotate_left(RBTree *tree, RBNode* x) {
	RBNode* y = x->right;

	x->right = y->left;
	if (y->left != tree->nil) {
		y->left->parent = x;
	}
	y->parent = x->parent;

	if (parent(x) == tree->nil) {
		tree->root = y;
	}else {
		if (x == parent(x)->left)
			parent(x)->left = y;
		else
			parent(x)->right = y;
	}
	y->left = x;
	x->parent = y;
}

void rotate_right(RBTree * tree, RBNode* x) {
	RBNode* y = x->left;

	x->left = y->right;
	if (y->right != tree->nil) {
		y->right->parent = x;
	}
	y->parent = x->parent;

	if (parent(x) == tree->nil) {
		tree->root = y;
	}else {
		if (x == parent(x)->right)
			parent(x)->right = y;
		else
			parent(x)->left = y;
	}
	y->right = x;
	x->parent = y;
}

RBNode* minimum(RBTree *tree, RBNode* n) {
	while (n->left != tree->nil)
		n = n->left;
	return n;
}

RBNode* maximum(RBTree *tree, RBNode* n) {
	while (n->right != tree->nil)
		n = n->right;
	return n;
}

RBNode* successor(RBTree *tree, RBNode* x) {
	RBNode* y;
	if (x->right != tree->nil)
		return minimum(tree, x->right);
	y = parent(x);
	while (y != tree->nil && x == y->right) {
		x = y;
		y = parent(y);
	}
	return y;
}

RBNode* predecessor(RBTree *tree, RBNode* x) {
	RBNode* y;
	if (x->left != tree->nil)
		return maximum(tree, x->left);
	y = parent(x);
	while (y != tree->nil && x == y->left) {
		x = y;
		y = parent(y);
	}
	return y;
}

void	rb_insert_fixup(RBTree *tree, RBNode *z) {
	RBNode *y;
	while (parent(z)->color == RED) {
		if (parent(z) == grandparent(z)->left) {
			y = grandparent(z)->right; // y为叔叔结点
			if (y->color == RED) { // 红父红叔
				parent(z)->color = BLACK;
				y->color = BLACK;
				grandparent(z)->color = RED;
				z = parent(parent(z));
			}else { //红父，黑叔
				if (z == parent(z)->right) { //  情形2 , 转换为情形1
					z = parent(z);
					rotate_left(tree, z);
				}
				// 情形1
				parent(z)->color = BLACK;
				grandparent(z)->color = RED;
				rotate_right(tree, grandparent(z));
			}
		}else {
			y = grandparent(z)->left; // y为叔叔结点
			if (y->color == RED) { // 红父红叔
				parent(z)->color = BLACK;
				y->color = BLACK;
				grandparent(z)->color = RED;
				z = parent(parent(z));
			}else { //红父，黑叔
				if (z == parent(z)->left) { //情形4 , 转换为情形3
					z = parent(z);
					rotate_right(tree, z);
				}
				//情形3
				parent(z)->color = BLACK;
				grandparent(z)->color = RED;
				rotate_left(tree, grandparent(z));
			}
		}
	}
	// 父节点是黑色，不进行处理

	// 当树为空时，插入第一个结点，需要将根节点染成黑色。
	tree->root->color = BLACK;
}

// Insert a new node to RBTree
void insert_node(RBTree *tree, RBNode *z)
{
	RBNode *y = tree->nil;
	RBNode *x = tree->root;

	while (x != tree->nil) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	} //  寻找y，y为新插入结点z的父结点
	z->parent = y;

	// 插入到合适的位置
	if (y == tree->nil) {
		tree->root = z;
	}else {
		if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
	}

	z->left = tree->nil;
	z->right = tree->nil;
	z->color = RED;

	rb_insert_fixup(tree, z);
}

void rb_delete_fixup(RBTree *tree, RBNode* x)
{
	RBNode *w;

	while (x != tree->root && x->color == BLACK) { //  真正删除结点为黑色
		if (x == parent(x)->left) {
			w = parent(x)->right; //w为兄弟结点
			if (w->color == RED) { // 红兄
				w->color = BLACK;
				parent(x)->color = RED;
				rotate_left(tree, parent(x));
				w = parent(x)->right; // 变成黑兄情况
			}
			//兄弟结点为黑色
			if (w->left->color == BLACK && w->right->color == BLACK) {
				// 双侄子为黑色
				w->color = RED;
				x = parent(x);
			}else{
				if (w->right->color == BLACK) { //情形4，转换为情形3
					w->left->color = BLACK;
					w->color = RED;
					rotate_right(tree, w);
					w = parent(x)->right;
				}
				// 情形3
				w->color = parent(x)->color;
				parent(x)->color = BLACK;
				w->right->color = BLACK;
				rotate_left(tree, parent(x));
				x = tree->root; //为了结束循环
			}
		}else {
			w = parent(x)->left; //w为兄弟结点
			if (w->color == RED) { // 红兄
				w->color = BLACK;
				parent(x)->color = RED;
				rotate_right(tree, parent(x));
				w = parent(x)->left; // 变成黑兄情况
			}
			//兄弟结点为黑色
			if (w->left->color == BLACK && w->right->color == BLACK) {
				// 双侄子为黑色
				w->color = RED;
				x = parent(x);
			}else{
				if (w->left->color == BLACK) { //情形2，转换为情形1
					w->right->color = BLACK;
					w->color = RED;
					rotate_left(tree, w);
					w = parent(x)->left;
				}

				// 情形1
				w->color = parent(x)->color;
				parent(x)->color = BLACK;
				w->left->color = BLACK;
				rotate_right(tree, parent(x));
				x = tree->root; //为了结束循环
			}
		}
	}

	x->color = BLACK;
}

void delete_node(RBTree *tree , RBNode *z) {
	RBNode *y, *x;
	// y是真正要删除的结点
	if (z->left == tree->nil || z->right == tree->nil)
		y = z;
	else
		//y = successor(tree, z);
		y = predecessor(tree, z);

	// x是y的子结点
	if (y->left != tree->nil)
		x = y->left;
	else
		x = y->right;

	// 删除y
	x->parent = y->parent;
	if (parent(y) == tree->nil) {
		tree->root = x;
	}else {
		if(y == parent(y)->left)
			parent(y)->left = x;
		else
			parent(y)->right = x;
	}

	if (y != z)
		z->key = y->key;

	if (y->color == BLACK)
		rb_delete_fixup(tree, x);

	free(y); //删除结点为红色，直接删除即可
}

void _inorder_tree_walk(RBTree *tree, RBNode *root){
	if (root != tree->nil) {
		_inorder_tree_walk(tree, root->left);
		printf(" %d", root->key);
		_inorder_tree_walk(tree, root->right);
	}
}

void inorder_tree_walk(RBTree* tree) {
	RBNode * root = tree->root;
	_inorder_tree_walk(tree, root);
}

RBNode* iterative_search(RBTree* tree, int key) {
	RBNode * root = tree->root;
	while (root != tree->nil && key != root->key) {
		if (key < root->key)
			root = root->left;
		else
			root = root->right;
	}
	return root;
}

RBNode* create_one_node(int key) {
	RBNode* node;

	node = (RBNode*)malloc(sizeof(RBNode));

	if (node == NULL)
		return NULL;

	memset(node, 0 ,sizeof(RBNode));

	node->key = key;

	return node;
}

// Insert
void insert(RBTree *tree, int key) {
	RBNode* new = create_one_node(key);

	if (new)
		insert_node(tree, new);
}

// Delete
void delete(RBTree *tree, int key) {
	RBNode* node = iterative_search(tree, key);

	if (node != tree->nil)
		delete_node(tree, node);
}
