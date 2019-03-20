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

	assert(i->height == 4);
	assert(d->height == 3 && l->height == 3);
	assert(c->height == 2 && h->height == 2 && k->height == 1 && n->height == 2);
	assert(a->height == 1 && f->height == 1 && j->height == 0 && m->height == 0 && p->height == 1);
	assert(b->height == 0 && e->height == 0 && g->height == 0 && o->height == 0);

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
