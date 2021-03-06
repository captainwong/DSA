#include "../../include/test/test_bintree.h"
#include <string>
#include <assert.h>

using namespace dtl;

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

	// test pred
	assert(a->pred() == nullptr);
	assert(b->pred() == a);
	assert(c->pred() == b);
	assert(d->pred() == c);
	assert(e->pred() == d);
	assert(f->pred() == e);
	assert(g->pred() == f);
	assert(h->pred() == g);
	assert(i->pred() == h);
	assert(j->pred() == i);
	assert(k->pred() == j);
	assert(l->pred() == k);
	assert(m->pred() == l);
	assert(n->pred() == m);
	assert(o->pred() == n);
	assert(p->pred() == o);

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

	tree.travPreOrder(visit);
	assert(str == "idcabhfeglkjnmpo");

	str.clear();
	tree.travInOrder(visit);
	assert(str == "abcdefghijklmnop");

	str.clear();
	tree.travPostOrder(visit);
	assert(str == "bacegfhdjkmopnli");

	str.clear();
	tree.travLevelOrder(visit);
	assert(str == "idlchknafjmpbego");

	// test swap
	tree.root()->swap();
	print(tree);
	str.clear();
	tree.travInOrder(visit);
	assert(str == "ponmlkjihgfedcba");
}

int main(int /*argc*/, char** /*argv*/)
{
	test_tree();
	system("pause");

	dtl::test::testBinTree<int>(5, -1);

	return 0;
}
