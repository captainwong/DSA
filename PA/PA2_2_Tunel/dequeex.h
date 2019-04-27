#pragma once

#define DEFAULT_DEQUE_CAPACITY (64 * 1024)

template <typename T> class DequeEx
{
private:
	int capacity_;
	int _beg;
	int _end;
	T* elem_;
protected:
	/*void expand()
	{
		if (_beg == 0 || _end == capacity_ - 1) {
			capacity_ <<= 2;
			T* old_elem = elem_;
			elem_ = new T[capacity_];

			
			int old_beg = _beg - 1;
			int new_beg = (capacity_ + _beg - _end) / 2;
			int new_end = new_beg + _end - _beg;

			for (int new_pos = new_beg, old_pos = old_beg; new_pos < _end - _beg - 1;) {
				elem_[new_pos++] = old_elem[old_pos++];
			}

			_beg = new_beg - 1;
			_end = new_end;
			delete[] old_elem;
		}
	}*/ // wrong
public:
	//DequeEx() :capacity_(0), _beg(0), _end(0), elem_(NULL) {}
	DequeEx(int size = DEFAULT_DEQUE_CAPACITY)
	{
		if (size < DEFAULT_DEQUE_CAPACITY)
			size = DEFAULT_DEQUE_CAPACITY;

		capacity_ = ((size / DEFAULT_DEQUE_CAPACITY) + 1) * DEFAULT_DEQUE_CAPACITY;
		_beg = capacity_ >> 2;
		_end = _beg + 1;
		elem_ = new T[capacity_];
	}
	~DequeEx() { delete[] elem_; }

	int size() { return _end - _beg - 1; }

	bool empty() { return size() == 0; }

	// elem_[capacity_ >> 2] always empty.
	void insert_as_front(T const& e)
	{
		//expand();
		elem_[_beg--] = e;
	}

	void insert_as_rear(T const& e)
	{
		//expand();
		elem_[_end++] = e;
	}

	T& front()
	{
		return elem_[_beg + 1];
	}

	T& rear()
	{
		return elem_[_end - 1];
	}

	T remove_front()
	{
		return elem_[++_beg];
	}

	T remove_rear()
	{
		return elem_[--_end];
	}
};