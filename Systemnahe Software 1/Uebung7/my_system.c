#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/mman.h>
#include "my_system.h"

#define SYSBLOCKSIZE 8192

struct sysblock {
	char * start;
	int offset;
	struct sysblock * next;
};

static struct sysblock * sysblocks = NULL;
static int sys_blockcount = 0;
static struct avl_node * blocks = NULL;

void * get_block_from_system ()
{
	char * ret;
	if (sysblocks == NULL || sysblocks->offset == SYSBLOCKSIZE) {
		struct sysblock * nb = malloc (sizeof (struct sysblock));
		/* Betriebssystem hat keinen weiteren Speicher mehr. */
		my_assert (nb, "Betriebssystem hat keinen weiteren Speicher mehr");
		nb->start = mmap (0, SYSBLOCKSIZE, PROT_READ|PROT_WRITE,
		                  MAP_PRIVATE|MAP_ANON, -1, 0);
		if (nb->start == NULL || nb->start == MAP_FAILED) {
			free (nb);
			return NULL;
		}
		nb->offset = 0;
		nb->next = sysblocks;
		sysblocks = nb;
	}
	ret = sysblocks->start + sysblocks->offset;
	sysblocks->offset += BLOCKSIZE;
	sys_blockcount++;
	if (blocks == NULL) {
		blocks = create_avl ();
	}
	insert_avl (&blocks, (unsigned long)ret, BLOCKSIZE);
	return ret;
}

int get_sys_blockcount ()
{
	return sys_blockcount;
}

int valid_area (unsigned long start, unsigned long len)
{
	struct avl_node * node;
	if (!blocks)
		return 0;
	node = find_avl (blocks, start);
	assert (node->start <= start);
	/* Speicherbereich an Adresse 0 oder nicht an einer 8 Byte Kante. */
	my_assert (start && start % 8 == 0 && len % 8 == 0, "Speicherbereich an Adresse 0 oder nicht an einer 8 Byte Kante");
	if (node->start + node->len >= start + len)
		return 1;
	return 0;
}

#define HEIGHT_LEFT(N)  (((N)->left)?((N)->left->height):0)
#define HEIGHT_RIGHT(N) (((N)->right)?((N)->right->height):0)
#define GETHEIGHT(N) ((HEIGHT_LEFT(N)>HEIGHT_RIGHT(N))?(1+HEIGHT_LEFT(N)):(1+HEIGHT_RIGHT(N)))

static void check_tree (struct avl_node * root);
static void check_ptr (struct avl_node * root);

static void rebalance1 (struct avl_node ** root, struct avl_node * n)
{
	struct avl_node * parent;
	if (n == 0)
		return;
	parent = n->parent;
	n->height = GETHEIGHT(n);
	if (HEIGHT_LEFT(n) + 1 < HEIGHT_RIGHT(n)) {
		struct avl_node * r = n->right;
		struct avl_node * rl = r->left;
		if (HEIGHT_RIGHT(r) > HEIGHT_LEFT(n)) {
			r->left = n; n->parent = r;
			n->right = rl;
			if (rl) {
				rl->parent = n;
			}
			n->height = GETHEIGHT(n);
			r->height = GETHEIGHT(r);
			r->parent = parent;
			if (parent) {
				if (parent->left == n) {
					parent->left = r;
				} else {
					parent->right = r;
				}
				parent->height = GETHEIGHT(parent);
			} else {
				(*root) = r;
			}
		} else {
			struct avl_node * rll = rl->left;
			struct avl_node * rlr = rl->right;
			n->right = rll;
			if (rll)
				rll->parent = n;
			r->left = rlr;
			if (rlr)
				rlr->parent = r;
			rl->left = n; n->parent = rl;
			rl->right = r; r->parent = rl;
			rl->parent = parent;
			n->height = GETHEIGHT(n);
			r->height = GETHEIGHT(r);
			rl->height = GETHEIGHT(rl);
			if (parent) {
				if (parent->left == n) {
					parent->left = rl;
				} else {
					parent->right = rl;
				}
				parent->height = GETHEIGHT(parent);
			} else {
				(*root) = rl;
			}
		}
		return;
	}
	if (HEIGHT_RIGHT(n) + 1 < HEIGHT_LEFT(n)) {
		struct avl_node * l = n->left;
		struct avl_node * lr = l->right;
		if (HEIGHT_LEFT(l) > HEIGHT_RIGHT(n)) {
			l->right = n; n->parent = l;
			n->left = lr;
			if (lr)
				lr->parent = n;
			n->height = GETHEIGHT(n);
			l->height = GETHEIGHT(l);
			l->parent = parent;
			if (parent) {
				if (parent->left == n) {
					parent->left = l;
				} else {
					parent->right = l;
				}
				parent->height = GETHEIGHT(parent);
			} else {
				(*root) = l;
			}
		} else {
			struct avl_node * lrl = lr->left;
			struct avl_node * lrr = lr->right;
			n->left = lrr;
			if (lrr)
				lrr->parent = n;
			l->right = lrl;
			if (lrl)
				lrl->parent = l;
			lr->right = n; n->parent = lr;
			lr->left = l; l->parent = lr;
			lr->parent = parent;
			n->height = GETHEIGHT(n);
			l->height = GETHEIGHT(l);
			lr->height = GETHEIGHT(lr);
			if (parent) {
				if (parent->left == n) {
					parent->left = lr;
				} else {
					parent->right = lr;
				}
				parent->height = GETHEIGHT(parent);
			} else {
				(*root) = lr;
			}
		}
		return;
	}
}

static void rebalance (struct avl_node ** root, struct avl_node * node)
{
	struct avl_node * next;
	while (node) {
		next = node->parent;
		rebalance1 (root, node);
		node = next;
	}
}

struct avl_node * create_avl (void)
{
	struct avl_node * ret = malloc (sizeof (struct avl_node));
	assert (ret);
	ret->prev = ret->next = NULL;
	ret->left = ret->right = ret->parent = NULL;
	ret->start = ret->len = 0;
	ret->height = 1;
	return ret;
}

struct avl_node * find_avl (struct avl_node * root, unsigned long start)
{
	struct avl_node * node = root;
	assert (node);
	while (1) {
		if (start < node->start) {
			if (!node->left) {
				break;
			}
			node = node->left;
			continue;
		}
		if (node->start == start)
			return node;
		if (!node->right)
			break;
		node = node->right;
	}
	if (start < node->start) {
		assert (node->prev);
		node = node->prev;
	}
	assert (start >= node->start);
	if (node->next) {
		assert (node->next->start > start);
	}
	return node;
}

void insert_avl (struct avl_node ** root, unsigned long start, unsigned long len)
{
	struct avl_node * prev = find_avl (*root, start);
	struct avl_node * next = prev->next;
	struct avl_node * n;
	/* Ueberlappende Speicherbereiche! */
	my_assert (prev->start + prev->len <= start, "Ueberlappende Speicherbereiche");
	if (next) {
		/* Ueberlappende Speicherbereiche */
		my_assert (next->start >= start + len, "Ueberlappende Speicherbereiche");
	}
	n = malloc (sizeof (struct avl_node));
	assert (n);
	n->start = start;
	n->len = len;
	n->prev = prev;
	n->next = next;
	prev->next = n;
	if (next) {
		next->prev = n;
	}
	n->height = 1;
	n->left = n->right = NULL;
	if (prev->right == NULL) {
		prev->right = n;
		n->parent = prev;
	} else {
		prev = prev->right;
		while (prev->left) {
			prev = prev->left;
		}
		prev->left = n;
		n->parent = prev;
	}
	rebalance (root, n);
}

void remove_avl (struct avl_node ** root, struct avl_node * node)
{
	struct avl_node * todel;
	if (node->left == NULL) {
		struct avl_node * prev = node->prev;
		struct avl_node * next = node->next;
		struct avl_node * parent = node->parent;
		prev->next = next;
		if (next) {
			next->prev = prev;
		} else {
			assert (node->right == NULL);
		}
		if (parent) {
			if (parent->left == node) {
				parent->left = node->right;
			} else {
				assert (parent->right == node);
				parent->right = node->right;
			}
		} else {
			(*root) = node->right;
		}
		if (node->right) {
			node->right->parent = parent;
		}
		free (node);
		rebalance (root, parent);
	} else {
		struct avl_node * prev;
		struct avl_node * next;
		struct avl_node * parent;
		todel = node->prev;
		assert (todel && todel->right == NULL);
		node->start = todel->start;
		node->len = todel->len;
		prev = todel->prev;
		next = todel->next;
		parent = todel->parent;
		if (prev) {
			prev->next = next;
		}
		if (next) {
			next->prev = prev;
		}
		if (parent) {
			if (parent->left == todel) {
				parent->left = todel->left;
			} else {
				parent->right = todel->left;
			}
		} else {
			(*root) = todel->left;
		}
		if (todel->left) {
			todel->left->parent = parent;
		}
		free (todel);
		rebalance (root, parent);
	}
}

static void check_ptr (struct avl_node * root)
{
	if (root->left)
		assert (root->left->parent == root);
	if (root->right)
		assert (root->right->parent == root);
	if (root->parent)
		assert (root == root->parent->left || root == root->parent->right);
}

static void check_tree (struct avl_node * root)
{
	if (!root)
		return;
	int hl = HEIGHT_LEFT(root);
	int hr = HEIGHT_RIGHT(root);
	//printf ("node %p %d left %p %d right %p %d\n", root, root->height,
	//	root->left, hl, root->right, hr); 
	check_ptr (root);
	assert (abs (hl - hr) <= 1);
	assert (root->height >= hl+1 && root->height >= hr+1);
	assert (root->height == hl+1 || root->height == hr+1);
	check_tree (root->left);
	check_tree (root->right);
}

void __my_assert (char * text)
{
	fprintf (stderr, "\nFEHLER: %s\n", text);
	exit (1);
}
