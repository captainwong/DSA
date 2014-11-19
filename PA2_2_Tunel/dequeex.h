#pragma once

#define DEFAULT_DEQUE_CAPACITY (64 * 1024)

template <typename T> class DequeEx
{
private:
	int _capacity;
	int _beg;
	int _end;
	T* _elem;
protected:
	/*void expand()
	{
		if (_beg == 0 || _end == _capacity - 1) {
			_capacity <<= 2;
			T* old_elem = _elem;
			_elem = new T[_capacity];

			
			int old_beg = _beg - 1;
			int new_beg = (_capacity + _beg - _end) / 2;
			int new_end = new_beg + _end - _beg;

			for (int new_pos = new_beg, old_pos = old_beg; new_pos < _end - _beg - 1;) {
				_elem[new_pos++] = old_elem[old_pos++];
			}

			_beg = new_beg - 1;
			_end = new_end;
			delete[] old_elem;
		}
	}*/ // wrong
public:
	//DequeEx() :_capacity(0), _beg(0), _end(0), _elem(NULL) {}
	DequeEx(int size = DEFAULT_DEQUE_CAPACITY)
	{
		if (size < DEFAULT_DEQUE_CAPACITY)
			size = DEFAULT_DEQUE_CAPACITY;

		_capacity = ((size / DEFAULT_DEQUE_CAPACITY) + 1) * DEFAULT_DEQUE_CAPACITY;
		_beg = _capacity >> 2;
		_end = _beg + 1;
		_elem = new T[_capacity];
	}
	~DequeEx() { delete[] _elem; }

	int size() { return _end - _beg - 1; }

	bool empty() { return size() == 0; }

	// _elem[_capacity >> 2] always empty.
	void insert_as_front(T const& e)
	{
		//expand();
		_elem[_beg--] = e;
	}

	void insert_as_rear(T const& e)
	{
		//expand();
		_elem[_end++] = e;
	}

	T& front()
	{
		return _elem[_beg + 1];
	}

	T& rear()
	{
		return _elem[_end - 1];
	}

	T remove_front()
	{
		return _elem[++_beg];
	}

	T remove_rear()
	{
		return _elem[--_end];
	}
};