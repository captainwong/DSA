#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "list.h"

// Import from ProgramCaicai.
// http://www.xuetangx.com/courses/TsinghuaX/30240184X/2014_T2/discussion/forum/undefined/threads/54392f32459f089cdd008aa2
const int SZ = 1 << 20;
struct fastio
{
	char inbuf[SZ];
	char outbuf[SZ];
	fastio()
	{
		setvbuf(stdin, inbuf, _IOFBF, SZ);
		setvbuf(stdout, outbuf, _IOFBF, SZ);
	}
}io;
// Import end.

#define MAX_VER 4000000

template <typename T>
struct list_node
{
	//int rank;
	T data;
	list_node<T>* prev;
	list_node<T>* next;
};

template <typename T>
class list
{
private:
	int _size;
	list_node<T>* _head;
	list_node<T>* _tail;
	//list_node* _v[MAX_VAR];
public:
	list() : _size(0), _head(NULL), _tail(NULL)
	{
		_head = new list_node<T>();
		_tail = new list_node<T>();
		_head->data = NULL;
		_head->prev = NULL;
		_head->next = _tail;
		_tail->data = NULL;
		_tail->prev = _head;
		_tail->next = NULL;
	}

	~list() { clear(); }

	int size() const { return _size; }
	list_node<T>* begin() { return _head->next; }
	list_node<T>* end() { return _tail; }

	void clear()
	{
		list_node<T>* node = _head->next;
		while (node != _tail) {
			list_node<T>* tmp = node->next;
			delete node;
			node = tmp;
		}
		_head->next = _tail;
		_tail->prev = _head;
		_size = 0;
	}

	void push_back(T const& data)
	{
		list_node<T>* node = new list_node<T>();
		node->data = data;
		node->prev = _tail->prev;
		node->next = _tail;
		_tail->prev->next = node;
		_tail->prev = node;
		_size++;
	}

	list_node<T>* insert_b(list_node<T>* pos, T const& data)
	{
		list_node<T>* node = new list_node<T>();
		node->data = data;
		node->prev = pos->prev;
		node->next = pos;
		pos->prev->next = node;
		pos->prev = node;
		_size++;
		return node;
	}

	/*list_node* insert(int rank, T const& data)
	{
		list_node* node = _v[rank];
		if (node == NULL) {
			node = new list_node();
			node->data = data;
			node->prev = _head;
			node->next = _tail;
			for (int i = rank - 1; i > 0; i--) {
				if (_v[i]) {
					node->prev = _v[i];
					_v[i]->next = node;
					break;
				}
			}
			for (int i = rank + 1; i < MAX_VAR; i++) {
				if (_v[i]) {
					node->next = _v[i];
					_v[i]->prev = node;
					break;
				}
			}
		}
	}
*/
	
	T remove(list_node<T>* node)
	{
		T data = node->data;
		list_node<T>* prev = node->prev;
		list_node<T>* next = node->next;
		delete node;
		prev->next = next;
		next->prev = prev;
		_size--;
		return data;
	}
};


//int Ligth[MAX_VER] = { 0 };

typedef struct LIGHT
{
	int x;
	int y;
	LIGHT(int a = 0, int b = 0) :x(a), y(b) {}
	/*LIGHT& operator=(const LIGHT& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}*/

	bool operator <= (const LIGHT& rhs)
	{
		return x <= rhs.x;
	}

}LIGHT, *PLIGHT;

//LIGHT Light[MAX_VER] = { (0, 0) };
int size = 0;
list<PLIGHT> LightList;
typedef list_node<PLIGHT>* Pos;
//list_node<PLIGHT> PosArray[MAX_VER] = { NULL };
//typedef List<LIGHT> LIGHT_LIST;
//typedef ListNode<LIGHT>* POS;

#define max(a, b)	(a) > (b) ? (a) : (b) 
#define min(a, b)	(a) < (b) ? (a) : (b) 


long long invertion_between(Pos lo, int m, Pos mi, int n)
{
	long long sum = 0;
	/*LIGHT *A = Light + lo;
	int lb = mi - lo;
	LIGHT *B = new LIGHT[lb]; for (int i = 0; i < lb; i++) { B[i] = A[i]; }
	int lc = hi - mi;
	LIGHT *C = A + mi;
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
		if ((j < lb) && (lc <= k || B[j].y < C[k].y)) {
			if (k < lc && (B[j].y < C[k].y)) {
				sum += lc - k;
			}
			A[i++] = B[j++];
		}
		if ((k < lc) && (lb <= j || C[k].y < B[j].y))
			A[i++] = C[k++];
	}
	delete[] B;*/

	Pos pp = lo->prev;
	while (0 < n) {
		if ((0 < m) && (lo->data->y < mi->data->y)) {
			sum += n;
			if (mi == (lo = lo->next))
				break;
			m--;
		} else {
			LightList.insert_b(lo, LightList.remove((mi = mi->next)->prev));
			n--;
		}
	}
	lo = pp->next;
	return sum;
}

long long invertion_inside(Pos lo, Pos hi, int n)
{
	if (n < 2)
		return 0;

	int m = (n) >> 1;
	Pos mi = lo;
	for(int i = 0; i < m; i++)
		mi = mi->next;
	long long l = invertion_inside(lo, mi, m);
	long long r = invertion_inside(mi, hi, n - m);
	return l + r + invertion_between(lo, m, mi, n - m);
}

void init_light_list()
{

}

void insert_and_sort_light(int x, int y)
{
	//ListNodePosi(PLIGHT) targetPos = NULL;
	bool b = false;
	list_node<PLIGHT>* targetPos = LightList.begin();
	while (targetPos != LightList.end()) {
		if (targetPos->data->x > x) {
			b = true;
			break;
		}
		targetPos = targetPos->next;
	}
	if (b) {
		LightList.insert_b(targetPos, new LIGHT(x, y));
	} else {
		LightList.push_back(new LIGHT(x, y));
	}
}

int main(int argc, char* argv[])
{
	int n = 0;
	if (scanf("%d", &n) == EOF)
		return 0;
	//LIGHT_LIST list;

	int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		if (scanf("%d %d", &x, &y) == EOF)
			return 0;
		//list.insert_as_last(LIGHT(x, y));
		insert_and_sort_light(x, y);
	}

	//list.sort();

//#ifndef _OJ_
//	ListNodePosi(LIGHT) p = list.first();
//	for (int i = 0; i < list.size(); i++, p = p->succ) {
//		printf("(%d, %d)\n", p->data.x, p->data.y);
//	}
//#endif
	//POS head = list.first();
	long long total = invertion_inside(LightList.begin(), LightList.end()->prev, n);
	printf("%lld\n", total);
	return 0;
}