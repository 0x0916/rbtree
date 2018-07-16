#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rbtree.h"

RBNode* parent(RBNode *n) {
	return n->parent;
}

int is_leaf(RBNode *n) {
	return n == LEAF;
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

// n 代表x节点
void rotate_left(RBNode* n) { // n =x, y = nnew
	RBNode* nnew = n->right;

	n->right = nnew->left;
	if (!is_leaf(nnew->left)) {
		nnew->left->parent = n;
	}
	nnew->parent = n->parent;

	if (n->parent != NULL) {
		if (n == n->parent->left)
			n->parent->left = nnew;
		else
			n->parent->right = nnew;
	}
	nnew->left = n;
	n->parent = nnew;
}

// n代表y节点
void rotate_right(RBNode* n) {
	RBNode* nnew = n->left;

	n->left = nnew->right;
	if (!is_leaf(nnew->right)) {
		nnew->right->parent = n;
	}
	nnew->parent = n->parent;
	if (n->parent != NULL) {
		if (n == n->parent->right)
			n->parent->right = nnew;
		else
			n->parent->left = nnew;
	}
	nnew->right = n;
	n->parent = nnew;
}

RBNode* minimum(RBNode* n) {
	while (!is_leaf(n->left))
		n = n->left;
	return n;
}

RBNode* maximum(RBNode* n) {
	while (!is_leaf(n->right))
		n = n->right;
	return n;
}

RBNode* successor(RBNode* n) {
	RBNode* y;
	if (!is_leaf(n->right))
		return minimum(n->right);
	y = parent(n);
	while (!is_leaf(y) && n == y->right) {
		n = y;
		y = parent(y);
	}
}

RBNode* predecessor(RBNode* n) {
	RBNode* y;
	if (!is_leaf(n->left))
		return maximum(n->left);
	y = parent(n);
	while (!is_leaf(y) && n == y->left) {
		n = y;
		y = parent(y);
	}
}

void insert_recurse(RBNode *root, RBNode *n) {
	// recursively descend the tree until a leaf is found
	if (root != NULL) {
		if (n->key < root->key) {
			if (root->left != LEAF) {
				insert_recurse(root->left, n);
				return;
			}
			root->left = n;
		}else {
			if (root->right != LEAF) {
				insert_recurse(root->right, n);
				return;
			}
			root->right = n;
		}
	}

	// insert new node n
	n->parent = root;
	n->left = LEAF;
	n->right = LEAF;
	n->color = RED;
}

// n is the root node, set its'color to black
void insert_case1(RBNode *n) {
	if (parent(n) == NULL)
		n->color = BLACK;
}

// n's parent is black
void insert_case2(RBNode *n) {
	return;
}

void insert_repaire_tree(RBNode *n);
//n's parent is red and n's uncle is red
void insert_case3(RBNode *n) {
	parent(n)->color = BLACK;
	uncle(n)->color = BLACK;
	grandparent(n)->color = RED;
	insert_repaire_tree(grandparent(n));
}

void insert_case4step2(RBNode *n) {
	RBNode *p = parent(n);
	RBNode *g = grandparent(n);

	if (n == p->left)
		rotate_right(g); //情形1
	else
		rotate_left(g); //情形3

	p->color = BLACK;
	g->color = RED;
}

//n's parent is red and n's uncle is black
void insert_case4(RBNode *n) {
	RBNode *p = parent(n);
	RBNode *g = grandparent(n);

	if (n == g->left->right) {
	// 情形2
		rotate_left(p);
		n = n->left; // 转换为情形1
	}else if (n == g->right->left) {
	// 情形4
		rotate_right(p);
		n = n->right; //转换为情形3
	}

	insert_case4step2(n);
}

void insert_repaire_tree(RBNode *n) {
	if (parent(n) == NULL) {
		insert_case1(n); // n is the root node
	}else if (parent(n)->color == BLACK) {
		insert_case2(n); // n's parent is black
	}else if (uncle(n)->color == RED) {
		insert_case3(n); // n's parent is red and n's uncle is red
	}else {
		insert_case4(n); // n's parent is red and n's uncle is black
	}
}

// Insert a new node to RBTree
RBNode* insert_node(RBNode *root, RBNode *n)
{
	RBNode *newroot;
	// insert new node inot the current tree
	insert_recurse(root, n);

	// repaire the tree in case any of the red-black properties have been violated
	insert_repaire_tree(n);

	// find the new root to return
	root = n;
	while(parent(root) != NULL)
		root = parent(root);

	return root;
}


void delete_case5(RBNode *n) {
	RBNode *s = slibing(n);

	s->color = n->parent->color;
	s->parent->color = BLACK;

	if (n == n->parent->left) { //情形3
		s->right->color = BLACK;
		rotate_left(n->parent);
	}else { //情形1
		s->left->color = BLACK;
		rotate_right(n->parent);
	}
}

void delete_case4(RBNode *n) {
	// 此时，删除结点为黑色，兄弟结点为黑色
	// 有一个侄子为红色

	// 这里分为四种情况

	RBNode *s = slibing(n);

	if (s->color == BLACK) {
		if ((n == n->parent->left) &&
			(s->right->color == BLACK) &&
			(s->left->color == RED)) { //情形4
			s->color = RED;
			s->left->color = BLACK;
			rotate_right(s);
		} else if ((n == n->parent->right) &&
				(s->left->color == BLACK) &&
				(s->right->color == RED)) { // 情形2
			s->color = RED;
			s->right->color = BLACK;
			rotate_left(s);
		}
	}

	delete_case5(n);
}

void delete_case2(RBNode *n);
void delete_case1(RBNode* n) {
	// 如果要删除的结点为根结点，此时n为LEAF，不需要进行任何操作
	// 否则根据其兄弟结点进行判断
	if (n->parent != NULL)
		delete_case2(n);
}

void delete_case3(RBNode *n) {
	// 此时，删除结点为黑色，兄弟结点为黑色
	// 根据其父亲和侄子的颜色区分一下情况

	RBNode *s = slibing(n);
	// 父亲是黑色，两个侄子是黑色
	if (n->parent->color == BLACK &&
		s->color == BLACK &&
		s->left->color == BLACK &&
		s->right->color == BLACK) {
		s->color = RED;
		delete_case1(n->parent);
	} else if (n->parent->color == RED && // 父亲是红色，两个侄子是黑色
		s->color == BLACK &&
		s->left->color == BLACK &&
		s->right->color == BLACK) {
		s->color = RED;
		n->parent->color = BLACK;
	} else {
		delete_case4(n);
	}
}


void delete_case2(RBNode *n) {
	RBNode *s = slibing(n);

	//兄弟结点为红色
	if (s->color == RED) {
		n->parent->color = RED;
		s->color = BLACK;

		if (n == n->parent->left)
			rotate_left(n->parent);
		else
			rotate_right(n->parent);
	}
	//兄弟结点为黑色
	delete_case3(n);
}


void rb_delete_fixup(RBNode* n)
{
	/*
	 * Precondition: n has at most one non-leaf child
	 */
	RBNode* child = is_leaf(n->right)? n->left: n->right;

	// 如果要删除的结点为红色，则它必定是叶子结点，直接删除即可
	// 要删除的结点为黑色, 则进行如下处理
	if (n->color == BLACK) {
		if (child->color == RED) // 删除结点为黑色，其孩子结点为红色
			child->color = BLACK;
		else			// 删除结点为黑色，且为叶子结点
			delete_case1(child);
	}
	free(n);
}

RBNode* delete_node(RBNode* root, RBNode *n) {
	RBNode *y, *x;
	// y是真正要删除的结点
	if (is_leaf(n->left) || is_leaf(n->right))
		y = n;
	else
		y = successor(n);

	// x是y的子结点
	if (!is_leaf(y->left))
		x = y->left;
	else
		x = y->right;

	// 删除y
	x->parent = y->parent;
	if ((parent(y) == NULL))
		root = x;
	else if(y == parent(y)->left)
		parent(y)->left = x;
	else
		parent(y)->right = x;

	if (y != n) 
		n->key = y->key;

	rb_delete_fixup(y);

	// find the new root to return
	root = x;
	while(parent(root) != NULL)
		root = parent(root);

	return root;
}


void inorder_tree_walk(RBNode* root) {
	if (!is_leaf(root)) {
		inorder_tree_walk(root->left);
		printf(" %d", root->key);
		inorder_tree_walk(root->right);
	}
}

RBNode* search(RBNode* root, int key) {
	if (is_leaf(root) || key == root->key)
		return root;
	if (key < root->key)
		return search(root->left, key);
	else
		return search(root->right, key);
}

RBNode* iterative_search(RBNode* root, int key) {
	RBNode * n = root;
	while (!is_leaf(n) && key != n->key) {
		if (key < n->key)
			n = n->left;
		else
			n = n->right;
	}

	return n;
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
RBNode* insert(RBNode *root, int key) {
	RBNode* new = create_one_node(key);

	if (new)
		return (RBNode*)insert_node(root, new);
	else
		return NULL;
}

// Delete
RBNode* delete(RBNode *root, int key) {
	RBNode* node = iterative_search(root, key);

	if (!is_leaf(node))
		delete_node(root, node);
}
