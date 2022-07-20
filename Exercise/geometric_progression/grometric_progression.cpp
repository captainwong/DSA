#include "../testcase.h"

int power(int x, int n) {
	int p = 1;
	for (int i = 0; i < n; i++) {
		p *= x;
	}
	return p;
}

int F(int a, int q, int n) {
	return a * power(q, n - 1);
}

int main()
{
	system("mkdir testcase");
	system("cd testcase && del *.in *.out testcase.zip && cd ..");

	gen_in_out(1, nullptr, nullptr);

	gen_in_out(2,
			   [](FILE* f) {
				   fprintf(f, "%d %d %d\n", 2, 2, 3);
			   },
			   [](FILE* f) {
				   fprintf(f, "%d\n", F(2, 2, 3));
			   });

	gen_in_out(3,
			   [](FILE* f) {
				   fprintf(f, "%d %d %d\n", 2, 3, 4);
				   fprintf(f, "%d %d %d\n", 6, 2, 4);
			   },
			   [](FILE* f) {
				   fprintf(f, "%d\n", F(2, 3, 4));
				   fprintf(f, "%d\n", F(6, 2, 4));
			   });

	gen_in_out(4,
			   [](FILE* f) {
				   fprintf(f, "%d %d %d\n", 2, 2, 0);
			   },
			   [](FILE* f) {
				   fprintf(f, "Invalid input\n");
			   });

	struct aqn {
		int a, q, n;
	};

	std::vector<aqn> as;
	for (int i = 0; i < 10; i++) {
		as.emplace_back(aqn{ (rand() % 3) + 1 , (rand() % 10) + 1 , (rand() % 8) + 1 });
	}

	gen_in_out(5,
			   [&as](FILE* f) {
				   for (const auto& i : as) {
					   fprintf(f, "%d %d %d\n", i.a, i.q, i.n);
				   }
			   },
			   [&as](FILE* f) {
				   for (const auto& i : as) {
					   fprintf(f, "%d\n", F(i.a, i.q, i.n));
				   }
			   });

	as.clear();
	for (int i = 0; i < 10; i++) {
		as.emplace_back(aqn{ -((rand() % 10) + 1) , -((rand() % 10) + 1) , (rand() % 7) + 1 });
	}

	gen_in_out(6,
			   [&as](FILE* f) {
				   for (const auto& i : as) {
					   fprintf(f, "%d %d %d\n", i.a, i.q, i.n);
				   }
			   },
			   [&as](FILE* f) {
				   for (const auto& i : as) {
					   fprintf(f, "%d\n", F(i.a, i.q, i.n));
				   }
			   });
	

	system("cd testcase && zip testcase.zip *.in *.out");

}