#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "../include/bintree.h"

#include "bintree/BinTree.h"
#include <string>
#include <assert.h>

void test_tree()
{
	/*
							i
				d						l
		    c	    h				k		 n
		a		  f				 j		   m    p	
		  b      e g						  o
	*/
	BinTree<char> tree;
	auto i = tree.insertAsRootNode('i');
	auto d = tree.insertAsLeftChild(i, 'd');
	auto c = tree.insertAsLeftChild(d, 'c');
	auto a = tree.insertAsLeftChild(c, 'a');
	auto b = tree.insertAsRightChild(a, 'b');
	auto h = tree.insertAsRightChild(d, 'h');
	auto f = tree.insertAsLeftChild(h, 'f');
	auto e = tree.insertAsLeftChild(f, 'e');
	auto g = tree.insertAsRightChild(f, 'g');
	auto l = tree.insertAsRightChild(i, 'l');
	auto k = tree.insertAsLeftChild(l, 'k');
	auto j = tree.insertAsLeftChild(k, 'j');
	auto n = tree.insertAsRightChild(l, 'n');
	auto m =tree.insertAsLeftChild(n, 'm');
	auto p = tree.insertAsRightChild(n, 'p');
	auto o = tree.insertAsLeftChild(p, 'o');

	// basic test
	assert(i->isRoot());
	assert(i->hasLChild());
	assert(i->hasRChild());
	assert(!d->isRoot());
	assert(d->isLChild());
	assert(l->isRChild());

	// test succ
	assert(a->succ() == b);
	assert(b->succ() == c);
	assert(c->succ() == d);
	assert(d->succ() == e);
	assert(e->succ() == f);
	assert(f->succ() == g);
	assert(g->succ() == h);
	assert(h->succ() == i);
	assert(i->succ() == j);
	assert(j->succ() == k);
	assert(k->succ() == l);
	assert(l->succ() == m);
	assert(m->succ() == n);
	assert(n->succ() == o);
	assert(o->succ() == p);
	assert(p->succ() == nullptr);

	// test height
	assert(i->height_ == 4);
	assert(d->height_ == 3 && l->height_ == 3);
	assert(c->height_ == 2 && h->height_ == 2 && k->height_ == 1 && n->height_ == 2);
	assert(a->height_ == 1 && f->height_ == 1 && j->height_ == 0 && m->height_ == 0 && p->height_ == 1);
	assert(b->height_ == 0 && e->height_ == 0 && g->height_ == 0 && o->height_ == 0);

	// test travel
	std::string str;
	auto visit = [&str](char c) {
		str += c;
	};

	tree.travPreOrder(i, visit);
	assert(str == "idcabhfeglkjnmpo");

	str.clear();
	tree.travInOrder(i, visit);
	assert(str == "abcdefghijklmnop");

	str.clear();
	tree.travPostOrder(i, visit);
	assert(str == "bacegfhdjkmopnli");

	str.clear();
	tree.travLevelOrder(i, visit);
	assert(str == "idlchknafjmpbego");

	
}

int main(int /*argc*/, char** /*argv*/)
{
	test_tree();
	system("pause");
	return 0;
}
