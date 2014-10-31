#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>
//#include "list.h"
//#include <windows.h>
int employee[10000001] = { -1 };

//#define MAXS 128 * 1024 * 1024
//char buff[MAXS] = { 0 };

class Bitmap
{
private:
	int *F;
	int *T;
	int N;
	int top;
protected:
	inline bool valid(int r)
	{
		return (0 <= r) && (r < top);
	}

	inline bool erased(int k)
	{
		return valid(F[k]) && !(T[F[k]] + 1 + k);
	}

public:
	Bitmap(int n = 8)
	{
		N = n;
		F = new int[N];
		T = new int[N];
		top = 0;
	}
	~Bitmap()
	{
		delete[] F;
		delete[] T;
	}

	inline void set(int k)
	{
		if (!test(k) && !erased(k)) {
			F[k] = top++;
		}
		T[F[k]] = k;
	}

	inline void clear(int k)
	{
		if (test(k)) {
			T[F[k]] = -1 - k;
		}
	}

	inline bool test(int k)
	{
		return valid(F[k]) && (k == T[F[k]]);
	}

	inline int size() const
	{
		return top;
	}

	inline int get(int r)
	{
		if (valid(r)) {
			return T[r];
		}
		return -1;
	}

	inline void clear()
	{
		//memset(T, 0, N*sizeof(int));
		//memset(F, 0, N*sizeof(int));
		top = 0;
	}
};

int main(int argc, char* argv[])
{
	//int len = fread(buff, 1, MAXS, stdin);
	//buff[len] = '\0';
	int n, m;
	if (scanf("%d %d", &n, &m) == EOF)
		return 0;

	//int *employee = new int[n + 1];
	memset(employee, 0xff, (n + 1) * sizeof(int));
	Bitmap bitmap(n+1);
	
	int working = 0;

	char cmd = 0;
	int number = 0;
	int code = 0;
	int result = 0;

	//DWORD total = 0;
	//DWORD start = GetTickCount();
	for (int i = 0; i < m; i++) {
		if (scanf("%c", &cmd) == EOF)
			return 0;
		if (cmd == '\n' || cmd == '\r' || cmd == ' ') {
			i--;
			continue;
		}
		switch (cmd) {
			case 'I':
				if (scanf("%d %d", &number, &code) == EOF)
					return 0;
				//if (employee[number] == -1)
				if (!bitmap.test(number)) {
					bitmap.set(number);
					working++;
				}
				employee[number] = code;
				break;
			case 'O':
				if (scanf("%d", &number) == EOF)
					return 0;
				//if (employee[number] != -1) 
				if (bitmap.test(number)) {
					employee[number] = -1;
					bitmap.clear(number);
					working--;
				}
				break;
			case 'C':
				if (working > 0) {
					//DWORD beg = GetTickCount();
					//memset(employee, 0xff, (n + 1) * sizeof(int));
					working = 0;
					bitmap.clear();
					/*int size = bitmap.size();
					for (int i = 0; i < size; i++) {
						int k = bitmap.get(i);
						if (bitmap.test(k)) {
							bitmap.clear(k);
							employee[k] = -1;
						}
					}*/
					//total += GetTickCount() - beg;
				}
				break;
			case 'N':
				result += working;
				break;
			case 'Q':
				if (scanf("%d", &number) == EOF)
					return 0;
				if (bitmap.test(number))
					result += employee[number];
				else
					result += -1;
				break;
			default:
				return 0; break;
		}
	}
	printf("%d\n", result);
	//printf("total %dms, memset %dms, avr %dms\n", GetTickCount() - start, total, total / n);
	//delete[] employee;

	return 0;
}
