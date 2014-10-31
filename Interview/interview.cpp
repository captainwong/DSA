#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct Node
{
	int data;
	Node* pred;
	Node* succ;
	Node(int data) :data(data) {}
	Node(int data, Node* pred, Node* succ) :data(data), pred(pred), succ(succ) {}
	inline Node* insertA(int data)
	{
		Node* node = new Node(data, this, succ);
		succ->pred = node;
		succ = node;
		return node;
	}

	inline Node* insertB(int data)
	{
		Node* node = new Node(data, pred, this);
		pred->succ = node;
		pred = node;
		return node;
	}
};

class SimpleList
{
private:
	Node* head;
	Node* tail;
	int _size;
protected:
	void init()
	{
		head = NULL;
		tail = NULL;
		_size = 0;
	}
	void clear()
	{
		Node* node = head;
		for (int i = 0; i < _size; i++) {
			Node* temp = node;
			node = node->succ;
			delete temp;
		}
	}
public:
	SimpleList() { init(); }
	~SimpleList() { clear(); }
	Node* last() const { return tail; }
	int size() const { return _size; }
	void insert(int data, int rank = 0)
	{
		if (_size == 0) {
			Node* node = new Node(data);
			node->pred = node->succ = node;
			head = tail = node;
		} else if (_size == 1) {
			Node* node = new Node(data);
			node->pred = node->succ = head;
			head->pred = head->succ = node;
			tail = node;
		}else {
			Node* pos = tail;
			for (int i = 0; i < rank; i++) {
				pos = pos->pred;
			}
			tail = pos->insertA(data);
		}
		_size++;
	}
};

void print_list(SimpleList& list, int n)
{
	Node* node = list.last();
	/*char out[1000 * 4] = { 0 };
	char temp[32] = { 0 };
	for (int i = 0; i < list.size(); i++) {
		sprintf(temp, "%d ", node->data);
		strcat(out, temp);
		node = node->succ;
	}
	strcat(out, "\n");
	printf(out);*/
	for (int i = 0; i < n && i < list.size(); i++) {
		printf("%d ", node->data);
		node = node->succ;
	}
	printf("\n");
}

#ifndef _OJ
void reverse_print_list(SimpleList& list)
{
	Node* node = list.last();
	//char out[1000 * 4] = { 0 };
	//char temp[32] = { 0 };
	for (int i = 0; i < list.size(); i++) {
		//sprintf(temp, "%d ", node->data);
		//strcat(out, temp);
		printf("%d ", node->data);
		node = node->pred;
	}
	printf("\n");
	//strcat(out, "\n");
	//printf(out);
}
#endif

int main(int argc, char* argv[])
{
	SimpleList list;
	/*list.insert(0);
	list.insert(1, 1);
	list.insert(2, 2);*/
	int n, m;
	if (scanf("%d %d", &n, &m) == EOF)
		return 0;

	int id = 0;
	for (int i = 0; i < n; i++) {
		if (scanf("%d", &id) == EOF)
			return 0;
		list.insert(id, m);
#ifndef _OJ_
		//print_list(list);
#endif
	}

	print_list(list, n);
	return 0;
}





