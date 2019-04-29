
#include "../include/dtl/vector.h"
#include "../include/test/test_vector.h"

using namespace dtl;

int main(int argc, char* argv[])
{
	test::testVector<int>(10, 1000);
	return 0;
}
